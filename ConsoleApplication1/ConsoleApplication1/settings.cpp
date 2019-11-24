#include "settings.h"
#include "utilities.h"
#include "fmapping.h"
#include "fwinapi.h"
#include "myfopen.h"
#include "myfstream.h"

Settings::Settings(char* arg) {  // NOLINT(hicpp-member-init)
	setIOMethod(arg);
	loadSettings();
	hPenFigure = CreatePen(PS_SOLID, 5, RGB(255, 200, 30));
	hBrushFigure = CreateSolidBrush(RGB(255, 200, 30));
}

Settings::~Settings() {
	saveSettings();
	DeleteObject(hPenCell);
	DeleteObject(hPenFigure);
	DeleteObject(hBrushFigure);
	DeleteObject(hBrushBackground);
	delete[] circleIconName;
	delete[] crestIconName;
}

void Settings::setIOMethod(char* arg) {
	IOMethod = arg;
}

void Settings::inputSettings(wchar_t* text) {
	std::wstringstream wss;
	COLORREF color;
	wss << text;
	wss >> N >> width >> height >> color;
	hBrushBackground = CreateSolidBrush(color);
	int iStyle, cWidth;
	wss >> iStyle >> cWidth >> color;
	hPenCell = CreatePen(iStyle, cWidth, color);
	std::wstring buff;
	wss >> buff;
	circleIconName = wstringConvertToWChar_t(buff);
	wss >> buff;
	crestIconName = wstringConvertToWChar_t(buff);
}

void Settings::outputSettings(std::wstringstream& wss) {
	const wchar_t divider[3] = _T("\r\n");
	wss << _T('\xFEFF') << N << divider << width << " " << height << divider;
	LOGBRUSH iBrush;
	GetObject(hBrushBackground, sizeof(LOGBRUSH), &iBrush);
	wss << iBrush.lbColor << divider;
	LOGPEN iPen;
	GetObject(hPenCell, sizeof(LOGPEN), &iPen);
	wss << iPen.lopnStyle << " " << iPen.lopnWidth.x << " " << iPen.lopnColor << divider << circleIconName << divider << crestIconName;
}

void Settings::loadSettings() {
	int id = 0;
	if (IOMethod != nullptr) {
		id = (int)strtod(IOMethod, nullptr);
	}
	switch (id) {
	case 0:
		loadSettingsWinAPI(this, name);
		break;
	case 1:
		loadSettingsMapping(this, name);
		break;
	case 2:
		loadSettingsStream(this, name);
		break;
	default:
		loadSettingsOpen(this, name);
		break;
	}
}

void Settings::saveSettings() {
	int id = 0;
	if (IOMethod != nullptr) {
		id = (int)strtod(IOMethod, nullptr);
	}
	switch (id) {
	case 0:
		saveSettingsWinAPI(this, name);
		break;
	case 1:
		saveSettingsMapping(this, name);
		break;
	case 2:
		saveSettingsStream(this, name);
		break;
	default:
		saveSettingsOpen(this, name);
		break;
	}
}
