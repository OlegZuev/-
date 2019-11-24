#pragma once
#include <windows.h>

struct Image {
	int height;
	int width;
	HBITMAP hBuffer;
};

struct Animation {
	Image* images;
	int size;
	std::atomic_int current;
};

struct Cell {
	std::atomic_bool isFilled;
	std::atomic_int imageNumber;
};

struct DrawBoardParam {
	HWND wnd;
	Settings* settings;
	Image* images;
};