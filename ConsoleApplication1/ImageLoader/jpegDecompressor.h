#pragma once

#include "jpeglib.h"
#include <csetjmp>

#ifdef JPEGDECOMPRESSOR_EXPORTS
#define JPEGDECOMPRESSOR_API __declspec(dllexport)
#else
#define JPEGDECOMPRESSOR_API __declspec(dllimport)
#endif

struct Image {
	int nWidth;
	int nHeight;
	UINT nPlanes;
	UINT nBitCount;
    unsigned char** lpBits;
};

extern "C" JPEGDECOMPRESSOR_API unsigned char* readJpegFile(const char* filename, int& height, int& width);