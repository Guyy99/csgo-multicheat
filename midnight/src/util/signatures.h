#pragma once

#include <windows.h>
#include <psapi.h>
#include <vector>
#include <iostream>

namespace util
{
	uintptr_t scan_signature(const char* moduleName, const char* pattern) noexcept; // format eg. 88 49 ?? 48
}