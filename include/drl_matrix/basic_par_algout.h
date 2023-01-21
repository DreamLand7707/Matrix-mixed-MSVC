//? 算法输出
#ifndef basic_par_algout
#define basic_par_algout 1

#include "basic_par_para.h"

class O_partmatr;

typedef O_partmatr Omatr;

//? 用于控制真正的输出的超级类

/*

^ 继承关系
& matrix -> paramatr    matrix   pri =>O_partmatr
&       pro             paramatr pri   ↑

*/

class strmatr : public _TSTRING, public matr::paramatr
{
 private:
    //?
 public:
    strmatr(void){};
    strmatr(_TSTRING const &str, matr::paramatr const &pama = matr::empty_paramatr)
        : _TSTRING(str),
          paramatr(pama)
    {
    }
    strmatr(const TCHAR *str, matr::paramatr const &pama = matr::empty_paramatr)
        : _TSTRING(str),
          paramatr(pama)
    {
    }
    strmatr(const strmatr &stma)
        : _TSTRING((_TSTRING &)stma),
          paramatr((matr::paramatr &)stma)
    {
    }
    auto operator[](int x) -> decltype(matr::paramatr::operator[](x))
    {
        return matr::paramatr::operator[](x);
    }
    bool operator==(const strmatr &stma) { return (_TSTRING)(*this) == (_TSTRING)(stma); }
    bool print_t(void) const
    {
        _TCOUT << _T("**********") << std::endl;
        _TCOUT << _T("command:") << std::endl
               << *((_TSTRING *)this) << std::endl;
        _TCOUT << _T("paras:") << std::endl;
        matr::paramatr::print();
        _TCOUT << _T("**********") << std::endl;
        return true;
    }
};

namespace matr
{
    class matrix_temp : public drl::matrix
    {
     public:
        matrix_temp(const matrix &ma)
            : matrix(ma){};
        matrix_temp(matrix &&ma)
            : matrix(ma){};
        matrix_temp()
            : matrix(){};
        matrix_temp(const matrix_temp &ma)
            : matrix_temp(static_cast<const matrix &>(ma)){};
        matrix_temp(matrix_temp &&ma)
            : matrix_temp(static_cast<matrix &&>(ma)){};
        using matrix::matrix;
        ~matrix_temp() {}
    };
} // namespace matr

class O_partmatr : private matr::matrix_temp, private matr::paramatr
{
 private:
    static const drl::matrix I_2;
    // int add_counts = 1;
 public:
    O_partmatr(void)
        : matrix_temp(0, matr_tag::SP),
          paramatr(matr::empty_paramatr)
    {
    }
    O_partmatr(drl::matrix const &ma, matr::paramatr const &pama = matr::empty_paramatr)
        : matrix_temp(ma),
          paramatr(pama)
    {
    }
    O_partmatr(O_partmatr const &Optma)
        : matrix_temp((drl::matrix &)(matrix_temp &)Optma)
    {
    }
    ~O_partmatr() {}
    void assign_point(const drl::matrix &A)
    {
        ((matrix &)(matrix_temp &)(*this)).operator=(A);
    }
    void assign_para(const paramatr &B)
    {
        ((paramatr &)(*this)).operator=(B);
    }
    strmatr const linear(void);
    strmatr const quadhet(double x = 10.0, int mode = 1);
    strmatr const quadthr(double dig = 0, bool x = false);
};

#endif