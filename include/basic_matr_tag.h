﻿//头文件basic_matr_class.h的特殊符号定义
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
// #include <conio.h>
#include <algorithm>
#include <array>
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
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#ifndef basic_matr_tag
    #define basic_matr_tag 1

    #ifndef _TM
        #ifndef _PM
            #ifndef _IM
                #ifndef _IN
                    #ifndef _Er
                        #ifndef _RAN
                            #ifndef _IRAN

                                #define _TM   matr_tag::T
                                #define _PM   matr_tag::P
                                #define _IM   matr_tag::I
                                #define _IN   matr_tag::II
                                #define _Er   matr_tag::Err
                                #define _RAN  matr_tag::RAN
                                #define _IRAN matr_tag::IRAN

                            #endif
                        #endif
                    #endif
                #endif
            #endif
        #endif
    #endif

#endif