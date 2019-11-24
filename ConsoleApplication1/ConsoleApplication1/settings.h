#pragma once
#include "source.h"

class Settings {
public:
	int N;
	int height;
	int width;
	HPEN hPenCell;
	HBRUSH hBrushBackground;
	wchar_t* circleIconName;
	wchar_t* crestIconName;
	char* IOMethod;
	const wchar_t* name = _T("C:\\C++\\ConsoleApplication1\\ConsoleApplication1\\setting.inf");
	HPEN hPenFigure;
	HBRUSH hBrushFigure;

	explicit Settings(char* arg);
	
	~Settings();

	void setIOMethod(char* arg);

	void inputSettings(wchar_t* text);

	void outputSettings(std::wstringstream& wss);

	void loadSettings();

	void saveSettings();
};
