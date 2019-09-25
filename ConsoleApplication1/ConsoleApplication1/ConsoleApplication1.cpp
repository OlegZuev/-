#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <windowsx.h>
#include <tchar.h>

const wchar_t* clName = _T("MyClassName");
const wchar_t* clWinName = _T("MyWindowName");
const int N = 5;
HPEN hPenCell;
HPEN hPenCircle;
HBRUSH hBrushBackground;
HBRUSH hBrushCircle;
bool board[N][N];

void runEditor() {
	STARTUPINFO startUpInfo = { 0 };
	startUpInfo.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION processInfo;
	CreateProcess(_T("C:\\Program Files\\Notepad++\\Notepad++.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startUpInfo, &processInfo);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

void cellClicked(HWND wnd, int x, int y) {
	RECT rect = { 0 };
	GetClientRect(wnd, &rect);
	int column = x / (rect.right / N);
	int row = y / (rect.bottom / N);
	board[row][column] ^= true;
	InvalidateRect(wnd, NULL, true);
}

//Свой обработчик
LRESULT CALLBACK WinProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN: 
	{
		cellClicked(wnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0); //Код возврата приложения
		return 0;
	}
	case WM_KEYUP:
	{
		if (wParam == VK_CONTROL && GetAsyncKeyState('Q') & 0x8000 ||
			wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return 0;
		}
		if (wParam == 'C' && GetKeyState(VK_SHIFT) & 0x8000) {
			runEditor();
			break;
		}
		if (wParam == VK_RETURN) {
			int r = rand() % 256;
			int g = rand() % 256;
			int b = rand() % 256;
			hBrushBackground = CreateSolidBrush(RGB(r, g, b));
			SetClassLongPtr(wnd, GCLP_HBRBACKGROUND, (LONG)hBrushBackground);
			InvalidateRect(wnd, NULL, true);
			break;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(wnd, &ps);

		RECT rect = { 0 };
		GetClientRect(wnd, &rect);
		
		HPEN hOldPen = (HPEN)SelectObject(hdc, hPenCell);

		for (int i = 1; i < N; i++) {
			int x = rect.right / N * i;
			MoveToEx(hdc, x, 0, NULL);
			LineTo(hdc, x, rect.bottom);

			int y = rect.bottom / N * i;
			MoveToEx(hdc, 0, y, NULL);
			LineTo(hdc, rect.right, y);
		}

		SelectObject(hdc, hPenCircle);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrushCircle);

		for(int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[j][i]) {
					RECT rect = { 0 };
					GetClientRect(wnd, &rect);
					int left = i * (rect.right / N) + (rect.right / N) * 0.1;
					int top = j * (rect.bottom / N) + (rect.bottom / N) * 0.1;
					int right = (rect.right / N) * 0.8 ;
					int bottom = (rect.bottom / N) * 0.8;
					Ellipse(hdc, left, top, left + right, top + bottom);
				}
			}
		}

		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);
		EndPaint(wnd, &ps);
		break;
	}
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}

int main() {
	HINSTANCE hThisInstance = GetModuleHandle(NULL);
	
	hPenCell = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	hPenCircle = CreatePen(PS_SOLID, 5, RGB(255, 200, 30));
	hBrushCircle = CreateSolidBrush(RGB(255, 200, 30));
	hBrushBackground = CreateSolidBrush(RGB(0, 0, 255));

	WNDCLASSEX wincl = { 0 }; //WNDCLASSEX нужно использовать
	wincl.hInstance = hThisInstance; //Ссылка на хандлер
	wincl.lpszClassName = clName;
	wincl.lpfnWndProc = WinProc; //Свой обработчик
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.hbrBackground = hBrushBackground;
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);

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
		320,
		240,
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
			printf("Something bad has happen with GetMessage!\n");
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(wnd);
	DeleteObject(hPenCell);
	DeleteObject(hPenCircle);
	DeleteObject(hBrushCircle);
	DeleteObject(hBrushBackground);
	UnregisterClass(clName, hThisInstance);

	return msg.lParam;
}

