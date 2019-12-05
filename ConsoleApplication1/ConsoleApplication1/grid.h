#pragma once
#include "source.h"
#include "settings.h"
#include "animation.h"

class Grid {
	std::vector<std::vector<Cell*>> arr;
	HANDLE namedCellMutex;
	LPVOID sharedGrid;
	HANDLE sharedGridFile;
	std::atomic<UINT>* sharedCount;
	HANDLE sharedCountFile;
	std::atomic<UINT>* sharedPreviousClick;
	HANDLE sharedPreviousClickFile;
	std::atomic_bool* sharedFirstPlayer;
	HANDLE sharedFirstPlayerFile;
	std::string playerName;
	HANDLE endGame;

public:
	bool firstPlayer;
	bool winner;

	explicit Grid(int n);

	~Grid();

    void initBoard(int n, LPVOID& sharedGrid);

	void clearBoard();

	static void drawGrid(Settings* settings, HDC hdc, double height, double width);

	static void drawBackground(Animation* background, HDC hdc, double height, double width);

	void drawPlayerSign(Image* images, HDC hdc, double height, double width) const;

	void drawBoard(HWND wnd, Settings* settings, Image* images, Animation* background, std::atomic_bool& flag, HANDLE workingSemaphore);

	void cellClicked(HWND wnd, Settings* settings, int x, int y);

	bool isWinner();

	void lose(HWND wnd) const;

	void win(HWND wnd) const;

	static LPVOID openSharedStructure(const std::string& name, size_t size, HANDLE& fileMap);
};
