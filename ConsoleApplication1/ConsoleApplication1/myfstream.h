#pragma once
#include "settings.h"

void loadSettingsStream(Settings* settings, const wchar_t* name);

void saveSettingsStream(Settings* settings, const wchar_t* name);