#include "fwinapi.h"

void loadSettingsWinAPI(Settings* settings, const wchar_t* name) {
	HANDLE file = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}

	int fileSize = GetFileSize(file, nullptr);
	wchar_t* text = new wchar_t[fileSize / sizeof(wchar_t) + 1];
	ZeroMemory(text, sizeof(char) * (fileSize / sizeof(wchar_t) + 1));

	if (!ReadFile(file, text, fileSize, nullptr, nullptr)) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	text[fileSize / sizeof(wchar_t)] = _T('\0');
	CloseHandle(file);

	settings->inputSettings(text);

	delete[] text;
}

void saveSettingsWinAPI(Settings* settings, const wchar_t* name) {
    HANDLE file = CreateFileW(name, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}

	std::wstringstream wss;
	settings->outputSettings(wss);
	WriteFile(file, wss.str().c_str(), wss.str().length() * sizeof(wchar_t), nullptr, nullptr);
	CloseHandle(file);
}
