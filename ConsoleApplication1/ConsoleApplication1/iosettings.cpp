#include "iosettings.h"

const wchar_t* name = _T("C:\\C++\\ConsoleApplication1\\ConsoleApplication1\\setting.inf");
char* IOMethod;

void setIOMethod(char* arg) {
	IOMethod = arg;
}

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
	settings.circleIconName = wstringConvertToWChar_t(buff);
	wss >> buff;
	settings.crestIconName = wstringConvertToWChar_t(buff);
}

void outputSettings(Settings& settings, std::wstringstream& wss) {
	const wchar_t divider[3] = _T("\r\n");
	wss << _T('\xFEFF') << settings.N << divider << settings.width << " " << settings.height << divider;
	LOGBRUSH iBrush;
	GetObject(settings.hBrushBackground, sizeof(LOGBRUSH), &iBrush);
	wss << iBrush.lbColor << divider;
	LOGPEN iPen;
	GetObject(settings.hPenCell, sizeof(LOGPEN), &iPen);
	wss << iPen.lopnStyle << " " << iPen.lopnWidth.x << " " << iPen.lopnColor << divider << settings.circleIconName << divider << settings.crestIconName;
}

void loadSettings(Settings& settings) {
	int id = 0;
	if (IOMethod != nullptr) {
		id = (int)strtod(IOMethod, nullptr);
	}
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

void saveSettings(Settings& settings) {
	int id = 0;
	if (IOMethod != nullptr) {
		id = (int)strtod(IOMethod, nullptr);
	}
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

void inputGrid(Grid** board, int size, std::wstringstream& wss) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			wss >> *board[i][j].isFilled >> *board[i][j].imageNumber;
		}
	}
}

void inputGridInStream(Grid** board, int size, wchar_t* file) {
	std::wstringstream wss;
	wss << file;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			wss >> *board[i][j].isFilled >> *board[i][j].imageNumber;
		}
	}
}

void outputGridInStream(Grid** board, int size, std::wstringstream& wss) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			wss << board[i][j].isFilled << " " << board[i][j].imageNumber << " ";
		}
	}
}