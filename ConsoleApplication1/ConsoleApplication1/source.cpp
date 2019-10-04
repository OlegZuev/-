#include "source.h"

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("MyWindowName");
const int SHUTDOWN_WINDOW = 1;
const int RUN_NOTEPAD = 2;
const int CHANGE_COLOR = 3;

bool** board;

HPEN hPenCircle;
HBRUSH hBrushCircle;
COLORREF color;

Settings settings;

void runEditor() {
	STARTUPINFO startUpInfo;
	ZeroMemory(&startUpInfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION processInfo;
	CreateProcess(_T("C:\\Program Files\\Notepad++\\Notepad++.exe"), nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &startUpInfo, &processInfo);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

void cellClicked(HWND wnd, int x, int y) {
	int column = x / ((double)settings.width / settings.N);
	int row = y / ((double)settings.height / settings.N);
	board[row][column] ^= true;
	InvalidateRect(wnd, nullptr, true);
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
		DeleteObject(settings.hPenCell);
		DeleteObject(hPenCircle);
		DeleteObject(hBrushCircle);
		DeleteObject(settings.hBrushBackground);
		PostQuitMessage(0); //Код возврата приложения
		return 0;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(wnd, &ps);

		RECT rect;
		ZeroMemory(&rect, sizeof(RECT));
		GetClientRect(wnd, &rect);

		HPEN hOldPen = (HPEN)SelectObject(hdc, settings.hPenCell);

		double height = rect.bottom;
		double width = rect.right;

		for (int i = 1; i < settings.N; i++) {
			double x = width / settings.N * i;
			MoveToEx(hdc, x, 0, nullptr);
			LineTo(hdc, x, height);

			double y = height / settings.N * i;
			MoveToEx(hdc, 0, y, nullptr);
			LineTo(hdc, width, y);
		}

		SelectObject(hdc, hPenCircle);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrushCircle);

		for (int i = 0; i < settings.N; i++) {
			for (int j = 0; j < settings.N; j++) {
				if (board[j][i]) {
					double left = i * width / settings.N + width / settings.N * 0.2;
					double top = j * height / settings.N + height / settings.N * 0.2;
					double right = width / settings.N * 0.6;
					double bottom = height / settings.N * 0.6;
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
			std::random_device rd;
			std::mt19937 generator(rd());
 			std::uniform_int_distribution<DWORD> dist(0, 16777215);
		    color = dist(generator);
			HBRUSH hBrushRandom = CreateSolidBrush(color);
			SetClassLongPtr(wnd, GCLP_HBRBACKGROUND, (LONG)hBrushRandom);
			DeleteObject(settings.hBrushBackground);
			settings.hBrushBackground = hBrushRandom;
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
		settings.width = rect.right;
		settings.height = rect.bottom;
		break;
	}
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}



int main(int argc, char* argv[]) {
	HINSTANCE hThisInstance = GetModuleHandle(nullptr);

	loadSettings(settings, argv[1]);
	initBoard(settings, board);

	hPenCircle = CreatePen(PS_SOLID, 5, RGB(255, 200, 30));
	hBrushCircle = CreateSolidBrush(RGB(255, 200, 30));

	WNDCLASSEX wincl; //WNDCLASSEX нужно использовать
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.lpfnWndProc = WinProc; //Свой обработчик
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hThisInstance; //Ссылка на хандлер
	wincl.hIcon = LoadIcon(hThisInstance, settings.iconName);
	wincl.hbrBackground = settings.hBrushBackground;
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
		settings.width,
		settings.height,
		HWND_DESKTOP,
		nullptr,
		hThisInstance,
		nullptr
	);
	
	if (wnd == nullptr) {
		return 0;
	}

	ShowWindow(wnd, SW_SHOW);

	//Обработчик событий
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

	saveSettings(settings, argv[1]);
	DestroyWindow(wnd);
	UnregisterClass(clName, hThisInstance);
	delete[] settings.iconName;
	delete[] settings.iconType;
	for (int i = 0; i < settings.N; ++i) {
		delete[] board[i];
	}
	delete[] board;

	return msg.lParam;
}