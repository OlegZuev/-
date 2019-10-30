#pragma once
#include "source.h"

wchar_t* wstringConvertToWChar_t(std::wstring& wstr);

void initBoard(Settings& settings, Grid**& board, LPVOID& sharedGrid);

Image readJpegImage(const wchar_t* wFilename);

Image readJpegImage(const std::string& filename);

Image* readJpegImages(const std::string* filename, int size);

Image readPngImage(const std::string& filename);

Image readPngImage(const wchar_t* wFilename);

BOOL WINAPI Crest(_In_ HDC hdc, _In_ int left, _In_ int top, _In_ int right, _In_ int bottom);

bool inputGridInMapping(Grid** board, const Settings& settings);

bool outputGridInMapping(Grid** board, const Settings& settings);

LPVOID openSharedGrid(const Settings& settings, HANDLE& fileMap);