#include "iosettings.h"

void inputSettings(Settings& settings, wchar_t* text) {
	std::wstringstream wss;
	COLORREF color;
	wss << text;
	wss >> settings.N >> settings.width >> settings.height >> color;
	settings.hBrushBackground = CreateSolidBrush(color);
	int iStyle, cWidth;
	wss >> iStyle >> cWidth >> color;
	settings.hPenCell = CreatePen(iStyle, cWidth, color);
	std::wstring buff;
	wss >> buff;
	settings.iconName = wstringConvertToWChar_t(buff);
	wss >> buff;
	settings.iconType = wstringConvertToWChar_t(buff);
}

void outputSettings(Settings& settings, std::wstringstream& wss) {
	const wchar_t divider[3] = _T("\r\n");
	wss << _T('\xFEFF') << settings.N << divider << settings.width << " " << settings.height << divider;
	LOGBRUSH iBrush;
	GetObject(settings.hBrushBackground, sizeof(LOGBRUSH), &iBrush);
	wss << iBrush.lbColor << divider;
	LOGPEN iPen;
	GetObject(settings.hPenCell, sizeof(LOGPEN), &iPen);
	wss << iPen.lopnStyle << " " << iPen.lopnWidth.x << " " << iPen.lopnColor << divider << settings.iconName << " " << settings.iconType;
}

void loadSettings(Settings& settings, char* arg) {
	const wchar_t* name = _T("setting.inf");
	int id = strtod(arg, nullptr);
	switch (id) {
	case 0:
		loadSettingsWinAPI(settings, name);
		break;
	case 1:
		loadSettingsMapping(settings, name);
		break;
	case 2:
		loadSettingsStream(settings, name);
		break;
	default:
		loadSettingsOpen(settings, name);
		break;
	}
}

void saveSettings(Settings& settings, char* arg) {
	const wchar_t* name = _T("setting.inf");
	int id = strtod(arg, nullptr);
	switch (id) {
	case 0:
		saveSettingsWinAPI(settings, name);
		break;
	case 1:
		saveSettingsMapping(settings, name);
		break;
	case 2:
		saveSettingsStream(settings, name);
		break;
    default:
		saveSettingsOpen(settings, name);
		break;
	}
}