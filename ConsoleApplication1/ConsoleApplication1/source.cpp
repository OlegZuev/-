#include "source.h"
#include "grid.h"
#include "utilities.h"
#include "animation.h"

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("Noughts and Crosses");
const int SHUTDOWN_WINDOW = 1;
const int RUN_NOTEPAD = 2;
const int CHANGE_COLOR = 3;
const int FREEZE_DRAW_BOARD_THREAD = 4;
const int IDLE_THREAD_PRIORITY = 5;
const int LOWEST_THREAD_PRIORITY = 6;
const int BELOW_NORMAL_THREAD_PRIORITY = 7;
const int NORMAL_THREAD_PRIORITY = 8;
const int ABOVE_NORMAL_THREAD_PRIORITY = 9;
const int HIGHEST_THREAD_PRIORITY = 10;
const int TIME_CRITICAL_THREAD_PRIORITY = 11;
bool threadFrozen = false;

UINT WM_RESTART = RegisterWindowMessageA("WM_RESTART");
UINT MY_WM_DESTROY = RegisterWindowMessageA("MY_WM_DESTROY");

Grid* grid;

Image image[3];

Animation* background;

Settings* settings;

std::atomic_bool drawBoardFlag;

std::thread drawBoardThread;

HANDLE workingSemaphore;
HANDLE numberPlayersSemaphore;

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
	if (msg == WM_RESTART) {
		grid->clearBoard();
		return 0;
	}
	if (msg == MY_WM_DESTROY) {
		PostQuitMessage(0);
	}
	switch (msg) {
	case WM_LBUTTONDOWN: {
		grid->cellClicked(wnd, settings, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	case WM_CREATE: {
		grid = new Grid(settings->N);
		drawBoardFlag = true;
		std::vector<std::string> filenames;
		background = new Animation("Animation\\layer", "png", 40);
	    workingSemaphore = CreateSemaphoreA(nullptr, 1, 1, nullptr);
		numberPlayersSemaphore = CreateSemaphoreA(nullptr, 2, 2, "numberPlayers");
		if (WaitForSingleObject(numberPlayersSemaphore, 0) == WAIT_TIMEOUT) {
			MessageBoxA(wnd, "Exceeded the number of players.", "Error", MB_OK);
			PostQuitMessage(0);
		}
		drawBoardThread = std::thread(&Grid::drawBoard, grid, wnd, settings, image, std::ref(background), std::ref(drawBoardFlag), workingSemaphore);
		break;
	}
	case WM_DESTROY: {
		drawBoardFlag = false;
		ReleaseSemaphore(numberPlayersSemaphore, 1, nullptr);
		ReleaseSemaphore(workingSemaphore, 1, nullptr);
		drawBoardThread.join();
		delete settings;
		delete grid;
		CloseHandle(workingSemaphore);
		CloseHandle(numberPlayersSemaphore);
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
		case IDLE_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_IDLE);
			std::cout << res << " " << THREAD_PRIORITY_IDLE << std::endl;
			break;
		}
		case LOWEST_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_LOWEST);
			std::cout << res << " " << THREAD_PRIORITY_LOWEST << std::endl;
			break;
		}
		case BELOW_NORMAL_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_BELOW_NORMAL);
			std::cout << res << " " << THREAD_PRIORITY_BELOW_NORMAL << std::endl;
			break;
		}
		case NORMAL_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_NORMAL);
			std::cout << res << " " << THREAD_PRIORITY_NORMAL << std::endl;
			break;
		}
		case ABOVE_NORMAL_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_ABOVE_NORMAL);
			std::cout << res << " " << THREAD_PRIORITY_ABOVE_NORMAL << std::endl;
			break;
		}
		case HIGHEST_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_HIGHEST);
			std::cout << res << " " << THREAD_PRIORITY_HIGHEST << std::endl;
			break;
		}
		case TIME_CRITICAL_THREAD_PRIORITY: {
			bool res = SetThreadPriority(drawBoardThread.native_handle(), THREAD_PRIORITY_TIME_CRITICAL);
			std::cout << res << " " << THREAD_PRIORITY_TIME_CRITICAL << std::endl;
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
		RegisterHotKey(wnd, IDLE_THREAD_PRIORITY, NULL, '1');
		RegisterHotKey(wnd, LOWEST_THREAD_PRIORITY, NULL, '2');
		RegisterHotKey(wnd, BELOW_NORMAL_THREAD_PRIORITY, NULL, '3');
		RegisterHotKey(wnd, NORMAL_THREAD_PRIORITY, NULL, '4');
		RegisterHotKey(wnd, ABOVE_NORMAL_THREAD_PRIORITY, NULL, '5');
		RegisterHotKey(wnd, HIGHEST_THREAD_PRIORITY, NULL, '6');
		RegisterHotKey(wnd, TIME_CRITICAL_THREAD_PRIORITY, NULL, '7');
		break;
	}
	case WM_KILLFOCUS: {
		UnregisterHotKey(wnd, SHUTDOWN_WINDOW);
		UnregisterHotKey(wnd, CHANGE_COLOR);
		UnregisterHotKey(wnd, RUN_NOTEPAD);
		UnregisterHotKey(wnd, FREEZE_DRAW_BOARD_THREAD);
		UnregisterHotKey(wnd, IDLE_THREAD_PRIORITY);
		UnregisterHotKey(wnd, LOWEST_THREAD_PRIORITY);
		UnregisterHotKey(wnd, BELOW_NORMAL_THREAD_PRIORITY);
		UnregisterHotKey(wnd, NORMAL_THREAD_PRIORITY);
		UnregisterHotKey(wnd, ABOVE_NORMAL_THREAD_PRIORITY);
		UnregisterHotKey(wnd, HIGHEST_THREAD_PRIORITY);
		UnregisterHotKey(wnd, TIME_CRITICAL_THREAD_PRIORITY);
		break;
	}
	case WM_SIZE: {
		RECT rect;
		GetWindowRect(wnd, &rect);
		settings->width = rect.right - rect.left;
		settings->height = rect.bottom - rect.top;
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
	BOOL bOk;
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