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

void initBoard(Settings& settings, bool**& array) {
	array = new bool* [settings.N];
	for (int i = 0; i < settings.N; i++) {
		array[i] = new bool[settings.N];
		ZeroMemory(array[i], sizeof(bool) * settings.N);
	}
}