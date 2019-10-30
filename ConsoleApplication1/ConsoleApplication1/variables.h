#pragma once
#include <Windows.h>

struct Settings {
	int N;
	int height;
	int width;
	HPEN hPenCell;
	HBRUSH hBrushBackground;
	wchar_t* circleIconName;
	wchar_t* crestIconName;
};

struct Image {
	int height;
	int width;
	HBITMAP hBuffer;
};

struct Grid {
	bool* isFilled;
	int* imageNumber;
};