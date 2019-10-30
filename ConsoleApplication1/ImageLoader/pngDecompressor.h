#pragma once

#include <cstdlib>
#include "png.h"

#ifdef PNGDECOMPRESSOR_EXPORTS
#define PNGDECOMPRESSOR_API __declspec(dllexport)
#else
#define PNGDECOMPRESSOR_API __declspec(dllimport)
#endif

extern "C" PNGDECOMPRESSOR_API unsigned char* readPngFile(char* filename, int& height, int& width);