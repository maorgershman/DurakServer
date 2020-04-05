#pragma once

#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#pragma warning(disable : 28251) // Inconsistent annotation on wWinMain/WinMain

#ifdef UNICODE
#define Main wWinMain
#define cout std::wcout
#define string std::wstring
#define stringstream std::wstringstream
#else
#define Main WinMain
#define cout std::cout
#define string std::string
#define stringstream std::stringstream
#endif

using std::endl;
