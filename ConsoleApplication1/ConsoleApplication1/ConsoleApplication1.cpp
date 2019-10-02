#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <tchar.h>
#include <windowsx.h>
#include <string>

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("MyWindowName");
int height;
int width;
const wchar_t* iconName;
const wchar_t* iconType;
int N;
const int SHUTDOWN_WINDOW = 1;
const int RUN_NOTEPAD = 2;
const int CHANGE_COLOR = 3;
HPEN hPenCell;
HPEN hPenCircle;
HBRUSH hBrushBackground;
HBRUSH hBrushCircle;
bool** board;

int parseInt(const char text[], int& currentPointer, int size);

wchar_t* parseWChar_t(const char text[], int& currentPointer, int size);

BOOL WriteFileInt(_In_ HANDLE hFile, _In_ int number);

BOOL WriteFileWChar_t(_In_ HANDLE hFile, _In_ const wchar_t* msg);

void runEditor() {
	STARTUPINFO startUpInfo;
	ZeroMemory(&startUpInfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION processInfo;
	CreateProcess(_T("C:\\Program Files\\Notepad++\\Notepad++.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startUpInfo, &processInfo);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

void cellClicked(HWND wnd, int x, int y) {
	RECT rect = { 0 };
	GetClientRect(wnd, &rect);
	int column = x / ((double)rect.right / N);
	int row = y / ((double)rect.bottom / N);
	board[row][column] ^= true;
	InvalidateRect(wnd, NULL, true);
}

//Свой обработчик
LRESULT CALLBACK WinProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN: {
		cellClicked(wnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	case WM_DESTROY: {
		UnregisterHotKey(wnd, SHUTDOWN_WINDOW);
		UnregisterHotKey(wnd, CHANGE_COLOR);
		UnregisterHotKey(wnd, RUN_NOTEPAD);
		DeleteObject(hPenCell);
		DeleteObject(hPenCircle);
		DeleteObject(hBrushCircle);
		DeleteObject(hBrushBackground);
		PostQuitMessage(0); //Код возврата приложения
		return 0;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(wnd, &ps);

		RECT rect = {0};
		GetClientRect(wnd, &rect);

		HPEN hOldPen = (HPEN)SelectObject(hdc, hPenCell);

		double height = rect.bottom;
		double width = rect.right;

		for (int i = 1; i < N; i++) {
			double x = width / N * i;
			MoveToEx(hdc, x, 0, NULL);
			LineTo(hdc, x, height);

			double y = height / N * i;
			MoveToEx(hdc, 0, y, NULL);
			LineTo(hdc, width, y);
		}

		SelectObject(hdc, hPenCircle);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrushCircle);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[j][i]) {
					double left = i * width / N+ width / N * 0.2;
					double top = j * height / N + height / N * 0.2;
					double right = width / N * 0.6;
					double bottom = height / N * 0.6;
					Ellipse(hdc, left, top, left + right, top + bottom);
				}
			}
		}

		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);
		EndPaint(wnd, &ps);
		break;
	}
	case WM_HOTKEY: {
		switch (wParam) {
		case SHUTDOWN_WINDOW: {
			PostQuitMessage(0);
			return 0;
		}
		case RUN_NOTEPAD: {
			runEditor();
			break;
		}
		case CHANGE_COLOR: {
			int r = rand() % 256;
			int g = rand() % 256;
			int b = rand() % 256;
			HBRUSH hBrushRandom = CreateSolidBrush(RGB(r, g, b));
			SetClassLongPtr(wnd, GCLP_HBRBACKGROUND, (LONG)hBrushRandom);
			DeleteObject(hBrushBackground);
			hBrushBackground = hBrushRandom;
			InvalidateRect(wnd, NULL, true);
			break;
		}
		}
		break;
	}
	case WM_SETFOCUS: {
		RegisterHotKey(wnd, SHUTDOWN_WINDOW, NULL, VK_ESCAPE);
		RegisterHotKey(wnd, SHUTDOWN_WINDOW, MOD_CONTROL, 'Q');
		RegisterHotKey(wnd, RUN_NOTEPAD, MOD_SHIFT | MOD_NOREPEAT, 'C');
		RegisterHotKey(wnd, CHANGE_COLOR, NULL, VK_RETURN);
		break;
	}
	case WM_KILLFOCUS: {
		UnregisterHotKey(wnd, SHUTDOWN_WINDOW);
		UnregisterHotKey(wnd, CHANGE_COLOR);
		UnregisterHotKey(wnd, RUN_NOTEPAD);
		break;
	}
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

void loadSettings() {
	const wchar_t* name = _T("setting.inf");

	HANDLE file = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int fileSize = GetFileSize(file, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
	}
	char text[512];
	int currentPointer = 0;

	if (!ReadFile(file, text, fileSize, NULL, NULL)) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
	}
	N = parseInt(text, currentPointer, fileSize);
	width = parseInt(text, currentPointer, fileSize);
	height = parseInt(text, currentPointer, fileSize);
	int r = parseInt(text, currentPointer, fileSize);
	int g = parseInt(text, currentPointer, fileSize);
	int b = parseInt(text, currentPointer, fileSize);
	hBrushBackground = CreateSolidBrush(RGB(r, g, b));
	int iStyle = parseInt(text, currentPointer, fileSize);
	int cWidth = parseInt(text, currentPointer, fileSize);
	r = parseInt(text, currentPointer, fileSize);
	g = parseInt(text, currentPointer, fileSize);
	b = parseInt(text, currentPointer, fileSize);
	hPenCell = CreatePen(iStyle, cWidth, RGB(r, g, b));
	iconName = parseWChar_t(text, currentPointer, fileSize);
	iconType = parseWChar_t(text, currentPointer, fileSize);
	CloseHandle(file);
}

void saveSettings() {
	const wchar_t* name = _T("setting.inf");

	HANDLE file = CreateFileW(name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int fileSize = GetFileSize(file, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
	}

	int currentPointer = 0;
	char tempChar[128];
	std::string temp = std::to_string(N);
	WriteFileInt(file, N);
	WriteFile(file, "\r\n", 2, NULL, NULL);
	WriteFileInt(file, width);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, height);
	WriteFile(file, "\r\n", 2, NULL, NULL);
	LOGBRUSH iBrush;
	GetObject(hBrushBackground, sizeof(LOGBRUSH), &iBrush);
	int r = GetRValue(iBrush.lbColor);
	int g = GetGValue(iBrush.lbColor);
	int b = GetBValue(iBrush.lbColor);
	WriteFileInt(file, r);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, g);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, b);
	WriteFile(file, "\r\n", 2, NULL, NULL);
	LOGPEN iPen;
	GetObject(hPenCell, sizeof(LOGPEN), &iPen);
	int iStyle = iPen.lopnStyle;
	int cWidth = iPen.lopnWidth.x;
    r = GetRValue(iPen.lopnColor);
    g = GetGValue(iPen.lopnColor);
    b = GetBValue(iPen.lopnColor);
	WriteFileInt(file, iStyle);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, cWidth);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, r);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, g);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileInt(file, b);
	WriteFile(file, "\r\n", 2, NULL, NULL);
	WriteFileWChar_t(file, iconName);
	WriteFile(file, " ", 1, NULL, NULL);
	WriteFileWChar_t(file, iconType);
	CloseHandle(file);
}

BOOL WriteFileInt(_In_ HANDLE hFile, _In_ int number) {
	std::string temp = std::to_string(number);
	return WriteFile(hFile, temp.c_str(), temp.size(), NULL, NULL);
}

BOOL WriteFileWChar_t(_In_ HANDLE hFile, _In_ const wchar_t* msg) {
	size_t length = std::wcslen(msg) + 1;
	char* converted = new char[length];
	size_t outSize;
    wcstombs_s(&outSize, converted, length,  msg, length - 1);
	BOOL result = WriteFile(hFile, converted, length - 1, NULL, NULL);
	delete[] converted;
	return result;
}

int parseInt(const char text[], int& currentPointer, int size) {
	int variable = 0;
	int i = currentPointer;
	for (; i < size; i++) {
		if (text[i] == ' ') {
			i++;
			break;
		}
		if (text[i] == '\r') {
			i += 2;
			break;
		}
		if (i == currentPointer) {
			variable = text[i] - '0';
		} else {
			variable = variable * 10 + text[i] - '0';
		}
	}
	currentPointer = i;
	return variable;
}

wchar_t* parseWChar_t(const char text[], int& currentPointer, int size) {
	int i = currentPointer;
	for (; i < size; i++) {
		if (text[i] == ' ') {
			break;
		}
		if (text[i] == '\r') {
			break;
		}
	}
	size_t length = i - currentPointer;
	
	if (length > 0) {
		wchar_t* variable = new wchar_t[length + 1];
		char* temp = new char[length];
	    i = currentPointer;
		for (; i < size; i++) {
			if (text[i] == ' ') {
				break;
			}
			if (text[i] == '\r') {
				break;
			}
			temp[i - currentPointer] = text[i];
		}
		size_t outSize;
		mbstowcs_s(&outSize, variable, length + 1, temp, length);
		if (text[length - 1] == '\r') {
			i++;
		}
		currentPointer = ++i;
		return variable;
	}
	return NULL;
}

void initBoard() {
	board = new bool*[N];
	for (int i = 0; i < N; i++) {
		board[i] = new bool[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; ++j) {
			board[i][j] = false;
		}
	}
}

int main() {
	HINSTANCE hThisInstance = GetModuleHandle(NULL);

	loadSettings();
	initBoard();

	//hPenCell = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	hPenCircle = CreatePen(PS_SOLID, 5, RGB(255, 200, 30));
	hBrushCircle = CreateSolidBrush(RGB(255, 200, 30));
	//hBrushBackground = CreateSolidBrush(RGB(0, 0, 255));

	WNDCLASSEX wincl; //WNDCLASSEX нужно использовать
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.lpfnWndProc = WinProc; //Свой обработчик
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hThisInstance; //Ссылка на хандлер
	wincl.hIcon = LoadIcon(hThisInstance, iconName);
	wincl.hbrBackground = hBrushBackground;
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.lpszClassName = clName;
	wincl.hIconSm = NULL;

	if (!RegisterClassEx(&wincl)) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
		return error;
	}

	HWND wnd = CreateWindowEx(
		0,
		clName,
		clWinName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		HWND_DESKTOP,
		NULL,
		hThisInstance,
		NULL
	);
	
	if (wnd == NULL) {
		return 0;
	}

	ShowWindow(wnd, SW_SHOW);

	//Обработчик событий
	BOOL bOk = FALSE;
	MSG msg;

	while ((bOk = GetMessage(&msg, NULL, 0, 0))) {
		if (bOk < 0) {
			DWORD error = GetLastError();
			printf("Something bad has happen with GetMessage! Error %lu\n", error);
			return error;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	saveSettings();
	DestroyWindow(wnd);
	UnregisterClass(clName, hThisInstance);

	return msg.lParam;
}

