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

Image readJpegImage(const std::string& filename) {
	HMODULE imageLoader = LoadLibraryA("ImageLoader");
	unsigned char* (*readJPEG)(const char*, int*, int*);
	(FARPROC&)readJPEG = GetProcAddress(imageLoader, "readJpegFile");
	Image image{};
	unsigned char* buffer = (*readJPEG)(filename.c_str(), &image.height, &image.width);
	image.buffer = CreateBitmap(image.width, image.height, 1, 32, buffer);
	FreeLibrary(imageLoader);
	//delete buffer;
	return image;
}