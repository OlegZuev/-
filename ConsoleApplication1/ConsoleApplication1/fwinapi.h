#pragma once
#include "settings.h"

void loadSettingsWinAPI(Settings* settings, const wchar_t* name);

void saveSettingsWinAPI(Settings* settings, const wchar_t* name);