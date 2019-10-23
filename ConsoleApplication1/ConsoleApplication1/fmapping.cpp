#include "source.h"

void loadSettingsMapping(Settings& settings, const wchar_t* name) {
	HANDLE file = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
		return;
	}
	HANDLE fileMap = CreateFileMappingW(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
	if (fileMap == nullptr) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
		return;
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_READ, 0, 0, 0);
	if (lpFileMap == nullptr) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
		return;
	}

	inputSettings(settings, (wchar_t*)lpFileMap);
	UnmapViewOfFile(lpFileMap);
	CloseHandle(file);
	CloseHandle(fileMap);
}

void saveSettingsMapping(Settings& settings, const wchar_t* name) {
    std::wstringstream wss;
	outputSettings(settings, wss);
	char* text = new char[wss.str().length() + 1];

	HANDLE file = CreateFileW(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
		return;
	}
	HANDLE fileMap = CreateFileMappingA(file, nullptr, PAGE_READWRITE, 0, wss.str().length() * sizeof(wchar_t), nullptr);
	if (fileMap == nullptr) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
		return;
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_WRITE, 0, 0, wss.str().length() * sizeof(wchar_t));
	if (lpFileMap == nullptr) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
		return;
	}

    wcscpy_s((wchar_t*)lpFileMap, wss.str().length() + 1, wss.str().c_str());
	UnmapViewOfFile(lpFileMap);
	CloseHandle(file);
	CloseHandle(fileMap);
	delete[] text;
}