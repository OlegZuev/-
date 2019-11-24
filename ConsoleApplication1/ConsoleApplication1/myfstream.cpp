//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "myfstream.h"
#include <codecvt>

// Read about codecvt and facet
void loadSettingsStream(Settings* settings, const wchar_t* name) {
	std::wifstream fin(name, std::ios::binary);
	if (!fin) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	std::locale loc = fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));
	fin.seekg(0, std::ios::end);
	size_t size = (size_t)fin.tellg();
	fin.seekg(0, std::ios::beg);
	wchar_t* text = new wchar_t[size / sizeof(wchar_t) + 1];
	text[size / sizeof(wchar_t)] = _T('\0');
	fin.read(text, size / sizeof(wchar_t));
	settings->inputSettings(text);
	fin.close();
	delete[] text;
}

void saveSettingsStream(Settings* settings, const wchar_t* name) {
	std::wofstream fout(name, std::ios::binary);
	if (!fout) {
		std::string message = "Error" + std::to_string(GetLastError());
		throw std::exception(message.c_str());
	}
	std::locale loc = fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));
	std::wstringstream wss;
	settings->outputSettings(wss);
	fout << wss.rdbuf();
	fout.close();
}