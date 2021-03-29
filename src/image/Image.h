#ifndef IMAGE_H
#define IMAGE_H

#include <string>

enum ImageFormat {
	Format_Invalid,
	Format_Grey8,
	Format_AlphaGrey16,
	Format_RGB24,
	Format_ARGB32
};

enum ImageFileType {
	FileType_Auto,
	FileType_PNG,
	FileType_JPG,
	FileType_BMP,
	FileType_TGA
};

class Image {
public:
	/// If <code>desiredFormat</code> is not <code>Format_Invalid</code> then the image will be loaded with the format specified
	Image(const std::string& filename, ImageFormat format = Format_Invalid);
	~Image();

	void Save(std::string filename, ImageFileType fileType = FileType_Auto, int jpgQuality = 80);

	/// If <code>desiredFormat</code> is not <code>Format_Invalid</code> then the image will be loaded with the format specified
	static uint8_t* LoadImage(const std::string& filename, int* width, int* height, ImageFormat* format, ImageFormat desiredFormat = Format_Invalid);
	static void FreeImage(uint8_t* bytes);
	/// <code>jpgQuality</code> is between 1 and 100 (inclusive)
	static void SaveImage(std::string filename, uint8_t* bytes, int width, int height, ImageFormat format, ImageFileType fileType = FileType_Auto, int jpgQuality = 80);

public:
	int m_Width;
	int m_Height;
	ImageFormat m_Format;
	uint8_t* m_Bytes;
};

#endif // IMAGE_H
