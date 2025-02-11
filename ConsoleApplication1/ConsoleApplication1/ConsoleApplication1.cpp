#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <tchar.h>
#include <windowsx.h>
#include <string>
#include <sstream>

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("MyWindowName");
int height;
int width;
wchar_t* iconName = new wchar_t[256];
wchar_t* iconType = new wchar_t[256];
int N;
const int SHUTDOWN_WINDOW = 1;
const int RUN_NOTEPAD = 2;
const int CHANGE_COLOR = 3;
HPEN hPenCell;
HPEN hPenCircle;
HBRUSH hBrushBackground;
HBRUSH hBrushCircle;
bool** board;

void runEditor() {
	STARTUPINFO startUpInfo;
	ZeroMemory(&startUpInfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION processInfo;
	CreateProcess(_T("C:\\Program Files\\Notepad++\\Notepad++.exe"), nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &startUpInfo, &processInfo);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

void cellClicked(HWND wnd, int x, int y) {
	int column = x / ((double)width / N);
	int row = y / ((double)height / N);
	board[row][column] ^= true;
	InvalidateRect(wnd, nullptr, true);
}

//���� ����������
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
		PostQuitMessage(0); //��� �������� ����������
		return 0;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(wnd, &ps);

		RECT rect;
		ZeroMemory(&rect, sizeof(RECT));
		GetClientRect(wnd, &rect);

		HPEN hOldPen = (HPEN)SelectObject(hdc, hPenCell);

		double height = rect.bottom;
		double width = rect.right;

		for (int i = 1; i < N; i++) {
			double x = width / N * i;
			MoveToEx(hdc, x, 0, nullptr);
			LineTo(hdc, x, height);

			double y = height / N * i;
			MoveToEx(hdc, 0, y, nullptr);
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
			InvalidateRect(wnd, nullptr, true);
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
	case WM_SIZE: {
		RECT rect;
		ZeroMemory(&rect, sizeof(RECT));
		GetClientRect(wnd, &rect);
		width = rect.right;
		height = rect.bottom;
		break;
	}
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

void loadSettings() {
	const wchar_t* name = _T("setting.inf");

	HANDLE file = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
	}

	int fileSize = GetFileSize(file, nullptr);
	char* text = new char[fileSize];
	ZeroMemory(text, sizeof(char) * fileSize);

	if (!ReadFile(file, text, fileSize, nullptr, nullptr)) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
	}
	CloseHandle(file);

	std::wstringstream wss;
	COLORREF color;
	wss << text;
	wss >> N >> width >> height >> color;
	hBrushBackground = CreateSolidBrush(color);
	int iStyle, cWidth;
	wss >> iStyle >> cWidth >> color;
	hPenCell = CreatePen(iStyle, cWidth, color);
	wss >> iconName >> iconType;
	delete[] text;
}

void saveSettings() {
	const wchar_t* name = _T("setting.inf");

	HANDLE file = CreateFileW(name, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
	}

	std::wstringstream wss;
	wss << N << "\r\n" << width << " " << height << "\r\n";
	LOGBRUSH iBrush;
	GetObject(hBrushBackground, sizeof(LOGBRUSH), &iBrush);
	wss << iBrush.lbColor << "\r\n";
	LOGPEN iPen;
	GetObject(hPenCell, sizeof(LOGPEN), &iPen);
	wss << iPen.lopnStyle << " " << iPen.lopnWidth.x << " " << iPen.lopnColor << "\r\n" << iconName << " " << iconType << "\r\n";
	char* text = new char[wss.str().length() + 1];
	size_t outSize;
	wcstombs_s(&outSize, text, wss.str().length() + 1, wss.str().c_str(), wss.str().length());
	WriteFile(file, text, wss.str().length(), nullptr, nullptr);
	CloseHandle(file);
	delete[] text;
}

void initBoard() {
	board = new bool*[N];
	for (int i = 0; i < N; i++) {
		board[i] = new bool[N];
		ZeroMemory(board[i], sizeof(bool) * N);
	}
}

int main() {
	HINSTANCE hThisInstance = GetModuleHandle(nullptr);

	loadSettings();
	initBoard();

	//hPenCell = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	hPenCircle = CreatePen(PS_SOLID, 5, RGB(255, 200, 30));
	hBrushCircle = CreateSolidBrush(RGB(255, 200, 30));
	//hBrushBackground = CreateSolidBrush(RGB(0, 0, 255));

	WNDCLASSEX wincl; //WNDCLASSEX ����� ������������
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.lpfnWndProc = WinProc; //���� ����������
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hThisInstance; //������ �� �������
	wincl.hIcon = LoadIcon(hThisInstance, iconName);
	wincl.hbrBackground = hBrushBackground;
	wincl.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wincl.lpszMenuName = nullptr;
	wincl.lpszClassName = clName;
	wincl.hIconSm = nullptr;

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
		nullptr,
		hThisInstance,
		nullptr
	);
	
	if (wnd == nullptr) {
		return 0;
	}

	ShowWindow(wnd, SW_SHOW);

	//���������� �������
	BOOL bOk = FALSE;
	MSG msg;

	while ((bOk = GetMessage(&msg, nullptr, 0, 0))) {
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
	delete[] iconName;
	delete[] iconType;
	for (int i = 0; i < N; ++i) {
		delete[] board[i];
	}
	delete[] board;

	return msg.lParam;
}