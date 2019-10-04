#include "utilities.h"

void initBoard(Settings& settings, bool**& array) {
	array = new bool* [settings.N];
	for (int i = 0; i < settings.N; i++) {
		array[i] = new bool[settings.N];
		ZeroMemory(array[i], sizeof(bool) * settings.N);
	}
}