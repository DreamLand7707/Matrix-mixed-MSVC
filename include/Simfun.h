// 建议非必要不要使用，可作为借鉴
#ifndef Simfun
#define Simfun 1
// Ver:2022/6
// 实用函数及C库头文件包含
/*
函数列表 funlist:
1.	s_gets			安全字符串
2.	gotoxy			控制台光标定位
3.	loading	LOAD	加载样式函数
4.	T_START T_END	时间控制显示
    STDEND_S		统一时间控制显示
5.	pause _PAUSE_S	Ctrl+Q的暂停控制
6.	gcd				求最大公因数
*/
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <time.h>

#define LOAD(X) loading((X))
#define STDEND_S \
    T_END;       \
    _PAUSE_S

/* 安全字符串自建函数
函数原型s_gets，使用字符串地址作为传入参数，作为内存中存储字符串位置
同时接受一个int值作为最大字符数，注意传入的字符数包含了空字符
返回一个char*类型的值，该值指向传入的字符串
*/
static inline char *s_gets(char *c, int a)   // 安全字符串输入函数 No.D2022416
{
    // 使用fgets作为内置函数，所以声明了stdio.h
    int i = 0;
    char *k = NULL;
    k = fgets(c, a, stdin);
    if (k)
    {
        while (c[i] != '\n' && c[i] != '\0')
            i++;
        if (c[i] == '\n')
            c[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return k;
}

/* 基于windows.h的控制台控制函数
用于控制控制台光标位置。接受两个参数，x和y，调用之后
将控制台光标置于xy指定的位置
*/
inline void gotoxy(int x, int y)   // 控制台光标控制函数 NO.D2022420
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

/*
& 基于Windows.h的加载函数
? 在当前区域生成一个“Loading”模样的延迟加载
! 用count来确定后面跟的点的个数，这个个数代表着延迟的秒数 NO.D2022420
! DrL:已经使用宏定义LOAD(X)，可以直接代替loading
*/
inline void loading(int count)
{
    printf("Loading");
    int i = 0;
    for (; i < count; i++)
    {
        putchar('.');
        Sleep(1000);
    }
}

/*
& 程序运行时间函数
? 在最初区域和最后区域之间进行运算，并且在相应的未知输出运行时间
? 进入标志为T_START,出口标志为T_END
! 若只有T_END，则自动将程序入点当作T_START位置 NO.D2022508
*/
inline clock_t t_time(void)
{
    return clock();
}

static clock_t _start_t = 0, _end_t = 0;
static clock_t _error_t = 0;

#define T_START _start_t = t_time()
#define T_END                                                             \
    _end_t = t_time();                                                    \
    printf("\n-----------------------------------------\nThe during of p" \
           "rogram is %.6lf seconds\n\n\tPress Q to Quit...",             \
           (double)(_end_t - _start_t) / (double)CLOCKS_PER_SEC)

/*暂停函数*/
inline void pause(void)
{
    char c;
    while ((c = _getch()) != 113)
        continue;
}
#define _PAUSE_S pause()

/*最大公因数*/
inline long long gcd(long long a, long long b)
{
    return b != 0 ? gcd(b, a % b) : a;
}
#endif