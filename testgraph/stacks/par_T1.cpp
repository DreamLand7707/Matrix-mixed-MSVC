// 爆炸粒子备份 2022/7/1

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define PI 3.1415926
#define E 2.7182818
int p = 1;
double var_fix(double var);
double abt(double a);
double s_rand(unsigned int n);
int main(void)
{
    FILE *file = NULL;
    file = fopen("particle.mcfunction", "w+");
    double poi[3]{}, var[3]{};     // 生成位置和速度
    double var_m = 1;              // 速度乘数的最大值
    int max = 2000;                // 最大执行量
    double t1 = 0, t2 = 0, t3 = 0; // 缓冲用
    double var_ = 0;

    var_m = (long long)s_rand(time(0)) % 1000;
    var_m = ((var_m) / 1000) * 0.8 + 0.8;

    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            poi[j] = ((double)rand() / RAND_MAX) * 1 - 0.5;
            t1 = ((double)rand() / RAND_MAX) * 2 - 1;
            if (poi[j] < 0)
                var[j] = -abt(t1);
            else
                var[j] = abt(t1);
        }
        var_ = ((double)rand() / RAND_MAX) * (var_m / 2) + (var_m / 4);
        if (var_ < var_m / 2)
            var_ = var_ - abt(var_ - var_m / 2);
        else
            var_ = var_ + abt(var_ - var_m / 2);
        var_ = var_ / sqrt(pow(var[0], 2) + pow(var[1], 2) + pow(var[2], 2));
        fprintf(file, "particle end_rod ~%.6lf ~%.6lf ~%.6lf %.6lf %.6lf %.6lf %.6lf 0 force\r\n",
                poi[0], poi[1] + 10, poi[2], var[0], var[1], var[2], var_);
        // particle <PID> <x> <y> <z> <dx> <dy> <dz> <speed> <count> <force|normal> <player>
    }
    fprintf(file, "say %.3lf\n", var_m);
    fclose(file);
    return 0;
}
double var_fix(double var)
{
    double fix_ = 0;
    fix_ = 2.881 * pow(E, -1.874 * var);
    return fix_;
}
double abt(double a)
{
    if (a > 0)
        return a;
    else
        return -a;
}
double s_rand(unsigned int n)
{
    double p = (n % 100) / 17.0;
    p = (long long)(p * p * 390) % 100 + 950;
    return p;
}