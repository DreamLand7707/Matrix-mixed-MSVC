//? basic_par_para.h库文件
#include "basic_par_para.h"
#define thma ((drl::matrix &)(*this))
#define par_def_name_change 1130
namespace matr
{
    drl::matrix empty_paramatr({1.0, 10.0, 10.0, 0.1, 0.0, 0.0, 0.0, 1.0,
                                1122.0, 1.0, 1.0, 1.0, 0.0, 240.0, 0.0, 0.0},
                               4, 4);
    drl::matrix empty_paramatr_1165({1.0, 10.0, 10.0, 0.1, 0.0, 0.0, 0.0, 1.0,
                                     1165.0, 1.0, 1.0, 1.0, 0.0, 240.0, 0.0,
                                     0.0},
                                    4, 4);

    _TSTRING paramatr::def_name_1122 = _T("endRod");
    _TSTRING paramatr::def_name_1165 = _T("end_rod");
    _TSTRING paramatr::def_path = _T("../mcfunctions");

    paramatr::paramatr(drl::matrix const &ma, const TCHAR *str) : drl::matrix(ma)
    {
        check();
        thma[1][0] = thma[0][2];
        thma[1][2] = thma[1][1] =
            ::ceil((::abt(thma[0][1] - thma[0][0]) / thma[0][3]) / thma[0][2]);
        // if ((int)((thma[0][1] - thma[0][0]) / thma[0][3]) % (int)thma[1][0]
        // != 0)
        //     thma[1][1]++;
        if (str == nullptr || ::wcslen(str) == 0)
            if (thma[2][0] < par_def_name_change)
                name = def_name_1122;
            else
                name = def_name_1165;
        else
            name = str;
    }
    paramatr::paramatr(const TCHAR *str, drl::matrix const &ma) : drl::matrix(ma)
    {
        check();
        thma[1][0] = thma[0][2];
        thma[1][2] = thma[1][1] =
            ::ceil((::abt(thma[0][1] - thma[0][0]) / thma[0][3]) / thma[0][2]);
        if (str == nullptr || ::wcslen(str) == 0)
            if (thma[2][0] < par_def_name_change)
                name = def_name_1122;
            else
                name = def_name_1165;
        else
            name = str;
    }
    paramatr::paramatr(const paramatr &pama) : drl::matrix((drl::matrix &)pama)
    {
        name = pama.name;
    }
    void paramatr::parname(const TCHAR *name)
    {
        if (name == nullptr || ::wcslen(name) == 0)
            if (thma[2][0] < par_def_name_change)
                paramatr::name = def_name_1122;
            else
                paramatr::name = def_name_1165;
        else
            paramatr::name = name;
    }
    void paramatr::pathname(const TCHAR *name)
    {
        if (name == nullptr || ::wcslen(name) == 0)
            path = def_path;
        else
            path = name;
    }
    bool paramatr::print_t() const
    {
        using _TCOUT;
        using std::endl;
        printf("Game version:%.f\n", thma[2][0]);
        _TCOUT << "The present particle is: " << name << endl;
        printf("t: %.3f ~ %.3f : %.3f : %.3f for %c in %.2f ticks\n",
               thma[0][0], thma[0][1], thma[0][2], thma[0][3],
               ((int)thma[1][3]) ? '+' : '-', thma[1][2]);
        printf("File: %.f : %.f\n", thma[1][0], thma[1][1]);
        printf(
            "Para: R:%.3f G:%.3f B:%.3f Light:%.f Life:%.f instant:%c mode:%.f\n",
            thma[2][1], thma[2][2], thma[2][3], thma[3][1], thma[3][0],
            ((int)thma[3][2]) ? 'T' : 'F', thma[3][3]);
        return true;
    }
    void paramatr::check(void)
    {
        if (thma.size(1) == 4 && thma.size(2) == 4)
        {
            if (thma[0][0] >= thma[0][1] &&
                fabs(thma[0][0] - thma[0][1]) < drl::matrix::matr_error)
            {
                thma[0][0] = 1;
                thma[0][1] = 10;
            } //? 参数大小判断
            if (thma[0][2] <= 0 || thma[0][3] <= 0)
            {
                thma[0][2] = 10;
                thma[0][3] = 0.1;
            } //? 正负判断
            else
                thma[0][2] = ::round(thma[0][2]); //? 取整

            if (thma[0][1] - thma[0][0] < thma[0][3])
            {
                thma[0][0] = 1;
                thma[0][1] = 10;
                thma[0][2] = 10;
                thma[0][3] = 0.1;
            }

            if (thma[1][3] < 0 || thma[1][3] > 0)
                thma[1][3] = 1;

            if (thma[2][0] < 0)
                thma[2][0] = 1122;

            if (thma[2][1] < 0)
                thma[2][1] = 1;

            if (thma[2][2] < 0)
                thma[2][2] = 1;

            if (thma[2][3] < 0)
                thma[2][3] = 1;

            if (thma[3][0] < -1)
                thma[3][0] = 0;

            if (thma[3][1] < 0)
                thma[3][1] = 240;

            if (thma[3][2] < 0 || thma[3][2] > 0)
                thma[3][2] = 1;

            if (thma[3][3] != 0 || thma[3][3] != 1 || thma[3][3] != 2)
                thma[3][3] = 0;
        }
        else
            thma = empty_paramatr;
    }
} // namespace matr
#undef thma
#undef par_def_name_change