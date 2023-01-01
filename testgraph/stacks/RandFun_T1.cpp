#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>
double s_rand(unsigned int n);
int main()
{
    double ma = 0;
    for (int i = 0; i < 1000; i++)
    {
        Sleep(1000);
        ma = (long long)s_rand(time(0)) % 1000;
        printf("%.3lf ", ma);
        fflush(stdout);
    }
    getchar();
}
double s_rand(unsigned int n)
{
    double p = (n % 100) / 17.0;
    p = (long long)(p * p * 390) % 100 + 950;
    return p;
}