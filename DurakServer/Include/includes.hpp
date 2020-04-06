#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <cstdint>

#ifdef UNICODE
#define T(x) L##x
#define tmain wWinMain
#define tcout std::wcout
#define tstring std::wstring
#define tstringstream std::wstringstream
#define to_tstring std::to_wstring
#else
#define T(x) x
#define tmain WinMain
#define tcout std::cout
#define tstring std::string
#define tstringstream std::stringstream
#define to_tstring std::to_string
#endif

using std::endl;
