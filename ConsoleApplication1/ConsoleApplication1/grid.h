#pragma once
#include "source.h"
#include "settings.h"
#include "variables.h"

class Grid {
	std::vector<std::vector<Cell*>> arr;
	std::mutex counterMutex;
	LPVOID sharedGrid;
	HANDLE sharedGridFile;

public:
	explicit Grid(int n);

	~Grid();

    void initBoard(int n, LPVOID& sharedGrid);

	static void drawGrid(Settings* settings, HDC hdc, double height, double width);

	static void drawBackground(Animation& background, HDC hdc, double height, double width);

	void drawBoard(HWND wnd, Settings* settings, Image* images, Animation& background, std::atomic_bool& flag, HANDLE workingSemaphore);

	void cellClicked(Settings* settings, int x, int y);

	void isWinner();

	static LPVOID openSharedStructure(const std::string& name, size_t size, HANDLE& fileMap);
};
