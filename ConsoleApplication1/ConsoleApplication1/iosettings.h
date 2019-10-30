#pragma once
#include "source.h"

void setIOMethod(char* arg);

void inputSettings(Settings& settings, wchar_t* text);

void outputSettings(Settings& settings, std::wstringstream& wss);

void loadSettings(Settings& settings);

void saveSettings(Settings& settings);

void inputGrid(Grid** board, int size, std::wstringstream& wss);

void inputGridInStream(Grid** board, int size, wchar_t* file);

void outputGridInStream(Grid** board, int size, std::wstringstream& wss);