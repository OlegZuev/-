#pragma once
#include "variables.h"
#include <string>

wchar_t* wstringConvertToWChar_t(std::wstring& wstr);

Image readJpegImage(const wchar_t* wFilename);

Image readJpegImage(const std::string& filename);

Image* readJpegImages(const std::string* filename, int size);

Image readPngImage(const std::string& filename);

Image readPngImage(const wchar_t* wFilename);

Image* readPngImages(const std::string* filename, int size);

BOOL WINAPI Crest(_In_ HDC hdc, _In_ int left, _In_ int top, _In_ int right, _In_ int bottom);

bool showPicture(Image& image, HDC& hdc, int left, int top, int right, int bottom);

bool replacePicture(HDC destHdc, int left, int top, int right, int bottom, HDC scrHdc, int width, int height);