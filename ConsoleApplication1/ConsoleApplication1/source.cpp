#include "source.h"

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("MyWindowName");
const int SHUTDOWN_WINDOW = 1;
const int RUN_NOTEPAD = 2;
const int CHANGE_COLOR = 3;

Grid** board;

HPEN hPenCircle;
HBRUSH hBrushCircle;
COLORREF color;
Image image[3];

Settings settings;\

void runEditor() {
	STARTUPINFO startUpInfo;
	ZeroMemory(&startUpInfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION processInfo;
	CreateProcess(_T("C:\\Program Files\\Notepad++\\Notepad++.exe"), nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &startUpInfo, &processInfo);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

void cellClicked(HWND wnd, int x, int y) {
	int column = (int)(x / ((double)settings.width / settings.N));
	int row = (int)(y / ((double)settings.height / settings.N));
	board[row][column].isFilled ^= true;
	if (!board[row][column].isFilled) {
		board[row][column].imageNumber = 0;
	}
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
		saveSettings(settings);
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
			int x = (int)(width / settings.N * i);
			MoveToEx(hdc, x, 0, nullptr);
			LineTo(hdc, x, (int)height);

			int y = (int)(height / settings.N * i);
			MoveToEx(hdc, 0, y, nullptr);
			LineTo(hdc, (int)width, y);
		}

		SelectObject(hdc, hPenCircle);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrushCircle);

		for (int i = 0; i < settings.N; i++) {
			for (int j = 0; j < settings.N; j++) {
				if (board[j][i].isFilled) {
					const int left = (int)(i * width / settings.N + width / settings.N * 0.2);
					const int top = (int)(j * height / settings.N + height / settings.N * 0.2);
					const int right = (int)(width / settings.N * 0.6);
					const int bottom = (int)(height / settings.N * 0.6);
					if (board[j][i].imageNumber == 0) {
						std::random_device rd;
						std::mt19937 generator(rd());
						std::uniform_int_distribution<int> dist(1, 2);
						board[j][i].imageNumber = dist(generator);
					}
					int index = board[j][i].imageNumber;
					HDC tempDC = CreateCompatibleDC(hdc);
				    auto oldImage = SelectObject(tempDC, image[index].hBuffer);
					BLENDFUNCTION blendFn = {};
					blendFn.BlendOp = AC_SRC_OVER;
					blendFn.BlendFlags = 0;
					blendFn.SourceConstantAlpha = 255;
					blendFn.AlphaFormat = AC_SRC_ALPHA;
					bool result = AlphaBlend(hdc, left, top, right, bottom, tempDC, 0, 0, image[index].width, image[index].height, blendFn);
					//bool result = TransparentBlt(hdc, left, top, right, bottom, tempDC, 0, 0, image[index].width, image[index].height, RGB(0, 0, 0));
					if (!result) {
						if (index == 1) {
							Ellipse(hdc, left, top, left + right, top + bottom);
						}
						if (index == 2) {
							Crest(hdc, left, top, left + right, top + bottom);
						}
					}
					SelectObject(tempDC, oldImage);
					DeleteDC(tempDC);
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

	setIOMethod(argv[1]);
	loadSettings(settings);
	initBoard(settings, board);
	
	image[1] = readPngImage(settings.circleIconName);	
	image[2] = readJpegImage(settings.crestIconName);

	hPenCircle = CreatePen(PS_SOLID, 5, RGB(255, 200, 30));
	hBrushCircle = CreateSolidBrush(RGB(255, 200, 30));

	WNDCLASSEX wincl; //WNDCLASSEX нужно использовать
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.lpfnWndProc = WinProc; //Свой обработчик
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hThisInstance; //Ссылка на хандлер
	wincl.hIcon = LoadIcon(hThisInstance, settings.circleIconName);
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

	DestroyWindow(wnd);
	UnregisterClass(clName, hThisInstance);
	delete[] settings.circleIconName;
	delete[] settings.crestIconName;
	for (int i = 0; i < settings.N; ++i) {
		delete[] board[i];
	}
	delete[] board;
	DeleteObject(image[1].hBuffer);
	DeleteObject(image[2].hBuffer);

	return msg.lParam;
}