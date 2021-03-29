#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <vector>
#include <sstream>

Image::Image(const std::string& filename, ImageFormat format) {
	m_Bytes = LoadImage(filename, &m_Width, &m_Height, &m_Format, format);
}

Image::~Image() {
	FreeImage(m_Bytes);
}

void Image::Save(std::string filename, ImageFileType fileType, int jpgQuality) {
	SaveImage(filename, m_Bytes, m_Width, m_Height, m_Format, fileType, jpgQuality);
}

uint8_t* Image::LoadImage(const std::string& filename, int* width, int* height, ImageFormat* format, ImageFormat desiredFormat) {
	int n = 0;
	if(desiredFormat != Format_Invalid) {
		int bytesPerPixel = desiredFormat;
		uint8_t* bytes = stbi_load(filename.c_str(), width, height, &n, bytesPerPixel);
		*format = desiredFormat;
		return bytes;
	}
	uint8_t* bytes = stbi_load(filename.c_str(), width, height, &n, 0);
	if(!bytes) {
		*format = Format_Invalid;
	} else {
		switch(n) {
			case 1: *format = Format_Grey8; break;
			case 2: *format = Format_AlphaGrey16; break;
			case 3: *format = Format_RGB24; break;
			case 4: *format = Format_ARGB32; break;
		}
		*format = (ImageFormat)n;
	}
	return bytes;
}

void Image::FreeImage(uint8_t* bytes) {
	stbi_image_free(bytes);
}

inline std::vector<std::string> Split(std::string str, char delim, bool ignoreEmpty = true) {
	// Current token
	std::stringstream token;
	std::vector<std::string> tokens;

	for(int i = 0; i < str.length(); i++) {
		if(str.at(i) == delim) {
			token.flush();
			if(!ignoreEmpty || !token.str().empty()) {
				tokens.push_back(token.str());
			}
			token.str(std::string()); // Empty the current token
		} else {
			token << char(str.at(i)); // Should probably make sure it's copied
		}
	}
	token.flush();
	if(!ignoreEmpty || !token.str().empty()) {
		tokens.push_back(token.str());
	}

	return tokens;
}

void Image::SaveImage(std::string filename, uint8_t* bytes, int width, int height, ImageFormat format, ImageFileType fileType, int jpgQuality) {
	if(fileType == FileType_Auto) {
		std::vector<std::string> parts = Split(filename, '.');
		std::string extension = parts.at(parts.size() - 1);
		if(extension == "png") {
			fileType = FileType_PNG;
		} else if(extension == "jpg" || extension == "jpeg") {
			fileType = FileType_JPG;
		} else if(extension == "bmp") {
			fileType = FileType_BMP;
		} else if(extension == "tga") {
			fileType = FileType_TGA;
		} else {
			fileType = FileType_PNG; // Default is PNG
		}
	}

	switch(fileType) {
		default: // This won't be used, but if somehow it does then just flow through to PNG
		case FileType_PNG:
			stbi_write_png(filename.c_str(), width, height, format, bytes, format * width);
			break;

		case FileType_JPG:
			stbi_write_jpg(filename.c_str(), width, height, format, bytes, jpgQuality);
			break;

		case FileType_BMP:
			stbi_write_bmp(filename.c_str(), width, height, format, bytes);
			break;

		case FileType_TGA:
			stbi_write_tga(filename.c_str(), width, height, format, bytes);
			break;
	}
}
