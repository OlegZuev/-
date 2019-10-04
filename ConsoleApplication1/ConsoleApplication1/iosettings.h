#pragma once
#include "source.h"

void inputSettings(Settings& settings, wchar_t* text);

void outputSettings(Settings& settings, std::wstringstream& wss);

void loadSettings(Settings& settings, char* arg);

void saveSettings(Settings& settings, char* arg);