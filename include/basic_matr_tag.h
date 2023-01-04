﻿// 头文件basic_matr_class.h的特殊符号定义
#include <cassert>
#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <tchar.h>
// #include <conio.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>


#ifdef UNICODE
using _TSTRING = std::wstring;
using _TOSTRINGSTREAM = std::wostringstream;
using _TISTRINGSTREAM = std::wistringstream;
using _TSTRINGSTREAM = std::wstringstream;
using _TOSTREAM = std::wostream;
#define _TO_TSTRING std::to_wstring
#define _TCOUT std::wcout
#define TEXTD CF_UNICODETEXT
#else
using _TSTRING = std::string;
using _TOSTRINGSTREAM = std::ostringstream;
using _TISTRINGSTREAM = std::istringstream;
using _TSTRINGSTREAM = std::stringstream;
using _TOSTREAM = std::ostream;
#define _TCOUT std::cout
#define _TO_TSTRING std::to_string
#define TEXTD CF_TEXT
#endif


#ifndef basic_matr_tag
#define basic_matr_tag 1

#ifndef _TM
#ifndef _PM
#ifndef _IM
#ifndef _IN
#ifndef _Er
#ifndef _RAN
#ifndef _IRAN

#define _TM matr_tag::T
#define _PM matr_tag::P
#define _IM matr_tag::I
#define _IN matr_tag::II
#define _Er matr_tag::Err
#define _RAN matr_tag::RAN
#define _IRAN matr_tag::IRAN

#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif