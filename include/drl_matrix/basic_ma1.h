// 库文件baisc_ma1.cpp对应的头文件
#ifndef basic_ma1
#define basic_ma1 1

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define DNU (const double *)NULL   //? 零值分配的最佳选项

#define pos_  ma->pos
#define line_ ma->count_l
#define raw_  ma->count_r

typedef struct Matrix
{
    double **pos;
    int count_l;
    int count_r;
} Mat;   //! 矩阵的基本形式
// ? 对矩阵进行初始化
double **matr_init(Mat *const ma, int c_line, int c_raw, const double *cont, int cont_init);
//* 1 4

// ? 在两个同维度矩阵之间进行数据的传递
Mat *matr_copy(Mat *const ma_tar, const Mat *const ma_sor);
//* 1 2

// ? 将一个矩阵重新初始化
double **matr_swit(Mat *const ma, int c_line, int c_raw, const double *cont,
                   int cont_init);
//* 1 4

// ? 释放矩阵占用的内存
void matr_free(Mat *const ma);
//* 1

// ? 将一个二维的矩阵（指向指针的指针）变为一维的矩阵
//! 会给tar分配空间
int matr_dou2lin(double **const tar, const double *const *const sor, int line,
                 int raw);
//* 1

// ? 进行线性运算：A=aA+bB+c
Mat *matr_lin(Mat *const ma_tar, const Mat *const ma_sor,
              const double *const la);
//* 1 2 3

// ? 进行矩阵乘法：C=A*B
//! 会给ma_tar分配空间
Mat *matr_mul(const Mat *const ma_sor1, const Mat *const ma_sor2,
              Mat *const ma_tar);
//* 1 2 3

//? 基础信息求解：最大值，最小值，平均值，中值
//^ mode=1取最小值 mode=2取最大值 mode=3取平均值 mode=4取中值
double matr_spr(const Mat *const ma_sor, int mode, double error);
//* 1

//? 范围判断
//^ mode=1为全在 mode=2为全不在 mode=3为是否在
int matr_range(const Mat *const ma_sor, int mode, double low, double high,
               double error);
//* 1

//? 矩阵的打印
int matr_print(const Mat *const ma, int n, double error);
//* 1

//? 矩阵的整齐打印
int matr_print_s(const Mat *const ma, int n, double error);
//* 1

double *bub_sort(double *const array, int n);
//* 1

double abt(double a);

//? 求矩阵头
int matr_head(const Mat *const ma, int *const a, int *const b, double error,
              int tar_l, int tar_r);
//* 1 2 3

//? 矩阵行线性
int matr_l_lin(Mat *const ma, int tar, int sor, const double *const la);
//* 1 4

//? 矩阵行交换
int matr_l_exc(Mat *const ma, int sor1, int sor2);
//* 1

//? 对矩阵做行初等变换，返回矩阵的行数列数的最小值，分正负，正数为行，负数为列
int matr_l_simp(Mat *const ma, double error);
//* 1

//? 矩阵的秩
int matr_rank(const Mat *const ma, double error);
//* 1

//? 矩阵的链接
int matr_r_link(Mat *const ma_tar, Mat const *const ma_sor);
//* 1 2

//? 矩阵列尾
int matr_r_tail(const Mat *const ma, int n, double error);

//! 会给b分配空间，false为自由未知量，true为非自由未知量
int matr_freeX(const Mat *const ma, bool **const b, double error);
//* 2

//^ 特解
//! 会给solve分配空间
int matr_uni_sol(const Mat *const ma_coe, const Mat *const ma_equ,
                 double **const solve, double error);
//* 1 2 3

//^ 通解
//! 会给solve，ma_solv分配空间
int matr_sim_sol(const Mat *const ma_coe, const Mat *const ma_equ,
                 double **const solve, double error, Mat *const ma_solv);
//* 1 2 3 5

//^ 全解
//! 会给ma_solv分配空间
int matr_perf_sol(const Mat *const ma_coe, const Mat *const ma_equ,
                  double error, Mat *const ma_solv);
//* 1 2 4

#endif