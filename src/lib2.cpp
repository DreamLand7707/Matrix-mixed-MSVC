//? basic_par_algout.h库文件
#include "../include/basic_par_algout.h"
using namespace drl;
drl::matrix const O_partmatr::I_2(2, matr_tag::I);
/*
    & 用于存储标准参数
    ^ t_start(d)          t_end(d)          CPT(i)             delta(d)
    ? 起始参数             结束参数           每tick计算次数        计算间隔
    ^ CPerf(i)            Tolf(i)           time(d)            direct(b)
    ? .每个file的指令数目   .一共有的文件数目    .完全生成的时间
   生成方向(true代表t_start -> t_end,false为反) ^ Ver(i)              R(d) G(d)
   B(d) ? 游戏版本             红                绿                  蓝 ^
   life(d)             light(i)          instant(b)         mode(i) ? 粒子寿命
   发光              是否瞬间生成          模式(colorblock:0,文件:1,混合:2)
*/
#define _PARAS ((::matrix &)(matr::paramatr &)(*this))
#define _POINTS ((::matrix &)(matr::matrix_temp &)(*this))
#define MAX_COUNTS 512
#define ERR_CK       \
    if (ans.iserr()) \
    return O_str::WRONG
static TCHAR *_str = new TCHAR[MAX_COUNTS]; //? 一个全局字符串

namespace O_str
{
    _TSTRING WRONG(_T("O_str.WRONG"));
    _TSTRING EMPTY(_T("O_str.EMPTY"));
} // namespace O_str

namespace
{
    matrix solved(matrix A, double x = 1, double y = 1, double z = 0)
    {
        while (A.size(2) > 1)
        {
            A.rsim(0, A.size(2) - 1, x, y, z, true);
            A.rdel(0);
        }
        return A;
    }
} // namespace

strmatr const Omatr::linear(void)
{
    if (!(_POINTS.size(1) >= 2 && _POINTS.size(2) >= 3))
        return O_str::WRONG;
    switch ((int)(_PARAS[3][3]))
    {
    case 0:
    { //? 即colorblock模式
        int b = (int)(_PARAS[2][0]);
        if (b == 1122)
        {
            //? 行只选前两行的前三个数字
            ::matrix left(2, 3), right(2, 2, 1.0);

            left[0][0] = _POINTS[0][0];
            left[1][0] = _POINTS[1][0];
            left[0][1] = _POINTS[0][1];
            left[1][1] = _POINTS[1][1];
            left[0][2] = _POINTS[0][2];
            left[1][2] = _POINTS[1][2];
            right[0][0] = _PARAS[0][0];
            right[1][0] = _PARAS[0][1];

            ::matrix funs;
            funs = left / right;

            if (funs.iserr())
                return O_str::WRONG;

            if (_PARAS[1][3])
                // particleex tickparameter <颗粒名> <x> <y> <z> <红> <绿> <蓝>
                // <透明度> <亮度> <vx> <vy> <vz> <tStart> <tEnd> <表达式>
                // [计算间隔] [CPT] [寿命] [速度表达式] [计算间隔] [组] [参数]
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f %.f 0 0 0 %.3f %.3f x=%.3f*t+%.3f;y=%.3f*t+%.3f;z=%.3f*t+%.3f %.3f %.f %.f"),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[3][1], _PARAS[0][0],
                    _PARAS[0][1], funs[0][0], funs[1][0], funs[0][1],
                    funs[1][1], funs[0][2], funs[1][2], _PARAS[0][3],
                    _PARAS[0][2], _PARAS[3][0]);
            else
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f %.f 0 0 0 %.3f %.3f x=%.3f*t+%.3f;y=%.3f*t+%.3f;z=%.3f*t+%.3f %.3f %.f %.f"),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[3][1], _PARAS[0][1],
                    _PARAS[0][0], funs[0][0], funs[1][0], funs[0][1],
                    funs[1][1], funs[0][2], funs[1][2], _PARAS[0][3],
                    _PARAS[0][2], _PARAS[3][0]);
            strmatr stma(_str, (paramatr &)(*this));
            return stma;
            //
        }
        else if (b == 1165)
        {
            //? 行只选前两行的前三个数字
            ::matrix left(2, 3), right(2, 2, 1.0);

            left[0][0] = _POINTS[0][0];
            left[1][0] = _POINTS[1][0];
            left[0][1] = _POINTS[0][1];
            left[1][1] = _POINTS[1][1];
            left[0][2] = _POINTS[0][2];
            left[1][2] = _POINTS[1][2];
            right[0][0] = _PARAS[0][0];
            right[1][0] = _PARAS[0][1];

            ::matrix funs;
            funs = left / right;

            if (funs.iserr())
                return O_str::WRONG;

            if (_PARAS[1][3])
                // /particleex tickparameter <颗粒> <坐标> <颜色> <速度> <begin>
                // <end> <表达式> [计算间隔] [CPT] [寿命] [速度表达式]
                // [计算间隔] [组]
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f 0 0 0 %.3f %.3f \"x= %.3f *t+ %.3f;y= %.3f *t+ %.3f;z= %.3f *t+ %.3f\" %.3f %.f %.f"),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[0][0], _PARAS[0][1],
                    funs[0][0], funs[1][0], funs[0][1], funs[1][1], funs[0][2],
                    funs[1][2], _PARAS[0][3], _PARAS[0][2], _PARAS[3][0]);
            else
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f 0 0 0 %.3f %.3f \"x= %.3f *t+ %.3f;y= %.3f *t+ %.3f;z= %.3f *t+ %.3f\" %.3f %.f %.f"),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[0][1], _PARAS[0][0],
                    funs[0][0], funs[1][0], funs[0][1], funs[1][1], funs[0][2],
                    funs[1][2], _PARAS[0][3], _PARAS[0][2], _PARAS[3][0]);

            strmatr stma(_str, (paramatr &)(*this));
            return stma;
            //
        }
        else
            return O_str::WRONG;
    }
    case 1:
    case 2:
    {
        return O_str::WRONG;
    }
    default:
        return O_str::WRONG;
    }
}

strmatr const Omatr::quadhet(double y, int mode)
{
    if (!(_POINTS.size(1) >= 2 && _POINTS.size(2) >= 3))
        return O_str::WRONG;
    switch ((int)(_PARAS[3][3]))
    {
    case 0:
    { //? 即colorblock模式
        int b = (int)(_PARAS[2][0]);
        if (b == 1122)
        {
            // mode=1为x抛物线 mode=2为y抛物线 mode=3为z抛物线
            if (mode < 0)
                mode = 0;
            if (mode > 2)
                mode = 2;
            if (y > 0)
                y = sqrt(y);
            else
                y = -pow(y, 2 / 3);
            double x = (_POINTS[0][mode] + _POINTS[1][mode]) / 2 - y;
            // mode切换
            ::matrix funs[3];
            for (int i = 0; i < 3; i++)
            {
                ::matrix left(2, 1), right(2, 2);
                if (i == mode)
                {
                    left[0][0] = _POINTS[0][i] - x;
                    left[1][0] = _POINTS[1][i] - x;
                    right[0][0] = _PARAS[0][0] * _PARAS[0][0];
                    right[0][1] = _PARAS[0][0];
                    right[1][0] = _PARAS[0][1] * _PARAS[0][1];
                    right[1][1] = _PARAS[0][1];

                    funs[i] = left / right;

                    if (funs[i].iserr())
                        return O_str::WRONG;

                    funs[i].rsim(0, 1, x, true);
                    funs[i].rdel(0);
                }
                else
                {
                    left[0][0] = _POINTS[0][i];
                    left[1][0] = _POINTS[1][i];
                    right[0][0] = _PARAS[0][0];
                    right[0][1] = 1;
                    right[1][0] = _PARAS[0][1];
                    right[1][1] = 1;

                    funs[i] = left / right;

                    if (funs[i].iserr())
                        return O_str::WRONG;

                    funs[i].rsim(0, 1, x, true);
                    funs[i].rdel(0);
                }
            }
            // particleex tickparameter <颗粒名> <x> <y> <z> <红> <绿> <蓝>
            // <透明度> <亮度> <vx> <vy> <vz> <tStart> <tEnd> <表达式>
            // [计算间隔] [CPT] [寿命] [速度表达式] [计算间隔] [组] [参数]
            if (_PARAS[1][3])
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f %.f 0 0 0 %.3f %.3f "),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[3][1], _PARAS[0][0],
                    _PARAS[0][1]);
            else
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f %.f 0 0 0 %.3f %.3f "),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[3][1], _PARAS[0][1],
                    _PARAS[0][0]);
            TCHAR c;
            for (int i = 0; i < 3; i++)
            {
                {
                    if (i == 0)
                        c = 'x';
                    else if (i == 1)
                        c = 'y';
                    else
                        c = 'z';
                }
                if (i == mode)
                {
                    _stprintf(_str + ::wcslen(_str), _T("%c= %.3f*t^2+%.3f*t+%.3f"), c,
                              funs[i][0][0], funs[i][1][0], x);
                }
                else
                {
                    _stprintf(_str + ::wcslen(_str), _T("%c=%.3f*t+%.3f"), c,
                              funs[i][0][0], funs[i][1][0]);
                }
                if (i != 2)
                    _stprintf(_str + ::wcslen(_str), _T(";"));
                else
                    continue;
            }
            _stprintf(_str + ::wcslen(_str), _T(" %.3f %.f %.f"), _PARAS[0][3],
                      _PARAS[0][2], _PARAS[3][0]);

            strmatr stma(_str, (paramatr &)(*this));
            return stma;
        }
        else if (b == 1165)
        {
            // mode=1为x抛物线 mode=2为y抛物线 mode=3为z抛物线
            if (mode < 0)
                mode = 0;
            if (mode > 2)
                mode = 2;
            if (y > 0)
                y = sqrt(y);
            else
                y = -pow(y, 2 / 3);
            double x = (_POINTS[0][mode] + _POINTS[1][mode]) / 2 - y;
            // mode切换
            ::matrix funs[3];
            for (int i = 0; i < 3; i++)
            {
                ::matrix left(2, 1), right(2, 2);
                if (i == mode)
                {
                    left[0][0] = _POINTS[0][i] - x;
                    left[1][0] = _POINTS[1][i] - x;
                    right[0][0] = _PARAS[0][0] * _PARAS[0][0];
                    right[0][1] = _PARAS[0][0];
                    right[1][0] = _PARAS[0][1] * _PARAS[0][1];
                    right[1][1] = _PARAS[0][1];

                    funs[i] = left / right;

                    if (funs[i].iserr())
                        return O_str::WRONG;

                    funs[i].rsim(0, 1, x, true);
                    funs[i].rdel(0);
                }
                else
                {
                    left[0][0] = _POINTS[0][i];
                    left[1][0] = _POINTS[1][i];
                    right[0][0] = _PARAS[0][0];
                    right[0][1] = 1;
                    right[1][0] = _PARAS[0][1];
                    right[1][1] = 1;

                    funs[i] = left / right;

                    if (funs[i].iserr())
                        return O_str::WRONG;

                    funs[i].rsim(0, 1, x, true);
                    funs[i].rdel(0);
                }
            }
            // /particleex tickparameter <颗粒> <坐标> <颜色> <速度> <begin>
            // <end> <表达式> [计算间隔] [CPT] [寿命]
            if (_PARAS[1][3])
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f 0 0 0 %.3f %.3f "),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[0][0],
                    _PARAS[0][1]);
            else
                _stprintf(
                    _str,
                    _T("particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.3f 0 0 0 %.3f %.3f "),
                    matr::paramatr::par_name().c_str(), _PARAS[2][1],
                    _PARAS[2][2], _PARAS[2][3], 1.0, _PARAS[0][1],
                    _PARAS[0][0]);
            TCHAR c;
            for (int i = 0; i < 3; i++)
            {
                {
                    if (i == 0)
                        c = 'x';
                    else if (i == 1)
                        c = 'y';
                    else
                        c = 'z';
                }
                if (i == 0)
                    _stprintf(_str + ::wcslen(_str), _T("\""));
                if (i == mode)
                {
                    _stprintf(_str + ::wcslen(_str), _T("%c= %.3f *t^2+ %.3f *t+ %.3f"), c,
                              funs[i][0][0], funs[i][1][0], x);
                }
                else
                {
                    _stprintf(_str + ::wcslen(_str), _T("%c= %.3f *t+ %.3f"), c,
                              funs[i][0][0], funs[i][1][0]);
                }
                if (i != 2)
                    _stprintf(_str + ::wcslen(_str), _T(";"));
                else
                    _stprintf(_str + ::wcslen(_str), _T("\""));
            }
            _stprintf(_str + ::wcslen(_str), _T(" %.3f %.f %.f"), _PARAS[0][3],
                      _PARAS[0][2], _PARAS[3][0]);

            strmatr stma(_str, (paramatr &)(*this));
            return stma;
        }
        else
        {
            return O_str::WRONG;
        }
    }
    case 1:
    case 2:
    {
        return O_str::WRONG;
    }
    default:
        return O_str::WRONG;
    }
}

strmatr const Omatr::quadthr(double dig, bool x)
{
    using namespace std;
    if (!(_POINTS.size(1) >= 3 && _POINTS.size(2) >= 3))
        return O_str::WRONG;
    switch ((int)(_PARAS[3][3]))
    {
    case 0:
    { //? 即colorblock模式
        int b = (int)(_PARAS[2][0]);
        if (b == 1122 || b == 1165)
        {
            if (fabs(((_POINTS[1][1] - _POINTS[0][1]) *
                      (_POINTS[2][0] - _POINTS[1][0])) -
                     ((_POINTS[2][1] - _POINTS[1][1]) *
                      (_POINTS[1][0] - _POINTS[0][0]))) < _POINTS.matr_error &&
                fabs(((_POINTS[1][2] - _POINTS[0][2]) *
                      (_POINTS[2][0] - _POINTS[1][0])) -
                     ((_POINTS[2][2] - _POINTS[1][2]) *
                      (_POINTS[1][0] - _POINTS[0][0]))) < _POINTS.matr_error)
                return linear();
            //? 下面进行平面方程的计算
            ::matrix right(3, 4, 1.0), left(3, 1), ans;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    right[i][j] = _POINTS[i][j];
            ans = left / right;
            ERR_CK;

            ::matrix bas_z = solved(ans).ldel(3);
            double temp1[] = {_POINTS[1][0] - _POINTS[0][0],
                              _POINTS[1][1] - _POINTS[0][1],
                              _POINTS[1][2] - _POINTS[0][2]};
            ::matrix bas_x(3, 1, temp1, 3);

            left.trans(2, 1, 0.0);
            right.trans(2, 3, 0.0);

            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 3; j++)
                {
                    if (i == 0)
                        right[i][j] = bas_z[j][0];
                    else
                        right[i][j] = bas_x[j][0];
                }
            ans = left / right;
            ERR_CK;

            ::matrix bas_y = solved(ans);

            double leng[3] = {sqrt(pow(bas_x[0][0], 2) + pow(bas_x[1][0], 2) +
                                   pow(bas_x[2][0], 2)),
                              sqrt(pow(bas_y[0][0], 2) + pow(bas_y[1][0], 2) +
                                   pow(bas_y[2][0], 2)),
                              sqrt(pow(bas_z[0][0], 2) + pow(bas_z[1][0], 2) +
                                   pow(bas_z[2][0], 2))};

            bas_x = bas_x *
                    ((fabs(leng[0]) < _POINTS.matr_error) ? 1 : (1 / leng[0]));
            bas_y = bas_y *
                    ((fabs(leng[1]) < _POINTS.matr_error) ? 1 : (1 / leng[1]));
            bas_z = bas_z *
                    ((fabs(leng[2]) < _POINTS.matr_error) ? 1 : (1 / leng[2]));

            left.trans(3, 2, 0.0);
            right.trans(3, 2, 0.0);

            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 3; j++)
                {
                    left[j][i] = _POINTS[i + 1][j] - _POINTS[0][j];
                    if (i == 0)
                        right[j][i] = bas_x[j][0];
                    else
                        right[j][i] = bas_y[j][0];
                }

            ans = left / right;
            ERR_CK;

            ::matrix bas_points(ans);

            ::matrix A_T(2, 2);
            int temp3;
            if (x)
                temp3 = -1;
            else
                temp3 = 1;
            A_T[0][0] = cos(dig), A_T[0][1] = sin(dig),
            A_T[1][0] = temp3 * -1 * sin(dig), A_T[1][1] = temp3 * cos(dig);

            A_T = A_T ^ _TM;

            if (A_T.rank() != 2)
                A_T.trans(2, matr_tag::I);
            ::matrix shif_points;
            ans = A_T ^ -1;
            ERR_CK;

            shif_points = ans * bas_points;

            left.trans(3, 1, 0.0);
            right.trans(3, 3, 0.0);

            right[0][0] = pow(shif_points[0][0], 2);
            right[0][1] = shif_points[0][0];
            right[0][2] = 1;
            left[0][0] = shif_points[1][0];
            right[1][0] = pow(shif_points[0][1], 2);
            right[1][1] = shif_points[0][1];
            right[1][2] = 1;
            left[1][0] = shif_points[1][1];
            right[2][2] = 1;

            ans = left / right;
            ERR_CK;
            ::matrix parafun = solved(ans);

            left.trans(3, 3, 0.0);

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (i == 0)
                        left[j][i] = bas_x[j][0];
                    else if (i == 1)
                        left[j][i] = bas_y[j][0];
                    else
                        left[j][i] = bas_z[j][0];
            double temp2[] = {A_T[0][0], A_T[0][1], 0, A_T[1][0], A_T[1][1],
                              0, 0, 0, 1};
            right.trans(3, 3, temp2, 9);

            ans = left * right;
            // ans = ans ^ -1;
            ERR_CK;

            right.trans(3, 3, 0.0);

            right[0][1] = 1;
            right[1][0] = parafun[0][0];
            right[1][1] = parafun[1][0];
            right[1][2] = parafun[2][0];

            ::matrix parafun_fin;

            parafun_fin = ans * right;
            for (int i = 0; i < 3; i++)
                parafun_fin[i][2] = _POINTS[0][i];

            ::matrix xmima(2, 1);
            right.trans(2, 2, 1);
            temp2[0] = shif_points[0][0];
            temp2[1] = shif_points[0][1];
            temp2[2] = 0;
            ::matrix xl(3, 1, temp2, 3);
            xmima[0][0] = xl.min_num();
            xmima[1][0] = xl.max_num();
            right[0][0] = _PARAS[0][0];
            right[1][0] = _PARAS[0][1];

            ans = xmima / right;
            ans = solved(ans);

            if (b == 1122)
            {
                _stprintf(
                    _str,
                    _T("/particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.f %.f 0 0 0 %.3f %.3f x= %f*(%f*t+%f)^2+%f*(%f*t+%f)+%f;y=%f*(%f*t+%f)^2+%f*(%f*t+%f)+%f;z=%f*(%f*t+%f)^2+%f*(%f*t+%f)+%f %f %.f %.f"),
                    paramatr::par_name().c_str(), _PARAS[2][1], _PARAS[2][2],
                    _PARAS[2][3], (double)1, _PARAS[3][1], _PARAS[0][0],
                    _PARAS[0][1], parafun_fin[0][0], ans[0][0], ans[1][0],
                    parafun_fin[0][1], ans[0][0], ans[1][0], parafun_fin[0][2],
                    parafun_fin[1][0], ans[0][0], ans[1][0], parafun_fin[1][1],
                    ans[0][0], ans[1][0], parafun_fin[1][2], parafun_fin[2][0],
                    ans[0][0], ans[1][0], parafun_fin[2][1], ans[0][0],
                    ans[1][0], parafun_fin[2][2], _PARAS[0][3], _PARAS[0][2],
                    _PARAS[3][0]);
            }
            else
            {
                _stprintf(
                    _str,
                    _T("/particleex tickparameter %s 0 0 0 %.3f %.3f %.3f %.f 0 0 0 %.3f %.3f \"x= %f *( %f *t+ %f )^2+ %f *( %f *t+ %f )+ %f;y= %f *( %f *t+ %f )^2+ %f *( %f *t+ %f )+ %f;z= %f *( %f *t+ %f )^2+ %f *( %f *t+ %f )+ %f\" %f %.f %.f"),
                    paramatr::par_name().c_str(), _PARAS[2][1], _PARAS[2][2],
                    _PARAS[2][3], (double)1, _PARAS[0][0], _PARAS[0][1],
                    parafun_fin[0][0], ans[0][0], ans[1][0], parafun_fin[0][1],
                    ans[0][0], ans[1][0], parafun_fin[0][2], parafun_fin[1][0],
                    ans[0][0], ans[1][0], parafun_fin[1][1], ans[0][0],
                    ans[1][0], parafun_fin[1][2], parafun_fin[2][0], ans[0][0],
                    ans[1][0], parafun_fin[2][1], ans[0][0], ans[1][0],
                    parafun_fin[2][2], _PARAS[0][3], _PARAS[0][2],
                    _PARAS[3][0]);
            }

            strmatr temp(_str, (paramatr &)(*this));
            return temp;

            /* 0.314165t^2+-1.075699t, -0.452050t^2+2.583027t,
            -0.556776t^2+1.618614t, t, -20, 20 setlocale(LC_ALL, "");
            wprintf(L"曲线(%f*(%f*t+%f)^2+%f*(%f*t+%f)+%f,%f*(%f*t+%f)^2+%f*(%f*t+%f)+%f,%f*(%f*t+%f)^2+%f*(%f*t+%f)+%f,t,%f,%f)",
                    parafun_fin[0][0], ans[0][0], ans[1][0], parafun_fin[0][1],
            ans[0][0], ans[1][0], parafun_fin[0][2], parafun_fin[1][0],
            ans[0][0], ans[1][0], parafun_fin[1][1], ans[0][0], ans[1][0],
            parafun_fin[1][2], parafun_fin[2][0], ans[0][0], ans[1][0],
            parafun_fin[2][1], ans[0][0], ans[1][0], parafun_fin[2][2],
                    _PARAS[0][0], _PARAS[0][1]);
            strmatr stma(_str, (paramatr &)(*this));
            return stma;
            */
        }
        else
            return O_str::WRONG;
    }
    case 1:
    case 2:
        return O_str::WRONG;
    default:
        return O_str::WRONG;
    }
}
#undef _PARAS
#undef _POINTS
#undef MAX_COUNTS
#undef ERR_CK