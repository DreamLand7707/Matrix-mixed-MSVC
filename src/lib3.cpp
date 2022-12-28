// ? 矩阵的底层实现
#include "../include/basic_ma1.h"
#include <algorithm>

// ? 排序
double *bub_sort(double *const array, int n)
{
    std::sort(array, array + n);
    return array;
}

// ? 对矩阵进行初始化
double **matr_init(Mat *const ma, int c_line, int c_raw, const double *cont,
                   int cont_init)
{
    if (c_line > 0 && c_raw > 0)
    {
        ma->pos = new double *[c_line];
        //? new double*[c_line]
        //? new double[c_raw]
        for (int i = 0; i < c_line; i++)
        {
            ma->pos[i] = new double[c_raw];
        }
        if (cont == NULL)
        {
            int min = c_raw * c_line;
            for (int i = 0; i < min; i++)
                ma->pos[i / c_raw][i % c_raw] = 0;
        }
        else
        {
            int min = cont_init > (c_line * c_raw) ? c_line * c_raw : cont_init;
            for (int i = 0; i < min; i++)
                ma->pos[i / c_raw][i % c_raw] = cont[i];
            if (min < c_line * c_raw)
                for (int i = min; i < c_line * c_raw; i++)
                    ma->pos[i / c_raw][i % c_raw] = 0;
        }

        ma->count_l = c_line, ma->count_r = c_raw;
        return ma->pos;
    }
    else
    {
        matr_init(ma, 3, 3, NULL, 0);
        return ma->pos;
    }
}

// ? 在两个同维度矩阵之间进行数据的传递
Mat *matr_copy(Mat *const ma_tar, const Mat *const ma_sor)
{
    if (ma_tar->count_l == ma_sor->count_l &&
        ma_tar->count_r == ma_sor->count_r)
    {
        for (int i = 0; i < ma_tar->count_l; i++)
            for (int j = 0; j < ma_tar->count_r; j++)
                ma_tar->pos[i][j] = ma_sor->pos[i][j];
        return ma_tar;
    }
    else
    {
        return NULL;
    }
}

// ? 将一个矩阵重新初始化
double **matr_swit(Mat *const ma, int c_line, int c_raw, const double *cont,
                   int cont_init)
{
    matr_free(ma);
    matr_init(ma, c_line, c_raw, cont, cont_init);
    return ma->pos;
}

// ? 释放矩阵占用的内存
void matr_free(Mat *const ma)
{
    if (ma->pos != nullptr)
    {
        for (int i = 0; i < ma->count_l; i++)
            delete[](ma->pos[i]);
        delete[](ma->pos);
    }
}

// ? 将一个二维的矩阵（指向指针的指针）变为一维的矩阵
int matr_dou2lin(double **const tar, const double *const *const sor, int line,
                 int raw)
{
    *tar = (double *)malloc(line * raw * sizeof(double));
    for (int i = 0; i < line; i++)
        for (int j = 0; j < raw; j++)
            (*tar)[i * raw + j] = sor[i][j];
    return line * raw;
}

// ? 进行线性运算：A=aA+bB+c
Mat *matr_lin(Mat *const ma_tar, const Mat *const ma_sor,
              const double *const la)   // A=aA+bB+c线性运算
{
    if (ma_tar->count_l == ma_sor->count_l &&
        ma_tar->count_r == ma_sor->count_r)
    {
        for (int i = 0; i < ma_tar->count_l; i++)
        {
            for (int j = 0; j < ma_tar->count_r; j++)
            {
                ma_tar->pos[i][j] = (la[0]) * ma_tar->pos[i][j] +
                                    (la[1]) * ma_sor->pos[i][j] + la[3];
            }
        }
        return ma_tar;
    }
    else
        return NULL;
}

// ? 进行矩阵乘法：C=A*B
Mat *matr_mul(const Mat *const ma_sor1, const Mat *const ma_sor2,
              Mat *const ma_tar)
{
    if (ma_sor1->count_r == ma_sor2->count_l)
    {
        double *p = (double *)malloc((ma_sor1->count_l) * (ma_sor2->count_r) *
                                     sizeof(double));
        memset(p, 0, (ma_sor1->count_l) * (ma_sor2->count_r) * sizeof(double));
        for (int i = 0; i < ma_sor1->count_l; i++)
        {
            for (int j = 0; j < ma_sor2->count_r; j++)
            {
                for (int k = 0; k < ma_sor1->count_r; k++)
                {
                    p[i * ma_sor2->count_r + j] +=
                        ma_sor1->pos[i][k] * ma_sor2->pos[k][j];
                }
            }
        }
        matr_swit(ma_tar, ma_sor1->count_l, ma_sor2->count_r, p,
                  ma_sor1->count_l * ma_sor2->count_r);
        free(p);
        return ma_tar;
    }
    else
        return NULL;
}

//? 基础信息求解：最大值，最小值，平均值，中值
//^ mode=1取最小值 mode=2取最大值 mode=3取平均值 mode=4取中值
double matr_spr(const Mat *const ma_sor, int mode, double error)
{
    double re = 0;
    //^ mode=1取最小值 mode=2取最大值 mode=3取平均值 mode=4取中值
    switch (mode)
    {
        case 1:
        {
            double min = 0;
            min = ma_sor->pos[0][0];
            for (int i = 0; i < ma_sor->count_l; i++)
                for (int j = 0; j < ma_sor->count_r; j++)
                {
                    if (min > ma_sor->pos[i][j])
                        min = ma_sor->pos[i][j];
                    else
                        continue;
                }
            re = min;
            break;
        }

        case 2:
        {
            double max = 0;
            max = ma_sor->pos[0][0];
            for (int i = 0; i < ma_sor->count_l; i++)
                for (int j = 0; j < ma_sor->count_r; j++)
                {
                    if (max < ma_sor->pos[i][j])
                        max = ma_sor->pos[i][j];
                    else
                        continue;
                }
            re = max;
            break;
        }

        case 3:
        {
            double add_ = 0;
            for (int i = 0; i < ma_sor->count_l; i++)
                for (int j = 0; j < ma_sor->count_r; j++)
                {
                    add_ += ma_sor->pos[i][j];
                }
            re = add_ / (ma_sor->count_l * ma_sor->count_r);
            break;
        }

        case 4:
        {
            double net = 0;
            double *p{};
            int max =
                matr_dou2lin(&p, ma_sor->pos, ma_sor->count_l, ma_sor->count_r);

            bub_sort(p, max);
            if (max % 2 == 0)
                net = (p[max / 2] + p[max / 2 - 1]) / 2;
            else
                net = p[(max - 1) / 2];
            re = net;
            free(p);
            break;
        }
        default:
        {
            re = error;
        }
    }
    return re;
}

//? 浮点数绝对值
double abt(double a)
{
    if (a > 0)
        return a;
    else
        return -a;
}

//? 范围判断
//^ mode=1为全在 mode=2为全不在 mode=3为是否在
int matr_range(const Mat *const ma_sor, int mode, double low, double high,
               double error)
{
    error = abt(error);
    double min, max;
    min = matr_spr(ma_sor, 1, 9);
    max = matr_spr(ma_sor, 2, 9);
    switch (mode)
    {
        case 1:
        {
            if ((low - abt(error)) < min && (high + abt(error)) > max)
                return 1;
            else
                return 0;
        }
        case 2:
        {
            double *p{};
            bool pointer = true;
            int count =
                matr_dou2lin(&p, ma_sor->pos, ma_sor->count_l, ma_sor->count_r);
            for (int i = 0; i < count; i++)
            {
                if (p[i] > low + error && p[i] < high - error)
                {
                    pointer = false;
                    break;
                }
                else
                    continue;
            }
            free(p);
            if (pointer == true)
                return 1;
            else
                return 0;
        }
        case 3:
        {
            double *p{};
            bool pointer_l = false, pointer_h = false;
            int count =
                matr_dou2lin(&p, ma_sor->pos, ma_sor->count_l, ma_sor->count_r);
            for (int i = 0; i < count; i++)
            {
                if (p[i] - error < low && p[i] + error > low)
                    pointer_l = true;
                if (p[i] - error < high && p[i] + error > high)
                    pointer_h = true;
                if (pointer_l == true && pointer_h == true)
                    break;
            }
            if (pointer_l == true && pointer_h == false)
                return 10;
            else if (pointer_l == false && pointer_h == true)
                return 1;
            else if (pointer_l == true && pointer_h == true)
                return 11;
            else
                return 0;
            break;
            free(p);
        }
        default:
            return 0;
    }
}

//? 矩阵的打印
int matr_print(const Mat *const ma, int n, double error)
{
    // putchar('\n');
    putchar('{');
    if (ma->count_r > 1)
    {
        for (int i = 0; i < ma->count_l; i++)
        {
            for (int j = 0; j < ma->count_r; j++)
            {
                if (j == 0 && i == 0)
                {
                    if (abt(ma->pos[i][j]) < error)
                        printf("{%.*lf ", n, 0.0);
                    else
                        printf("{%.*lf ", n, ma->pos[i][j]);
                    fflush(stdout);
                }
                else if (j == 0 && i != 0)
                {
                    if (abt(ma->pos[i][j]) < error)
                        printf(" {%.*lf ", n, 0.0);
                    else
                        printf(" {%.*lf ", n, ma->pos[i][j]);
                    fflush(stdout);
                }
                else if (j == ma->count_r - 1 && i != ma->count_l - 1)
                    if (abt(ma->pos[i][j]) < error)
                        printf("%.*lf} \n", n, 0.0);
                    else
                        printf("%.*lf} \n", n, ma->pos[i][j]);
                else if (j == ma->count_r - 1 && i == ma->count_l - 1)
                    if (abt(ma->pos[i][j]) < error)
                        printf("%.*lf}}\n", n, 0.0);
                    else
                        printf("%.*lf}}\n", n, ma->pos[i][j]);
                else
                {
                    if (abt(ma->pos[i][j]) < error)
                        printf("%.*lf ", n, 0.0);
                    else
                        printf("%.*lf ", n, ma->pos[i][j]);
                    fflush(stdout);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < ma->count_l; i++)
            if (i == 0)
                if (abt(ma->pos[i][0]) < error)
                    printf("{%.*lf} \n", n, 0.0);
                else
                    printf("{%.*lf} \n", n, ma->pos[i][0]);
            else if (i != 0 && i != ma->count_l - 1)
                if (abt(ma->pos[i][0]) < error)
                    printf(" {%.*lf} \n", n, 0.0);
                else
                    printf(" {%.*lf} \n", n, ma->pos[i][0]);
            else
            {
                if (abt(ma->pos[i][0]) < error)
                    printf(" {%.*lf}}\n", n, 0.0);
                else
                    printf(" {%.*lf}}\n", n, ma->pos[i][0]);
            }
    }
    return ma->count_l * ma->count_r;
}

//? 对矩阵做行初等变换，返回矩阵的行数列数的最小值，分正负，正数为行，负数为列
int matr_l_simp(Mat *const ma, double error)
{
    error = abt(error);
    int t1 = 0, t2 = 0, t3 = 0;
    t3 = matr_head(ma, &t1, &t2, error, 0, 0);
    if (t3 < 0)
        return 0;
    else
    {
        int a = 0, b = 0;
        double tr[3] = {0, 0, 0};
        for (; a < line_ && b < raw_; b++)
        {
            matr_head(ma, &t1, &t2, error, a, b);
            if (t1 >= a)
            {
                matr_l_exc(ma, a, t1);
                for (int j = a + 1; j < line_; j++)
                {
                    tr[0] = 1;
                    if (abt(pos_[a][t2]) < error)
                        tr[1] = 0;
                    else
                        tr[1] = -pos_[j][t2] / pos_[a][t2];
                    matr_l_lin(ma, j, a, tr);
                }
                a++;
            }
            else
                continue;
        }
        return line_ > raw_ ? -raw_ : line_;
    }
}

//? 求矩阵头
int matr_head(const Mat *const ma, int *const a, int *const b, double error,
              int tar_l, int tar_r)
{
    error = abt(error);
    int t1 = 0, t2 = 0;
    bool bre = 0;
    for (t1 = tar_r; t1 < raw_; t1++)
    {
        for (t2 = (t1 == tar_r) ? tar_l : 0; t2 < line_; t2++)
        {
            if (abt(pos_[t2][t1]) < abt(error))
                continue;
            else
            {
                *a = t2;
                *b = t1;
                bre = true;
                break;
            }
        }
        if (bre == true)
            break;
        else
            continue;
    }
    if (t2 == line_ && t1 == raw_)
    {
        *a = -1;
        *b = -1;
        return -1;
    }
    else
        return 1;
}

//? 矩阵行线性
int matr_l_lin(Mat *const ma, int tar, int sor, const double *const la)
{
    if ((sor >= 0 && sor < line_) && (tar >= 0 && tar < line_))
    {
        for (int i = 0; i < raw_; i++)
        {
            pos_[tar][i] = la[0] * pos_[tar][i] + la[1] * pos_[sor][i] + la[2];
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

//? 矩阵行交换
int matr_l_exc(Mat *const ma, int sor1, int sor2)
{
    if ((sor1 >= 0 && sor1 < line_) && (sor2 >= 0 && sor2 < line_))
    {
        double temp = 0;
        for (int i = 0; i <= raw_; i++)
        {
            temp = pos_[sor1][i];
            pos_[sor1][i] = pos_[sor2][i];
            pos_[sor2][i] = temp;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

//? 矩阵的秩
int matr_rank(const Mat *const ma, double error)
{
    error = abt(error);
    Mat b{};
    matr_init(&b, ma->count_l, ma->count_r, NULL, 0);
    matr_copy(&b, ma);

    matr_l_simp(&b, error);
    int rank = 0;
    for (int i = 0; i < line_; i++)
    {
        bool te = false;
        for (int j = 0; j < raw_; j++)
            if (abt(b.pos[i][j]) > abt(error))
            {
                te = true;
                break;
            }
            else
                continue;
        if (te)
            rank++;
        else
            continue;
    }
    matr_free(&b);
    return rank;
}

//? 矩阵的链接
int matr_r_link(Mat *const ma_tar, Mat const *const ma_sor)
{
    if (ma_tar->count_l == ma_sor->count_l)
    {
        Mat temp{};
        matr_init(&temp, ma_tar->count_l, ma_tar->count_r + ma_sor->count_r,
                  NULL, 0);
        for (int i = 0; i < temp.count_l; i++)
        {
            for (int j = 0; j < temp.count_r; j++)
            {
                if (j >= 0 && j < ma_tar->count_r)
                    temp.pos[i][j] = ma_tar->pos[i][j];
                else
                    temp.pos[i][j] = ma_sor->pos[i][j - ma_tar->count_r];
            }
        }
        matr_swit(ma_tar, temp.count_l, temp.count_r, NULL, 0);
        matr_copy(ma_tar, &temp);
        matr_free(&temp);
        return 1;
    }
    else
        return 0;
}

//? 矩阵列尾
int matr_r_tail(const Mat *const ma, int n, double error)
{
    error = abt(error);
    int re_sor = 0;
    for (int i = 0; i < ma->count_l; i++)
    {
        if (abt(ma->pos[i][n]) < abt(error))
            continue;
        else
            re_sor = i + 1;
    }
    return re_sor - 1;
}

//! 会给b分配空间，false为自由未知量，true为非自由未知量
int matr_freeX(const Mat *const ma, bool **const b, double error)
{
    error = abt(error);
    bool *p = (bool *)malloc((ma->count_r - 1) * sizeof(bool));
    memset(p, true, (ma->count_r - 1) * sizeof(bool));
    int a = -1;
    int c = 0;
    for (int i = 0; i < ma->count_r - 1; i++)
    {
        c = matr_r_tail(ma, i, error);
        if (c < 0)
        {
            p[i] = false;
            continue;
        }
        else
        {
            if (c <= a)
            {
                p[i] = false;
                continue;
            }
            else
            {
                p[i] = true;
                a = c;
                continue;
            }
        }
    }
    *b = p;
    return a;
}

//^ 特解
//! 会给solve分配空间
int matr_uni_sol(const Mat *const ma_coe, const Mat *const ma_equ,
                 double **const solve, double error)
{
    error = abt(error);
    if (ma_coe->count_l != ma_equ->count_l)
        return -2;
    double temp = 0;
    (*solve) = (double *)malloc(ma_coe->count_r * sizeof(double));
    bool *t = NULL;
    bool *y = NULL;
    int rank = 0;
    int posi = 0;
    Mat ma_pick1{}, ma_pick2{};
    matr_init(&ma_pick1, ma_coe->count_l, ma_coe->count_r, NULL, 0);
    matr_init(&ma_pick2, ma_coe->count_l, ma_coe->count_r, NULL, 0);
    matr_copy(&ma_pick1, ma_coe);
    matr_copy(&ma_pick2, ma_coe);
    // coe的两个副本
    matr_r_link(&ma_pick1, ma_equ);
    if ((rank = matr_rank(&ma_pick1, error)) == matr_rank(&ma_pick2, error) &&
        rank >= 0)
    {
        matr_free(&ma_pick2);
        matr_l_simp(&ma_pick1, error);
        matr_freeX(&ma_pick1, &t, error);
        matr_freeX(&ma_pick1, &y, error);
        //? 进行自由未知量的初始化
        for (int i = 0; i < (ma_pick1.count_r - 1); i++)
        {
            if (t[i] == false)
                (*solve)[i] = 0;
            else
                (*solve)[i] = 1;
        }
        //?
        //进行非自由未知量的计算，其中t是为了验证可用性，若为false则使用已有的solve值，true则固定为0
        //? y是为了确定非自由未知量的位置
        for (int i = rank - 1; i >= 0; i--)
        {
            temp = ma_pick1.pos[i][ma_pick1.count_r - 1];
            for (int j = 0; j < ma_pick1.count_r - 1; j++)
            {
                if (!t[j])
                    temp = temp - ((*solve)[j] * ma_pick1.pos[i][j]);
                else
                    continue;
            }
            posi = -1;
            for (int j = ma_pick1.count_r - 2; j >= 0; j--)
                if (y[j])
                {
                    posi = j;
                    y[j] = false;
                    break;
                }
                else
                    continue;
            if (posi >= 0)
            {
                (*solve)[posi] = temp / ma_pick1.pos[i][posi];
                t[posi] = false;
            }
            else
                continue;
        }
        free(t);
        free(y);
        return rank;
    }
    else
        return -1;
    matr_free(&ma_pick1);
    matr_free(&ma_pick2);
}

//^ 通解
//! 会给solve，ma_solv分配空间
int matr_sim_sol(const Mat *const ma_coe, const Mat *const ma_equ,
                 double **const solve, double error, Mat *const ma_solv)
{
    error = abt(error);
    int zero = 0;
    if (ma_coe->count_l != ma_equ->count_l)
        return -2;
    int rank = 0;             //? 矩阵的秩
    int sim_count = 0;        //? 自由未知量的个数
    int pos1 = 0, pos2 = 0;   //* 用于定位
    rank = matr_uni_sol(ma_coe, ma_equ, solve, error);

    Mat ma_pick1{}, ma_pick2{};
    matr_init(&ma_pick1, ma_coe->count_l, ma_coe->count_r, NULL, 0);
    matr_init(&ma_pick2, ma_coe->count_l, ma_coe->count_r, NULL, 0);
    matr_copy(&ma_pick1, ma_coe);
    matr_copy(&ma_pick2, ma_coe);
    matr_r_link(&ma_pick1, ma_equ);
    matr_r_link(&ma_pick2, ma_equ);
    matr_l_simp(&ma_pick1, error);
    matr_l_simp(&ma_pick2, error);
    bool *t1{}, *t2{};
    matr_freeX(&ma_pick1, &t1, error);
    matr_freeX(&ma_pick1, &t2, error);
    for (int i = 0; i < ma_pick1.count_r - 1; i++)
        if (t1[i] == true)
            continue;
        else
            sim_count++;
    if (rank < 0)
    {
        matr_init(ma_solv, 1, ma_pick1.count_r - 1, NULL, 0);
        for (int i = 0; i < ma_pick1.count_r - 1; i++)
            ma_solv->pos[0][i] /= zero;
        return rank;
    }
    if (sim_count == 0)
    {
        matr_init(ma_solv, 1, ma_pick1.count_r - 1, NULL, 0);
        return rank;
    }
    Mat sim_solve{};
    double **S = NULL;
    S = matr_init(&sim_solve, sim_count, ma_pick1.count_r - 1, NULL, 0);
    for (int i = 0; i < sim_count; i++)   // 从后往前第n个false
    {
        int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;
        bool temp = false;
        for (i1 = ma_pick1.count_r - 2, i2 = 0; i1 >= 0; i1--)
        {
            if (t1[i1] == false && i2 == i)
            {
                S[i][i1] = 1;
                i3 = i1;
                i2++;
            }
            else if (t1[i1] == false && i2 != i)
            {
                S[i][i1] = 0;
                i2++;
            }
            else
                S[i][i1] = -1;
        }
        // 找出最后一个false的位置,数组位置为i3;
        for (i1 = rank - 1; i1 >= 0; i1--, i4++)
        {
            i5 = 0;
            for (i2 = ma_pick1.count_r - 2; i2 >= 0; i2--)
            {
                if (i2 == i3)
                {
                    ma_pick1.pos[i1][ma_pick1.count_r - 1] =
                        ma_pick1.pos[i1][ma_pick1.count_r - 1] -
                        ma_pick1.pos[i1][i2];
                    ma_pick1.pos[i1][i2] = 0;
                }
                else if (t1[i2] == false && i2 != i3)
                {
                    ma_pick1.pos[i1][i2] = 0;
                }
                else if (t1[i2] == true)
                {
                    if (i5 == i4)
                    {
                        if (abt(ma_pick1.pos[i1][i2]) < error)
                            S[i][i2] = 0;
                        else
                            S[i][i2] = ma_pick1.pos[i1][ma_pick1.count_r - 1] /
                                       ma_pick1.pos[i1][i2];
                        i5++;
                        break;
                    }
                    else
                    {
                        ma_pick1.pos[i1][ma_pick1.count_r - 1] =
                            ma_pick1.pos[i1][ma_pick1.count_r - 1] -
                            S[i][i2] * ma_pick1.pos[i1][i2];
                        i5++;
                    }
                }
            }
        }
        matr_copy(&ma_pick1, &ma_pick2);
    }
    matr_init(ma_solv, sim_solve.count_l, sim_solve.count_r, NULL, 0);
    matr_copy(ma_solv, &sim_solve);
    for (int i = 0; i < ma_solv->count_l; i++)
    {
        for (int j = 0; j < ma_solv->count_r; j++)
            ma_solv->pos[i][j] = ma_solv->pos[i][j] - (*solve)[j];
    }
    matr_free(&ma_pick1);
    matr_free(&ma_pick2);
    matr_free(&sim_solve);
    free(t1);
    free(t2);
    return rank;
}

//^ 全解
//! 会给ma_solv分配空间
int matr_perf_sol(const Mat *const ma_coe, const Mat *const ma_equ,
                  double error, Mat *const ma_solv)
{
    error = abt(error);
    double *p = NULL;
    double *p1 = NULL;
    int zero = 0;
    int rank = 0;
    Mat P1{}, P2{};
    rank = matr_sim_sol(ma_coe, ma_equ, &p, error, &P1);
    if (rank >= 0)
    {
        matr_dou2lin(&p1, P1.pos, P1.count_l, P1.count_r);
        matr_init(&P2, P1.count_l + 1, P1.count_r, p1, P1.count_l * P1.count_r);
        for (int i = 0; i < P2.count_r; i++)
            P2.pos[P2.count_l - 1][i] = p[i];
        matr_free(&P1);
        free(p);
        free(p1);
        matr_dou2lin(&p, P2.pos, P2.count_l, P2.count_r);
        matr_init(ma_solv, P2.count_l, P2.count_r, p, P2.count_l * P2.count_r);
        free(p);
        matr_free(&P2);
        return rank;
    }
    else
    {
        matr_init(ma_solv, 1, ma_coe->count_r, NULL, 0);
        for (int i = 0; i < ma_solv->count_r; i++)
            ma_solv->pos[0][i] /= zero;
        return -2;
    }
}

//? 矩阵整齐打印
int matr_print_s(const Mat *const ma, int n, double error)
{
    double max = matr_spr(ma, 2, error);
    double min = matr_spr(ma, 1, error);
    int max_ = 0, min_ = 0;
    if (max < 0)
    {
        for (max_ = 1; abs(max) >= pow(10, max_); max_++)
            ;
        max_ = max_ + 2 + n;
    }
    else
    {
        for (max_ = 1; max >= pow(10, max_); max_++)
            ;
        max_ = max_ + 1 + n;
    }
    if (min < 0)
    {
        for (min_ = 1; abs(min) >= pow(10, min_); min_++)
            ;
        min_ = min_ + 2 + n;
    }
    else
    {
        for (min_ = 1; min >= pow(10, min_); min_++)
            ;
        min_ = min_ + 1 + n;
    }
    max_ = max_ > min_ ? max_ : min_;

    // putchar('\n');
    putchar('{');
    if (ma->count_r > 1)
    {
        for (int i = 0; i < ma->count_l; i++)
        {
            for (int j = 0; j < ma->count_r; j++)
            {
                if (j == 0 && i == 0)
                {
                    if (abt(ma->pos[i][j]) < error)
                        printf("{%*.*lf ", max_, n, 0.0);
                    else
                        printf("{%*.*lf ", max_, n, ma->pos[i][j]);
                    fflush(stdout);
                }
                else if (j == 0 && i != 0)
                {
                    if (abt(ma->pos[i][j]) < error)
                        printf(" {%*.*lf ", max_, n, 0.0);
                    else
                        printf(" {%*.*lf ", max_, n, ma->pos[i][j]);
                    fflush(stdout);
                }
                else if (j == ma->count_r - 1 && i != ma->count_l - 1)
                    if (abt(ma->pos[i][j]) < error)
                        printf("%*.*lf} \n", max_, n, 0.0);
                    else
                        printf("%*.*lf} \n", max_, n, ma->pos[i][j]);
                else if (j == ma->count_r - 1 && i == ma->count_l - 1)
                    if (abt(ma->pos[i][j]) < error)
                        printf("%*.*lf}}\n", max_, n, 0.0);
                    else
                        printf("%*.*lf}}\n", max_, n, ma->pos[i][j]);
                else
                {
                    if (abt(ma->pos[i][j]) < error)
                        printf("%*.*lf ", max_, n, 0.0);
                    else
                        printf("%*.*lf ", max_, n, ma->pos[i][j]);
                    fflush(stdout);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < ma->count_l; i++)
            if (i == 0)
                if (abt(ma->pos[i][0]) < error)
                    printf("{%*.*lf} \n", max_, n, 0.0);
                else
                    printf("{%*.*lf} \n", max_, n, ma->pos[i][0]);
            else if (i != 0 && i != ma->count_l - 1)
                if (abt(ma->pos[i][0]) < error)
                    printf(" {%*.*lf} \n", max_, n, 0.0);
                else
                    printf(" {%*.*lf} \n", max_, n, ma->pos[i][0]);
            else
            {
                if (abt(ma->pos[i][0]) < error)
                    printf(" {%*.*lf}}\n", max_, n, 0.0);
                else
                    printf(" {%*.*lf}}\n", max_, n, ma->pos[i][0]);
            }
    }
    return ma->count_l * ma->count_r;
}