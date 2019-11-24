#include "fmapping.h"

void loadSettingsMapping(Settings* settings, const wchar_t* name) {
	HANDLE file = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	HANDLE fileMap = CreateFileMappingW(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
	if (fileMap == nullptr) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_READ, 0, 0, 0);
	if (lpFileMap == nullptr) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}

	settings->inputSettings((wchar_t*)lpFileMap);
	UnmapViewOfFile(lpFileMap);
	CloseHandle(file);
	CloseHandle(fileMap);
}

void saveSettingsMapping(Settings* settings, const wchar_t* name) {
    std::wstringstream wss;
	settings->outputSettings(wss);
	char* text = new char[wss.str().length() + 1];

	HANDLE file = CreateFileW(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	HANDLE fileMap = CreateFileMappingA(file, nullptr, PAGE_READWRITE, 0, wss.str().length() * sizeof(wchar_t), nullptr);
	if (fileMap == nullptr) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	LPVOID lpFileMap = MapViewOfFile(fileMap, FILE_MAP_WRITE, 0, 0, wss.str().length() * sizeof(wchar_t));
	if (lpFileMap == nullptr) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}

    wcscpy_s((wchar_t*)lpFileMap, wss.str().length() + 1, wss.str().c_str());
	UnmapViewOfFile(lpFileMap);
	CloseHandle(file);
	CloseHandle(fileMap);
	delete[] text;
}