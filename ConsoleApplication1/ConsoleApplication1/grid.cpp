#include "grid.h"
#include "utilities.h"

Grid::Grid(int n) {  // NOLINT(hicpp-member-init)
	sharedGrid = openSharedStructure("Grid", sizeof(Cell) * n * n, sharedGridFile);
	initBoard(n, sharedGrid);
}

Grid::~Grid() {
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

		for (int i = 0; i < settings->N; i++) {
			for (int j = 0; j < settings->N; j++) {
				if (arr[j][i]->isFilled) {
					const int left = (int)(i * width / settings->N + width / settings->N * 0.2);
					const int top = (int)(j * height / settings->N + height / settings->N * 0.2);
					const int right = (int)(width / settings->N * 0.6);
					const int bottom = (int)(height / settings->N * 0.6);
					if (arr[j][i]->imageNumber == 0) {
						std::random_device rd;
						std::mt19937 generator(rd());
						std::uniform_int_distribution<int> dist(1, 2);
						arr[j][i]->imageNumber = dist(generator);
					}
					int index = arr[j][i]->imageNumber;
					bool result = showPicture(images[index], hdc, left, top, right, bottom);
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

		SelectObject(hdc, hOldPen);
		ReleaseDC(wnd, hdc);
	    std::this_thread::sleep_for(std::chrono::milliseconds(35));
		ReleaseSemaphore(workingSemaphore, 1, nullptr);
	}
}

void Grid::cellClicked(Settings* settings, int x, int y) {
	int column = (int)(x / ((double)settings->width / settings->N));
	int row = (int)(y / ((double)settings->height / settings->N));
	arr[row][column]->isFilled = arr[row][column]->isFilled ^ true;
	if (!arr[row][column]->isFilled) {
		arr[row][column]->imageNumber = 0;
	}
}

void Grid::isWinner() {
	
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
