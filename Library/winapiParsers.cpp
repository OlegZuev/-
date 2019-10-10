int parseInt(const char text[], int& currentPointer, int size) {
	int variable = 0;
	int i = currentPointer;
	for (; i < size; i++) {
		if (text[i] == ' ') {
			i++;
			break;
		}
		if (text[i] == '\r') {
			i += 2;
			break;
		}
		if (i == currentPointer) {
			variable = text[i] - '0';
		} else {
			variable = variable * 10 + text[i] - '0';
		}
	}
	currentPointer = i;
	return variable;
}

wchar_t* parseWChar_t(const char text[], int& currentPointer, int size) {
	int i = currentPointer;
	for (; i < size; i++) {
		if (text[i] == ' ') {
			break;
		}
		if (text[i] == '\r') {
			break;
		}
	}
	size_t length = i - currentPointer;
	
	if (length > 0) {
		wchar_t* variable = new wchar_t[length + 1];
		char* temp = new char[length];
	    i = currentPointer;
		for (; i < size; i++) {
			if (text[i] == ' ') {
				break;
			}
			if (text[i] == '\r') {
				break;
			}
			temp[i - currentPointer] = text[i];
		}
		size_t outSize;
		mbstowcs_s(&outSize, variable, length + 1, temp, length);
		if (text[length - 1] == '\r') {
			i++;
		}
		currentPointer = ++i;
		delete[] temp;
		return variable;
	}
	return nullptr;
}

BOOL WriteFileInt(_In_ HANDLE hFile, _In_ int number) {
	std::string temp = std::to_string(number);
	return WriteFile(hFile, temp.c_str(), temp.size(), nullptr, nullptr);
}

BOOL WriteFileWChar_t(_In_ HANDLE hFile, _In_ const wchar_t* msg) {
	size_t length = std::wcslen(msg) + 1;
	char* converted = new char[length];
	size_t outSize;
    wcstombs_s(&outSize, converted, length,  msg, length - 1);
	BOOL result = WriteFile(hFile, converted, length - 1, nullptr, nullptr);
	delete[] converted;
	return result;
}