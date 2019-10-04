#include "fwinapi.h"

void loadSettingsWinAPI(Settings& settings, const wchar_t* name) {
	HANDLE file = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
		return;
	}

	int fileSize = GetFileSize(file, nullptr);
	wchar_t* text = new wchar_t[fileSize / sizeof(wchar_t) + 1];
	ZeroMemory(text, sizeof(char) * (fileSize / sizeof(wchar_t) + 1));

	if (!ReadFile(file, text, fileSize, nullptr, nullptr)) {
		DWORD error = GetLastError();
		printf("Error %lu\n", error);
	}
	text[fileSize / sizeof(wchar_t)] = _T('\0');
	CloseHandle(file);

	inputSettings(settings, text);

	delete[] text;
}

void saveSettingsWinAPI(Settings& settings, const wchar_t* name) {
    HANDLE file = CreateFileW(name, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "Error: INVALID_HANDLE_VALUE";
	}

	std::wstringstream wss;
	outputSettings(settings, wss);
	WriteFile(file, wss.str().c_str(), wss.str().length() * sizeof(wchar_t), nullptr, nullptr);
	CloseHandle(file);
}
