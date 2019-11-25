#pragma once
#include "windows.h"
#include <atomic>

struct Image {
	int height;
	int width;
	HBITMAP hBuffer;
};

struct Cell {
	std::atomic_bool isFilled;
	std::atomic_int imageNumber;
};