#include "utilities.h"

// ReSharper disable once CppInconsistentNaming
wchar_t* wstringConvertToWChar_t(std::wstring& wstr) {
	wchar_t* wc = new wchar_t[wstr.length() + 1];
	for (int i = 0, length = wstr.length(); i < length; ++i) {
		wc[i] = wstr[i];
	}
	wc[wstr.length()] = '\0';
	return wc;
}

void initBoard(Settings& settings, Grid**& array) {
	array = new Grid* [settings.N];
	for (int i = 0; i < settings.N; i++) {
		array[i] = new Grid[settings.N];
		ZeroMemory(array[i], sizeof(Grid) * settings.N);
	}
}

Image readJpegImage(const wchar_t* wFilename) {
	char* cFilename = new char[wcslen(wFilename) + 1];
	size_t size;
	wcstombs_s(&size, cFilename, wcslen(wFilename) + 1, wFilename, wcslen(wFilename));
	return readJpegImage(cFilename);
}

Image readJpegImage(const std::string& filename) {
	HMODULE imageLoader = LoadLibraryA("ImageLoader");
	unsigned char* (*readJPEG)(const char*, int*, int*);
	(FARPROC&)readJPEG = GetProcAddress(imageLoader, "readJpegFile");
	Image image{};
	unsigned char* buffer = (*readJPEG)(filename.c_str(), &image.height, &image.width);
	image.hBuffer = CreateBitmap(image.width, image.height, 1, 32, buffer);
	FreeLibrary(imageLoader);
	delete buffer;
	return image;
}

Image* readJpegImages(const std::string* filename, int size) {
	HMODULE imageLoader = LoadLibraryA("ImageLoader");
	unsigned char* (*readJPEG)(const char*, int*, int*);
	(FARPROC&)readJPEG = GetProcAddress(imageLoader, "readJpegFile");
	Image* image = new Image[size];
	for (int i = 0; i < size; ++i) {
		unsigned char* buffer = (*readJPEG)(filename[i].c_str(), &image[i].height, &image[i].width);
		image[i].hBuffer = CreateBitmap(image[i].width, image[i].height, 1, 32, buffer);
		delete buffer;
	}
	FreeLibrary(imageLoader);
	return image;
}

Image readPngImage(const wchar_t* wFilename) {
	char* cFilename = new char[wcslen(wFilename) + 1];
	size_t size;
	wcstombs_s(&size, cFilename, wcslen(wFilename) + 1, wFilename, wcslen(wFilename));
	return readPngImage(cFilename);
}

Image readPngImage(const std::string& filename) {
	HMODULE imageLoader = LoadLibraryA("ImageLoader");
	unsigned char* (*readPNG)(const char*, int*, int*);
	(FARPROC&)readPNG = GetProcAddress(imageLoader, "readPngFile");
	Image image{};
	unsigned char* buffer = (*readPNG)(filename.c_str(), &image.height, &image.width);
	image.hBuffer = CreateBitmap(image.width, image.height, 1, 32, buffer);
	FreeLibrary(imageLoader);
	delete buffer;
	return image;
}

BOOL WINAPI Crest(_In_ HDC hdc, _In_ int left, _In_ int top, _In_ int right, _In_ int bottom) {
	MoveToEx(hdc, left, top, nullptr);
	LineTo(hdc, right, bottom);

	MoveToEx(hdc, right, top, nullptr);
	LineTo(hdc, left, bottom);

	return TRUE;
}