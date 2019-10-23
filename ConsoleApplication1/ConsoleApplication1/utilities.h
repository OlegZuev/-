#pragma once
#include "source.h"

wchar_t* wstringConvertToWChar_t(std::wstring& wstr);

void initBoard(Settings& settings, Grid**& array);

Image readJpegImage(const std::string& filename);