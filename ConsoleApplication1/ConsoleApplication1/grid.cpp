#include "grid.h"
#include "utilities.h"

Grid::Grid(int n) {  // NOLINT(hicpp-member-init)
	namedCellMutex = CreateMutexA(nullptr, FALSE, "CellMutex");
	sharedCount = (std::atomic<UINT>*)openSharedStructure("Count", sizeof(std::atomic_int), sharedCountFile);
	sharedPreviousClick = (std::atomic<UINT>*)Grid::openSharedStructure("SharedPreviousClick", sizeof(std::atomic<UINT>), sharedPreviousClickFile);
	sharedGrid = openSharedStructure("Grid", sizeof(Cell) * n * n, sharedGridFile);
	initBoard(n, sharedGrid);
}

Grid::~Grid() {
	CloseHandle(namedCellMutex);
	UnmapViewOfFile(sharedCount);
	CloseHandle(sharedCountFile);
	UnmapViewOfFile(sharedPreviousClick);
	CloseHandle(sharedPreviousClickFile);
	UnmapViewOfFile(sharedGrid);
	CloseHandle(sharedGridFile);
}

void Grid::initBoard(int n, LPVOID& sharedGrid) {
	for (int i = 0; i < n; i++) {
		arr.emplace_back(n);
	}
	Cell* temp = (Cell*)sharedGrid; //Связываю поле с разделяемой памятью
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			arr[i][j] = temp;
			temp++;
		}
	}
}

void Grid::clearBoard() {
	WaitForSingleObject(namedCellMutex, INFINITE);
	for (auto& i : arr) {
		for (auto& j : i) {
			j->imageNumber = 0;
			j->isFilled = false;
		}
	}
	ReleaseMutex(namedCellMutex);
}

void Grid::drawGrid(Settings* settings, HDC hdc, double height, double width) {
	for (int i = 1; i < settings->N; i++) {
		int x = (int)(width / settings->N * i);
		MoveToEx(hdc, x, 0, nullptr);
		LineTo(hdc, x, (int)height);

		int y = (int)(height / settings->N * i);
		MoveToEx(hdc, 0, y, nullptr);
		LineTo(hdc, (int)width, y);
	}
}

void Grid::drawBackground(Animation& background, HDC hdc, double height, double width) {
	if (background.current == 40) {
		background.current = 0;
	}
	showPicture(background.images[background.current], hdc, 0, 0, (int)width, (int)height);
	++background.current;
}

void Grid::drawBoard(HWND wnd, Settings* settings, Image* images, Animation& background, std::atomic_bool& flag, HANDLE workingSemaphore) {
	while (flag) {
		WaitForSingleObject(workingSemaphore, INFINITE);
		HDC hdc = GetDC(wnd);

		RECT rect;
		GetClientRect(wnd, &rect);

		HPEN hOldPen = (HPEN)SelectObject(hdc, settings->hPenCell);

		double height = rect.bottom;
		double width = rect.right;

		drawBackground(background, hdc, height, width);

		drawGrid(settings, hdc, height, width);

		std::vector<HDC> imagesHdc;
		imagesHdc.push_back(CreateCompatibleDC(hdc));
		DeleteObject(SelectObject(imagesHdc[0], images[1].hBuffer));
		imagesHdc.push_back(CreateCompatibleDC(hdc));
		DeleteObject(SelectObject(imagesHdc[1], images[2].hBuffer));
		for (int i = 0; i < settings->N; i++) {
			for (int j = 0; j < settings->N; j++) {
				if (arr[j][i]->isFilled) {
					const int left = (int)(i * width / settings->N + width / settings->N * 0.2);
					const int top = (int)(j * height / settings->N + height / settings->N * 0.2);
					const int right = (int)(width / settings->N * 0.6);
					const int bottom = (int)(height / settings->N * 0.6);
					WaitForSingleObject(namedCellMutex, INFINITE);
					int index = arr[j][i]->imageNumber;
					ReleaseMutex(namedCellMutex);
					bool result = replacePicture(hdc, left, top, right, bottom, imagesHdc[index - 1], images[index].width, images[index].height);
					if (!result) {
						SelectObject(hdc, settings->hPenFigure);
						HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, settings->hBrushFigure);
						if (index == 1) {
							Ellipse(hdc, left, top, left + right, top + bottom);
						}
						if (index == 2) {
							Crest(hdc, left, top, left + right, top + bottom);
						}
						SelectObject(hdc, hOldBrush);
					}
				}
			}
		}
		DeleteDC(imagesHdc[0]);
		DeleteDC(imagesHdc[1]);

		SelectObject(hdc, hOldPen);
		ReleaseDC(wnd, hdc);
	    std::this_thread::sleep_for(std::chrono::milliseconds(35));
		ReleaseSemaphore(workingSemaphore, 1, nullptr);
	}
}

void Grid::cellClicked(HWND wnd, Settings* settings, int x, int y, UINT currentClick) {
	int column = (int)(x / ((double)settings->width / settings->N));
	int row = (int)(y / ((double)settings->height / settings->N));
	if (!arr[row][column]->isFilled) {
		WaitForSingleObject(namedCellMutex, INFINITE);
		arr[row][column]->isFilled = true;
		if (currentClick == WM_LBUTTONDOWN && *sharedPreviousClick != WM_LBUTTONDOWN) {
			arr[row][column]->imageNumber = 1;
		} else if (currentClick == WM_RBUTTONDOWN && *sharedPreviousClick != WM_RBUTTONDOWN) {
			arr[row][column]->imageNumber = 2;
		} else {
			MessageBoxA(wnd, "This turn is not your!", "Error", MB_OK);
			arr[row][column]->isFilled = false;
		}
		ReleaseMutex(namedCellMutex);
		*sharedPreviousClick = currentClick;
		++*sharedCount;
	}
	if (isWinner()) {
		MessageBoxA(wnd, "You are a winner!", "Congratulation!", MB_OK);
		if (MessageBoxA(wnd, "Do you want to try again?", "Continue", MB_YESNO) == IDYES) {
			UINT WM_RESTART = RegisterWindowMessageA("WM_RESTART");
			*sharedPreviousClick = 0;
			*sharedCount = 0;
			SendMessageA(HWND_BROADCAST, WM_RESTART, 0, 0);
		} else {
			UINT MY_WM_DESTROY = RegisterWindowMessageA("MY_WM_DESTROY");
			SendMessageA(HWND_BROADCAST, MY_WM_DESTROY, 0, 0);
		}
	}
	if (*sharedCount == arr.size() * arr.size()) {
		MessageBoxA(wnd, "It is a draw!", "Draw!", MB_OK);
		if (MessageBoxA(wnd, "Do you want to try again?", "Continue", MB_YESNO) == IDYES) {
			UINT WM_RESTART = RegisterWindowMessageA("WM_RESTART");
			*sharedPreviousClick = 0;
			*sharedCount = 0;
			SendMessageA(HWND_BROADCAST, WM_RESTART, 0, 0);
		} else {
			UINT MY_WM_DESTROY = RegisterWindowMessageA("MY_WM_DESTROY");
			SendMessageA(HWND_BROADCAST, MY_WM_DESTROY, 0, 0);
		}
	}
}

bool Grid::isWinner() {
	int circleNumber = 1;
	int crestNumber = 2;
	size_t crestCountHorizontal = 0;
	size_t crestCountVertical = 0;
	size_t crestCountDiagonalLeft = 0;
	size_t crestCountDiagonalRight = 0;
	size_t circleCountHorizontal = 0;
	size_t circleCountVertical = 0;
	size_t circleCountDiagonalLeft = 0;
	size_t circleCountDiagonalRight = 0;
	for (size_t i = 0; i < arr.size(); ++i) {
		for (size_t j = 0; j < arr[i].size(); ++j) {
			if (arr[i][j]->imageNumber == crestNumber) {
				crestCountHorizontal++;
			}
			if (arr[j][i]->imageNumber == crestNumber) {
				crestCountVertical++;
			}
			if (i == j && arr[i][j]->imageNumber == crestNumber) {
				crestCountDiagonalLeft++;
			}
			if (i == j && arr[i][arr[i].size() - j - 1]->imageNumber == crestNumber) {
				crestCountDiagonalRight++;
			}

			if (arr[i][j]->imageNumber == circleNumber) {
				circleCountHorizontal++;
			}
			if (arr[j][i]->imageNumber == circleNumber) {
				circleCountVertical++;
			}
			if (i == j && arr[i][j]->imageNumber == circleNumber) {
				circleCountDiagonalLeft++;
			}
			if (i == j && arr[i][arr[i].size() - j - 1]->imageNumber == circleNumber) {
				circleCountDiagonalRight++;
			}
		}
		if (crestCountHorizontal == arr.size() ||
			crestCountVertical == arr.size() ||
			crestCountDiagonalLeft == arr.size() ||
			crestCountDiagonalRight == arr.size()) {
			return true;
		}
		if (circleCountHorizontal == arr.size() ||
			circleCountVertical == arr.size() ||
			circleCountDiagonalLeft == arr.size() ||
			circleCountDiagonalRight == arr.size()) {
			return true;
		}
		crestCountHorizontal = 0;
		crestCountVertical = 0;
		circleCountHorizontal = 0;
		circleCountVertical = 0;
	}
	return false;
}

LPVOID Grid::openSharedStructure(const std::string& name, size_t size, HANDLE& fileMap) {
    fileMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, name.c_str());
	if (fileMap == nullptr) {
		fileMap = CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, size, name.c_str());
	}
	if (fileMap == nullptr) {
		DWORD error = GetLastError();
		printf("SharedStructure1: Error %lu and %s\n", error, name.c_str());
		throw std::exception(std::to_string(error).c_str());
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_ALL_ACCESS, 0, 0, size);
	if (lpFileMap == nullptr) {
		DWORD error = GetLastError();
		printf("SharedStructure2: Error %lu and %s\n", error, name.c_str());
		throw std::exception(std::to_string(error).c_str());
	}

	return lpFileMap;
}
