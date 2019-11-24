#pragma once
#include "source.h"
#include "settings.h"
#include "variables.h"

class Grid {
	std::vector<std::vector<Cell*>> arr;
	HANDLE namedCellMutex;
	LPVOID sharedGrid;
	HANDLE sharedGridFile;
	std::atomic<UINT>* sharedCount;
	HANDLE sharedCountFile;
	std::atomic<UINT>* sharedPreviousClick;
	HANDLE sharedPreviousClickFile;

public:
	explicit Grid(int n);

	~Grid();

    void initBoard(int n, LPVOID& sharedGrid);

	void clearBoard();

	static void drawGrid(Settings* settings, HDC hdc, double height, double width);

	static void drawBackground(Animation& background, HDC hdc, double height, double width);

	void drawBoard(HWND wnd, Settings* settings, Image* images, Animation& background, std::atomic_bool& flag, HANDLE workingSemaphore);

	void cellClicked(HWND wnd, Settings* settings, int x, int y, UINT currentClick);

	bool isWinner();

	static LPVOID openSharedStructure(const std::string& name, size_t size, HANDLE& fileMap);
};
