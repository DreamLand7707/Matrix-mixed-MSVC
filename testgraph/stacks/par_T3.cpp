//? 黄金回旋长方体源代码
#include <cstdio>
#include <cmath>
#define R 0.3
#define G 0.2
#define B 0.8
int main(void)
{
    FILE *par = NULL;
    par = fopen("./block.mcfunction", "w+");
    //particleex normal <颗粒名> <x> <y> <z> <红> <绿> <蓝> <透明度>\
    <亮度> <vx> <vy> <vz> <dx> <dy> <dz> <数量> [寿命] [速度表达式] [计算间隔]
    /*
    计算公式：
    ^ y=rcos(wt+u)
    ^ z=rsin(wt+u)
    */
    double w = 0;                    //? 转动速度
    double x1 = 0, y1 = 0, z1 = 0;   //? 起始位置,无需调节
    double p = 0;                    //? 密集度
    double l1 = 0, l2 = 0, l3 = 0;   //? 长宽高
    double r = 0, ang = 0, cang = 0; //? 缓存：半径|角度|角度余弦,无需调节
    double delta = 0;                //? 计算间隔
    double height = 0;               //? 生成的中心轴高度

    l1 = 8, l2 = 8, l3 = 8;
    w = 0.5;
    p = 0.5;
    delta = 0.01;
    height = 6;
    //* 上平面
    for (double i = -l2 / 2; i < (l2 / 2); i += p)
    {
        for (double j = -l1 / 2; j < (l1 / 2); j += p)
        {
            //固定y为l3/2,xz为ji
            cang = (l3 / 2) / (sqrt(pow(l3 / 2, 2) + pow(i, 2)));
            r = sqrt(pow(l3 / 2, 2) + pow(i, 2));
            if (i < 0)
                ang = -acos(cang);
            else
                ang = acos(cang);
            fprintf(par, "particleex normal end_rod ~%f ~%f ~%f %f %f %f 1 0 0 0 0 0 0 1 -1 \"(vy,vz)=(-%f*sin(%f*t+%f),%f*cos(%f*t+%f))\" %f\n",
                    j, l3 / 2 + height, i, R, G, B, r * w, w / delta, ang, r * w, w / delta, ang, delta);
        }
    }
    //* 下平面
    for (double i = -l2 / 2; i < (l2 / 2); i += p)
    {
        for (double j = -l1 / 2; j < (l1 / 2); j += p)
        {
            //固定y为-l3/2,xz为ji
            cang = (-l3 / 2) / (sqrt(pow(-l3 / 2, 2) + pow(i, 2)));
            r = sqrt(pow(l3 / 2, 2) + pow(i, 2));
            if (i < 0)
                ang = -acos(cang);
            else
                ang = acos(cang);
            fprintf(par, "particleex normal end_rod ~%f ~%f ~%f %f %f %f 1 0 0 0 0 0 0 1 -1 \"(vy,vz)=(-%f*sin(%f*t+%f),%f*cos(%f*t+%f))\" %f\n",
                    j, -l3 / 2 + height, i, R, G, B, r * w, w / delta, ang, r * w, w / delta, ang, delta);
        }
    }
    //* 前平面
    for (double i = -l3 / 2; i < (l2 / 2); i += p)
    {
        for (double j = -l1 / 2; j < (l1 / 2); j += p)
        {
            //固定z为l2/2,xy为ji
            cang = i / (sqrt(pow(l2 / 2, 2) + pow(i, 2)));
            r = sqrt(pow(l2 / 2, 2) + pow(i, 2));
            ang = acos(cang);
            fprintf(par, "particleex normal end_rod ~%f ~%f ~%f %f %f %f 1 0 0 0 0 0 0 1 -1 \"(vy,vz)=(-%f*sin(%f*t+%f),%f*cos(%f*t+%f))\" %f\n",
                    j, i + height, l2 / 2, R, G, B, r * w, w / delta, ang, r * w, w / delta, ang, delta);
        }
    }
    //* 后平面
    for (double i = -l3 / 2; i < (l2 / 2); i += p)
    {
        for (double j = -l1 / 2; j < (l1 / 2); j += p)
        {
            //固定z为l2/2,xy为ji
            cang = i / (sqrt(pow(l2 / 2, 2) + pow(i, 2)));
            r = sqrt(pow(l2 / 2, 2) + pow(i, 2));
            ang = -acos(cang);
            fprintf(par, "particleex normal end_rod ~%f ~%f ~%f %f %f %f 1 0 0 0 0 0 0 1 -1 \"(vy,vz)=(-%f*sin(%f*t+%f),%f*cos(%f*t+%f))\" %f\n",
                    j, i + height, -l2 / 2, R, G, B, r * w, w / delta, ang, r * w, w / delta, ang, delta);
        }
    }
    //* 左平面
    for (double i = -l2 / 2; i < (l2 / 2); i += p)
    {
        for (double j = -l3 / 2; j < (l3 / 2); j += p)
        {
            //固定x为l1/2,yz为ji
            if ((sqrt(pow(j, 2) + pow(i, 2))) < 1e-6)
                cang = 1;
            else
                cang = j / (sqrt(pow(j, 2) + pow(i, 2)));
            r = sqrt(pow(j, 2) + pow(i, 2));
            if (i < 0)
                ang = -acos(cang);
            else
                ang = acos(cang);
            fprintf(par, "particleex normal end_rod ~%f ~%f ~%f %f %f %f 1 0 0 0 0 0 0 1 -1 \"(vy,vz)=(-%f*sin(%f*t+%f),%f*cos(%f*t+%f))\" %f\n",
                    l1 / 2 - p, j + height, i, R, G, B, r * w, w / delta, ang, r * w, w / delta, ang, delta);
        }
    }
    //* 右平面
    for (double i = -l2 / 2; i < (l2 / 2); i += p)
    {
        for (double j = -l3 / 2; j < (l3 / 2); j += p)
        {
            //固定x为l1/2,yz为ji
            if ((sqrt(pow(j, 2) + pow(i, 2))) < 1e-6)
                cang = 1;
            else
                cang = j / (sqrt(pow(j, 2) + pow(i, 2)));
            r = sqrt(pow(j, 2) + pow(i, 2));
            if (i < 0)
                ang = -acos(cang);
            else
                ang = acos(cang);
            fprintf(par, "particleex normal end_rod ~%f ~%f ~%f %f %f %f 1 0 0 0 0 0 0 1 -1 \"(vy,vz)=(-%f*sin(%f*t+%f),%f*cos(%f*t+%f))\" %f\n",
                    -l1 / 2, j + height, i, R, G, B, r * w, w / delta, ang, r * w, w / delta, ang, delta);
        }
    }
    fclose(par);
    return 0;
}