#pragma once
#include "source.h"

void setIOMethod(char* arg);

void inputSettings(Settings& settings, wchar_t* text);

void outputSettings(Settings& settings, std::wstringstream& wss);

void loadSettings(Settings& settings);

void saveSettings(Settings& settings);