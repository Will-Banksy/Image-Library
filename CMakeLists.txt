# Minimum required version of cmake
cmake_minimum_required(VERSION 3.5)

# ===

set(ProjectName "ILib")
set(ProjectVersion "1.0")
set(LibraryName "ilib")

set(CMakeFlags "")
set(CMakeDebugFlags "")

option(ILIB_STATIC "If true, compiles as a static library, else compiles as a shared library" OFF)

# ===

project("${ProjectName}" VERSION "${ProjectVersion}" LANGUAGES CXX C)

# Project root directory and the source directory src/
set(ProjectDir "${PROJECT_SOURCE_DIR}") # PROJECT_SOURCE_DIR is set by calls to project()
set(SourceDir "${ProjectDir}/src")

# ===

set(Libraries "") # Example: -lglfw -lGL -ldl

set(SourceFiles
	"${SourceDir}/image/Image.cpp"
)

set(HeaderFiles
	"${ProjectDir}/Stb-Image/stb_image.h"
	"${ProjectDir}/Stb-Image/stb_image_write.h"

	"${SourceDir}/image/Image.h"
)

# ===

set(CMAKE_CXX_FLAGS_DEBUG "${CMakeDebugFlags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMakeFlags}")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

if("${ILIB_STATIC}")
	add_library("${LibraryName}" STATIC "${SourceFiles}" "${HeaderFiles}")
else()
	add_library("${LibraryName}" SHARED "${SourceFiles}" "${HeaderFiles}")
endif()

target_include_directories("${LibraryName}" PRIVATE "${SourceDir}" "${ProjectDir}/Stb-Image")

target_link_libraries("${LibraryName}" PRIVATE "${Libraries}")

install(TARGETS ${LibraryName} DESTINATION "${CMAKE_INSTALL_LIBDIR}")