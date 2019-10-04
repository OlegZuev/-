#pragma once
#include <Windows.h>

struct Settings {
	int N;
	int height;
	int width;
	HPEN hPenCell;
	HBRUSH hBrushBackground;
	wchar_t* iconName;
	wchar_t* iconType;
};