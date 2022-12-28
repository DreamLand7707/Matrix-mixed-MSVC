//? 算法输出
#ifndef basic_par_algout
#define basic_par_algout 1

#include "../include/basic_par_para.h"

class O_partmatr;

typedef O_partmatr Omatr;

//? 用于控制真正的输出的超级类

/*

^ 继承关系
& matrix -> paramatr    matrix   pri =>O_partmatr
&       pro             paramatr pri   ↑

*/

class strmatr : public std::string, public matr::paramatr
{
 private:
    //?
 public:
    strmatr(void);
    strmatr(std::string const &str, matr::paramatr const &pama = matr::empty_paramatr)
        : std::string(str), paramatr(pama)
    {
    }
    strmatr(const char *str, matr::paramatr const &pama = matr::empty_paramatr)
        : std::string(str), paramatr(pama)
    {
    }
    strmatr(const strmatr &stma)
        : std::string((std::string &)stma), paramatr((matr::paramatr &)stma)
    {
    }
    auto operator[](int x) -> decltype(matr::paramatr::operator[](x))
    {
        return matr::paramatr::operator[](x);
    }
    bool operator==(const strmatr &stma) { return (std::string)(*this) == (std::string)(stma); }
    void print(void)
    {
        std::cout << "**********" << std::endl;
        std::cout << "command:" << std::endl
                  << *((std::string *)this) << std::endl;
        std::cout << "paras:" << std::endl;
        matr::paramatr::print();
        std::cout << "**********" << std::endl;
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
}   // namespace matr

class O_partmatr : private matr::matrix_temp, private matr::paramatr
{
 private:
    static const drl::matrix I_2;
    // int add_counts = 1;
 public:
    O_partmatr(void)
        : matrix_temp(0, matr_tag::SP), paramatr()
    {
    }
    O_partmatr(drl::matrix const &ma, matr::paramatr const &pama = matr::empty_paramatr)
        : matrix_temp(ma), paramatr(pama)
    {
    }
    O_partmatr(O_partmatr const &Optma)
        : matrix_temp((drl::matrix &)(matrix_temp &)Optma)
    {
    }
    ~O_partmatr() {}
    strmatr const linear(void);
    strmatr const quadhet(double x = 10.0, int mode = 1);
    strmatr const quadthr(double dig = 0, bool x = false);
};

#endif