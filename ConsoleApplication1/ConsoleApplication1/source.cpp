#include "source.h"
#include "grid.h"
#include "utilities.h"

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("MyWindowName");
const int SHUTDOWN_WINDOW = 1;
const int RUN_NOTEPAD = 2;
const int CHANGE_COLOR = 3;
const int FREEZE_DRAW_BOARD_THREAD = 4;
bool threadFrozen = false;

UINT WM_CELLCLICKED = RegisterWindowMessageA("WM_CELLCLICKED");

Grid* grid;

Image image[3];

Animation background;

Settings* settings;

std::atomic_bool drawBoardFlag;

std::future<void> result;

HANDLE workingSemaphore;

void runEditor() {
	STARTUPINFO startUpInfo;
	ZeroMemory(&startUpInfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION processInfo;
	CreateProcess(_T("C:\\Program Files\\Notepad++\\Notepad++.exe"), nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &startUpInfo, &processInfo);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

//Свой обработчик
LRESULT CALLBACK WinProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN: {
		grid->cellClicked(settings, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	case WM_CREATE: {
		WM_CELLCLICKED = RegisterWindowMessageA("WM_CELLCLICKED");
		grid = new Grid(settings->N);
		drawBoardFlag = true;
		std::vector<std::string> filenames;
		background.size = 40;
		background.current = 0;
		filenames.reserve(background.size);
		for (int i = 0; i < background.size; ++i) {
			filenames.push_back("Animation\\layer (" + std::to_string(i + 1) + ").png");
		}		
		background.images = readPngImages(&filenames[0], background.size);
	    workingSemaphore = CreateSemaphoreA(nullptr, 1, 1, nullptr);
		result = std::async(std::launch::async, &Grid::drawBoard, grid, wnd, settings, image, std::ref(background), std::ref(drawBoardFlag), workingSemaphore);
		break;
	}
	case WM_DESTROY: {
		drawBoardFlag = false;
		result.get();
		delete settings;
		delete grid;
		UnregisterHotKey(wnd, SHUTDOWN_WINDOW);
		UnregisterHotKey(wnd, CHANGE_COLOR);
		UnregisterHotKey(wnd, RUN_NOTEPAD);
		PostQuitMessage(0); //Код возврата приложения
		return 0;
	}
	case WM_PAINT: {
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
		    COLORREF color = dist(generator);
			HBRUSH hBrushRandom = CreateSolidBrush(color);
			SetClassLongPtr(wnd, GCLP_HBRBACKGROUND, (LONG)hBrushRandom);
			DeleteObject(settings->hBrushBackground);
			settings->hBrushBackground = hBrushRandom;
			InvalidateRect(wnd, nullptr, true);
			break;
		}
		case FREEZE_DRAW_BOARD_THREAD: {
			if (!threadFrozen) {
				WaitForSingleObject(workingSemaphore, INFINITE);
				threadFrozen ^= true;
			} else {
				ReleaseSemaphore(workingSemaphore, 1, nullptr);
				threadFrozen ^= true;
			}
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
		RegisterHotKey(wnd, FREEZE_DRAW_BOARD_THREAD, NULL, VK_SPACE);
		break;
	}
	case WM_KILLFOCUS: {
		UnregisterHotKey(wnd, SHUTDOWN_WINDOW);
		UnregisterHotKey(wnd, CHANGE_COLOR);
		UnregisterHotKey(wnd, RUN_NOTEPAD);
		UnregisterHotKey(wnd, FREEZE_DRAW_BOARD_THREAD);
		break;
	}
	case WM_SIZE: {
		RECT rect;
		GetClientRect(wnd, &rect);
		settings->width = rect.right;
		settings->height = rect.bottom;
		break;
	}
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

int main(int argc, char* argv[]) {
	HINSTANCE hThisInstance = GetModuleHandle(nullptr);

	settings = new Settings(argv[1]);
	
	image[1] = readPngImage(settings->circleIconName);	
	image[2] = readJpegImage(settings->crestIconName);

	WNDCLASSEX wincl; //WNDCLASSEX нужно использовать
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.lpfnWndProc = WinProc; //Свой обработчик
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hThisInstance; //Ссылка на хандлер
	wincl.hIcon = nullptr;
	wincl.hbrBackground = settings->hBrushBackground;
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
		settings->width,
		settings->height,
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

	DeleteObject(image[1].hBuffer);
	DeleteObject(image[2].hBuffer);

	return msg.lParam;
}