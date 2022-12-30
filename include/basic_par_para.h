//? 粒子算法
#ifndef basic_par_para
#define basic_par_para 1

/*
曲线：
*①瞬间的：
密度
*②动态的：
密度
完全生成的时间
方向

无论是文件(mcfunction)还是单指令(colorblock)
均可用如下公式计算：
^[CPT]   = C (在文件中是单个文件包含的指令数)
^[delta] = D (在文件中是(t_end-t_start)/(C*TD - 1))

TD是total block总的命令方块数

生成时间  =  ((t_end - t_start)/D)/C => (tick)
密度由如下变量决定：
^t_end - t_start(正相关)
^delta          (反比例)

^ 使用算法生成曲线矩阵
^ 使用特定输出解析曲线矩阵
*/

#include "../include/basic_matr_class.h"
#include <iostream>
#include <string>

namespace matr
{
    extern drl::matrix empty_paramatr;
    extern drl::matrix empty_paramatr_1165;
    class paramatr : public drl::matrix
    {
     private:
        _TSTRING name;
        _TSTRING path = def_path;

     public:
        static _TSTRING def_name_1122;
        static _TSTRING def_name_1165;
        static _TSTRING def_path;

        paramatr(drl::matrix const &ma = empty_paramatr, const TCHAR *str = _T(""));
        paramatr(const TCHAR *str, drl::matrix const &ma = empty_paramatr);
        paramatr(const paramatr &);
        virtual ~paramatr() {}
        virtual bool print_t() const;
        void parname(const TCHAR *name = _T(""));
        void pathname(const TCHAR *name = _T(""));
        void check(void);
        const _TSTRING &par_name(void)
        {
            return name;
        }
        using matrix::operator[];
        inline int tail(void)
        {
            double total;
            total =
                ::ceil((matrix::operator[](0)[1] - matrix::operator[](0)[0]) /
                       matrix::operator[](0)[3]);
            double i_tail;
            if ((int)total % (int)matrix::operator[](0)[2] == 0)
                i_tail = 0;
            else
                i_tail = (int)total % (int)matrix::operator[](0)[2];
            return (int)i_tail;
        }
    };
    /*
        & 用于存储标准参数
        ^ t_start(d)          t_end(d)          CPT(i)             delta(d)
        ? 起始参数             结束参数           每tick计算次数      计算间隔
        ^ CPerf(i)            Tolf(i)           time(d)            direct(b)
        ? .每个file的指令数目   .一共有的文件数目    .完全生成的时间     生成方向(true代表t_start -> t_end,false为反)
        ^ Ver(i)              R(d)               G(d)               B(d)
        ? 游戏版本             红                绿                  蓝
        ^life(d)             light(i)          instant(b)         mode(i) ?
        粒子寿命             发光              是否瞬间生成           模式(colorblock:0,文件:1,混合:2)
    */
} // namespace matr

#endif