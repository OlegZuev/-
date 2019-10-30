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

void initBoard(Settings& settings, Grid**& board, LPVOID& sharedGrid) {
	board = new Grid* [settings.N];
	for (int i = 0; i < settings.N; i++) {
		board[i] = new Grid[settings.N];
		ZeroMemory(board[i], sizeof(Grid) * settings.N);
	}
	bool* temp = (bool*)sharedGrid; //Связываю поле с разделяемой памятью
	int k = 0;
	for (int i = 0; i < settings.N; ++i) {
		for (int j = 0; j < settings.N; ++j) {
			board[i][j].isFilled = temp + k * 5;
			board[i][j].imageNumber = (int*)(temp + k * 5 + 1);
			k++;
		}
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

bool inputGridInMapping(Grid** board, const Settings& settings) {
	HANDLE fileMap = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READONLY, 0, sizeof(Grid) * settings.N * settings.N, _T("Grid"));
	if (fileMap == nullptr) {
		DWORD error = GetLastError();
		printf("InputGridInMapping: Error %lu\n", error);
		return false;
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_READ, 0, 0, 0);
	if (lpFileMap == nullptr) {
		DWORD error = GetLastError();
		printf("InputGridInMapping: Error %lu\n", error);
		return false;
	}

	inputGridInStream(board, settings.N, (wchar_t*)lpFileMap);
	UnmapViewOfFile(lpFileMap);
	CloseHandle(fileMap);
	return true;
}

bool outputGridInMapping(Grid** board, const Settings& settings) {
	std::wstringstream wss;
	outputGridInStream(board, settings.N, wss);

	HANDLE fileMap = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, wss.str().length() * sizeof(wchar_t), _T("Grid"));
	if (fileMap == nullptr) {
		DWORD error = GetLastError();
		printf("OutputGridInMapping: Error %lu\n", error);
		return false;
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_WRITE, 0, 0, wss.str().length() * sizeof(wchar_t));
	if (lpFileMap == nullptr) {
		DWORD error = GetLastError();
		printf("OutputGridInMapping: Error %lu\n", error);
		return false;
	}

	wcscpy_s((wchar_t*)lpFileMap, wss.str().length() + 1, wss.str().c_str());
	UnmapViewOfFile(lpFileMap);
	CloseHandle(fileMap);
	return true;
}

LPVOID openSharedGrid(const Settings& settings, HANDLE& fileMap) {
    fileMap = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, _T("Grid"));
	if (fileMap == nullptr) {
		fileMap = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(Grid) * settings.N * settings.N, _T("Grid"));
	}
	if (fileMap == nullptr) {
		DWORD error = GetLastError();
		printf("OpenSharedGrid: Error %lu\n", error);
		return nullptr;
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Grid) * settings.N * settings.N);
	if (lpFileMap == nullptr) {
		DWORD error = GetLastError();
		printf("OpenSharedGrid: Error %lu\n", error);
		return nullptr;
	}
	return lpFileMap;
}