// 矩阵库的类代码重写,库实现文件
#include "basic_matr_class.h"
#include <fstream>
#include <ios>
// using namespace drl;
namespace matr
{
    drl::matrix I(3, _IM);
    drl::matrix II(3, _IN);
    drl::matrix Err(3, _Er);
    drl::matrix Empty(3, 3);
} // namespace matr

drl::matrix::matrix(void)
{
    ::matr_init(&mar, 3, 3, NULL, 0);
    inited = true;
}
drl::matrix::matrix(int c_line, int c_raw, const double *cont, int cont_init)
{
    if (c_raw < 0)
        c_raw = c_line;
    if (cont_init < 0)
        cont_init = c_line * c_raw;
    cont_init = std::min(cont_init, c_line * c_raw);
    ::matr_init(&mar, c_line, c_raw, cont, cont_init);
    inited = true;
}
drl::matrix::matrix(int c_line, int c_raw, double init_num)
{
    if (c_raw == -2)
        c_raw = c_line;
    ::matr_init(&mar, c_line, c_raw, NULL, 0);
    for (int i = 0; i < c_line; i++)
        for (int j = 0; j < c_raw; j++)
            mar.pos[i][j] = init_num;
    inited = true;
}
drl::matrix::matrix(int c_lr, matr_tag tag)
{
    switch (tag)
    {
    case matr_tag::I:
    {
        ::matr_init(&mar, c_lr, c_lr, NULL, 0);
        for (int i = 0; i < c_lr; i++)
            mar.pos[i][i] = 1;
        inited = true;
        break;
    }

    case matr_tag::II:
    {
        ::matr_init(&mar, c_lr, c_lr, NULL, 0);
        for (int i = 0; i < c_lr; i++)
            mar.pos[i][i] = -1;
        inited = true;
        break;
    }

    case matr_tag::Err:
    {
        int zero = 0;
        ::matr_init(&mar, c_lr, c_lr, NULL, 0);
        for (int i = 0; i < c_lr; i++)
            mar.pos[i][i] /= zero;
        inited = true;
        nand = true;
        break;
    }

    case matr_tag::SP:
    {
        ::matr_init(&mar, c_lr, 3, NULL, 0);
        inited = true;
        break;
    }

    case matr_tag::PP:
    {
        ::matr_init(&mar, c_lr, 2, NULL, 0);
        inited = true;
        break;
    }
    default:
    {
        ::matr_init(&mar, c_lr, c_lr, NULL, 0);
        inited = true;
    }
    }
}
double drl::matrix::matr_rand_max = 65535;
double drl::matrix::matr_rand_min = 0;
int drl::matrix::matr_rand_max_intager = INT_MAX;
int drl::matrix::matr_rand_min_intager = INT_MIN;
drl::matrix::matrix(int c_l, int c_r, matr_tag tag)
{
    switch (tag)
    {
    case matr_tag::RAN:
    {
        ::matr_init(&mar, c_l, c_r, NULL, 0);
        static std::mt19937 randst(time(nullptr));
        std::uniform_real_distribution<double> dis(matr_rand_min,
                                                   matr_rand_max);
        for (int i = 0; i < c_l; i++)
            for (int j = 0; j < c_r; j++)
                mar.pos[i][j] = dis(randst);
        inited = true;
        break;
    }
    case matr_tag::IRAN:
    {
        ::matr_init(&mar, c_l, c_r, NULL, 0);
        static std::default_random_engine randst(time(nullptr));
        std::uniform_int_distribution<long long> dis(matr_rand_min_intager,
                                                     matr_rand_max_intager);
        for (int i = 0; i < c_l; i++)
            for (int j = 0; j < c_r; j++)
                mar.pos[i][j] = dis(randst);
        inited = true;
        break;
    }
    default:
    {
        ::matr_init(&mar, c_l, c_r, NULL, 0);
        inited = true;
    }
    }
}
drl::matrix::~matrix()
{
    free();
}
drl::matrix::matrix(drl::matrix const &ma_sor)
{
    ::matr_init(&mar, ma_sor.mar.count_l, ma_sor.mar.count_r, NULL, 0);
    ::matr_copy(&mar, &ma_sor.mar);
    inited = true;
    nand = ma_sor.nand;
}
drl::matrix::matrix(const mat &&ma_sor)
{
    mar = ma_sor.mar;
    inited = true;
    nand = false;
    *const_cast<double ***>(&(ma_sor.mar.pos)) = NULL;
}

drl::matrix::matrix(const unit_iterator &lhs, const unit_iterator &rhs,
                    int c_line, int c_raw, int cont_init)
{
    auto x = std::min(lhs, rhs);
    auto y = std::max(lhs, rhs);
    if (c_line <= 0 && c_raw <= 0)
    {
        c_line = 1;
        c_raw = y - x;
    }
    else if (c_line > 0 && c_raw <= 0)
        c_raw = c_line;
    if (cont_init <= 0)
        cont_init = c_line * c_raw;
    int e = y - x;
    e = std::min(e, cont_init);
    e = std::min(e, c_line * c_raw);
    ::matr_init(&mar, c_line, c_raw, NULL, 0);
    for (int i = 0; i < e; i++)
        mar.pos[i / c_raw][i % c_raw] = lhs[i];
    inited = true;
    nand = false;
}
drl::matrix::matrix(const line_reference &line, int c_line, int c_raw,
                    int cont_init)
{
    if (c_line <= 0 && c_raw <= 0)
    {
        c_line = 1;
        c_raw = line.size();
    }
    else if (c_line > 0 && c_raw <= 0)
        c_raw = c_line;
    if (cont_init <= 0)
        cont_init = c_raw * c_line;
    int e = line.size();
    e = std::min(e, cont_init);
    e = std::min(e, c_line * c_raw);
    ::matr_init(&mar, c_line, c_raw, NULL, 0);
    for (int i = 0; i < e; i++)
    {
        mar.pos[i / c_raw][i % c_raw] = line.core()->operator[](line.pos())[i];
    }
    inited = true;
    nand = false;
}

drl::matrix::matrix(const raw_reference &line, int c_line, int c_raw,
                    int cont_init)
{
    if (c_line <= 0 && c_raw <= 0)
    {
        c_line = line.size();
        c_raw = 1;
    }
    else if (c_line > 0 && c_raw <= 0)
        c_raw = c_line;
    if (cont_init <= 0)
        cont_init = c_raw * c_line;
    int e = line.size();
    e = std::min(e, cont_init);
    e = std::min(e, c_line * c_raw);
    ::matr_init(&mar, c_line, c_raw, NULL, 0);
    for (int i = 0; i < e; i++)
    {
        mar.pos[i / c_raw][i % c_raw] = line.core()->operator[](i)[line.pos()];
    }
    inited = true;
    nand = false;
}

drl::matrix::matrix(double start, double end, double delta, int line, int raw)
{
    if (line < 0)
        line = 1;
    if ((end - start > 0 && delta < 0) || (end - start < 0 && delta > 0) ||
        (end - start > 0 && delta > end - start) ||
        (end - start < 0 && delta < end - start))
    {
        ::matr_init(&mar, 1, 2, NULL, 0);
        mar.pos[0][0] = start;
        mar.pos[0][1] = end;
        inited = true;
        nand = false;
    }
    else
    {
        double count = (end - start) / delta;
        if (count > floor(count) + matr_error)
            count = ceil(count) + 1;
        else
            count = floor(count) + 1;
        if (raw < 0)
            raw = (int)count / line + (((int)count % line) ? 1 : 0);
        ::matr_init(&mar, line, raw, NULL, 0);
        for (int i = 0; i < line; i++)
            for (int j = 0; j < raw; j++)
                if (count - 1 <= (i * raw + j))
                    mar.pos[i][j] = end;
                else
                    mar.pos[i][j] = start + (i * raw + j) * delta;
        inited = true;
        nand = false;
    }
}
drl::matrix::matrix(double start, double end, int count)
{
    if (count < 2)
        count = 2;
    double delta = (end - start) / (count - 1);
    ::matr_init(&mar, 1, count, NULL, 0);
    for (int i = 0; i < count; i++)
        if (i == count - 1)
            mar.pos[0][i] = end;
        else
            mar.pos[0][i] = start + i * delta;
    inited = true;
    nand = false;
}
drl::matrix::matrix(double start, double end, int line, int raw)
{
    if (raw < 0)
        raw = line;
    double delta = (end - start) / (line * raw - 1);
    ::matr_init(&mar, line, raw, NULL, 0);
    for (int i = 0; i < line; i++)
        for (int j = 0; j < raw; j++)
            if (i == line - 1 && j == raw - 1)
                mar.pos[i][j] = end;
            else
                mar.pos[i][j] = start + (raw * i + j) * delta;
    inited = true;
    nand = false;
}

drl::matrix &drl::matrix::operator=(drl::matrix const &ma_sor)
{
    if ((&ma_sor != this) && ((*this).free() == true))
    {
        double *lined = nullptr;
        int all = ma_sor.mar.count_l * ma_sor.mar.count_r;
        ::matr_dou2lin(&lined, ma_sor.mar.pos, ma_sor.mar.count_l,
                       ma_sor.mar.count_r);
        ::matr_init(&mar, ma_sor.mar.count_l, ma_sor.mar.count_r, lined, all);
        ::free(lined);
        inited = true;
        nand = ma_sor.nand;
        return *this;
    }
    else
        return *this;
}
drl::matrix &drl::matrix::operator=(const drl::matrix &&ma_sor)
{
    if ((&ma_sor != this) && (free() == true))
    {
        mar = ma_sor.mar;
        *const_cast<double ***>(&(ma_sor.mar.pos)) = nullptr;
        inited = ma_sor.inited;
        nand = ma_sor.nand;
        return *this;
    }
    else
        return *this;
}
const drl::matrix drl::matrix::operator+(drl::matrix const &ma_sor) const
{
    if (mar.count_l == ma_sor.mar.count_l && mar.count_r == ma_sor.mar.count_r)
    {
        mat temp1(*this);
        mat temp2(ma_sor);
        double add[3] = {1, 1, 0};
        ::matr_lin(&(temp1.mar), &(temp2.mar), add);
        return temp1;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator-(drl::matrix const &ma_sor) const
{
    if (mar.count_l == ma_sor.mar.count_l && mar.count_r == ma_sor.mar.count_r)
    {
        drl::matrix temp1(*this);
        drl::matrix temp2(ma_sor);
        double add[3] = {1, -1, 0};
        ::matr_lin(&(temp1.mar), &(temp2.mar), add);
        return temp1;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator*(drl::matrix const &ma_sor) const
{
    ::Mat temp1;
    ::matr_init(&temp1, 1, 1, NULL, 0);
    ::Mat *tempptr;
    tempptr = ::matr_mul(&mar, &(ma_sor.mar), &temp1);
    if (tempptr != NULL)
    {
        double *temp2 = nullptr;
        ::matr_dou2lin(&temp2, temp1.pos, temp1.count_l, temp1.count_r);
        drl::matrix temp3{temp1.count_l, temp1.count_r, temp2,
                          temp1.count_l * temp1.count_r};
        ::free(temp2);
        ::matr_free(&temp1);
        return temp3;
    }
    else
        return matr::Err;
}
static int mo = 0;
const drl::matrix drl::matrix::operator/(drl::matrix const &ma_sor) const
{
    int zero = 0;
    if (mar.count_l == ma_sor.mar.count_l)
        if (mar.count_r == 1)
        {
            ::Mat temp1;
            mo = ::matr_perf_sol(&(ma_sor.mar), &mar, matr_error, &temp1);
            double *temp2 = nullptr;
            ::matr_dou2lin(&temp2, temp1.pos, temp1.count_l, temp1.count_r);
            drl::matrix temp3{temp1.count_l, temp1.count_r, temp2,
                              temp1.count_l * temp1.count_r};
            ::free(temp2);
            ::matr_free(&temp1);
            temp3 = temp3 ^ _TM;
            return temp3;
        }
        else if (mar.count_r > 1)
        {
            drl::matrix temp2(ma_sor.mar.count_r, mar.count_r);
            drl::matrix temp3(mar.count_l, 1);
            drl::matrix temp4;
            for (int i = 0; i < mar.count_r; i++)
            {
                for (int j = 0; j < mar.count_l; j++)
                    temp3[j][0] = mar.pos[j][i];
                temp4 = temp3 / ma_sor;
                for (int j = 0; j < ma_sor.mar.count_r; j++)
                    for (int k = 0; k < temp4.mar.count_r; k++)
                        if (mo >= 0)
                            temp2[j][i] += temp4[j][k];
                        else
                        {
                            temp2[j][i] /= zero;
                            temp2.nand = true;
                        }
            }
            return temp2;
        }
        else
            return matr::Err;
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator*(double q) const
{
    ::Mat temp1;
    double *temp2;
    ::matr_dou2lin(&temp2, mar.pos, mar.count_l, mar.count_r);
    ::matr_init(&temp1, mar.count_l, mar.count_r, temp2,
                mar.count_l * mar.count_r);
    double temp3[3] = {q, 0, 0};
    ::matr_lin(&temp1, &temp1, temp3);
    ::free(temp2);
    ::matr_dou2lin(&temp2, temp1.pos, temp1.count_l, temp1.count_r);
    drl::matrix temp4{temp1.count_l, temp1.count_r, temp2,
                      temp1.count_l * temp1.count_r};
    ::matr_free(&temp1);
    return temp4;
}
const drl::matrix drl::operator*(double q, drl::matrix const &ma_sor)
{
    return ma_sor * q;
}
const double *const drl::matrix::operator[](int x) const
{
    if (x < mar.count_l)
        return mar.pos[x];
    else
        return nullptr;
}
double *const drl::matrix::operator[](int x)
{
    if (x < mar.count_l)
        return mar.pos[x];
    else
        return nullptr;
}
const drl::matrix drl::matrix::operator&(drl::matrix const &ma_sor) const
{
    drl::matrix A = *this;
    if (size(1) == ma_sor.size(1) && size(2) == ma_sor.size(2))
    {
        for (int i = 0; i < size(1); i++)
            for (int j = 0; j < size(2); j++)
                A[i][j] *= ma_sor[i][j];
        return A;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator^(int x) const
{
    if (size(1) == size(2))
    {
        if (x >= 0)
        {
            drl::matrix temp1;
            temp1.trans(size(1), matr_tag::I);
            for (int i = 0; i < x; i++)
                temp1 = temp1 * (*this);
            return temp1;
        }
        else if (size(1) == rank())
        {
            if (x == -1)
            {
                drl::matrix I(size(1), matr_tag::I);
                drl::matrix temp2;
                temp2 = I / *this;
                return temp2;
            }
            else
            {
                drl::matrix I(size(1), matr_tag::I);
                drl::matrix temp2;
                temp2 = I / *this;
                temp2 = temp2 ^ (-x);
                return temp2;
            }
        }
        else
            return matr::Err;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator^(matr_tag tag) const
{
    switch (tag)
    {
    case matr_tag::T:
    {
        double *p_d = nullptr;
        ::matr_dou2lin(&p_d, mar.pos, mar.count_l, mar.count_r);
        drl::matrix temp1(mar.count_r, mar.count_l);
        for (int i = 0; i < mar.count_r; i++)
            for (int j = 0; j < mar.count_l; j++)
                temp1[i][j] = (*this)[j][i];
        ::free(p_d);
        return temp1;
    }
    case matr_tag::P:
    {
        if (mar.count_l == mar.count_r)
        {
            drl::matrix temp1(mar.count_l, mar.count_r);
            for (int i = 0; i < mar.count_l; i++)
                for (int j = 0; j < mar.count_r; j++)
                    temp1[i][j] = ::pow(-1, i + j) * (*this).Rdet(i, j).det();
            temp1 = temp1 ^ _TM;
            return temp1;
        }
        else
            return matr::Err;
    }
    case matr_tag::LIN:
    {
        return lrev();
    }
    case matr_tag::RAW:
    {
        return rrev();
    }
    default:
        return matr::Err;
    }
}
const drl::matrix drl::operator-(drl::matrix const &ma_sor)
{
    return -1 * ma_sor;
}
const drl::matrix drl::matrix::operator+(const double x) const
{
    for (auto i = begin(); i < end(); i++)
        *i += x;
    return *this;
}
const drl::matrix drl::matrix::operator-(const double x) const
{
    for (auto i = begin(); i < end(); i++)
        *i -= x;
    return *this;
}
const drl::matrix drl::matrix::operator/(const double x) const
{
    for (auto i = begin(); i < end(); i++)
        *i /= x;
    return *this;
}
const drl::matrix drl::matrix::operator%(const int x) const
{
    for (auto i = begin(); i < end(); i++)
        *i = (int)*i % (int)x;
    return *this;
}
const drl::matrix drl::matrix::operator^(const double x) const
{
    for (auto i = begin(); i < end(); i++)
        *i = pow(*i, x);
    return *this;
}
const double drl::matrix::det(void) const
{
    int zero = 0;
    if (mar.count_l == mar.count_r && mar.count_l > 0 && mar.count_r > 0)
    {
        if (mar.count_r > 1)
        {
            double temp1 = 0;
            drl::matrix temp2;
            for (int i = 0; i < mar.count_r; i++)
            {
                temp2 = Rdet(0, i);
                temp1 += (::pow(-1, i) * temp2.det() * (*this)[0][i]);
            }
            return temp1;
        }
        else
            return (*this)[0][0];
    }
    else
        return 1.0 / zero;
}
const drl::matrix drl::matrix::Rdet(int x, int y) const
{
    if (x >= 0 && y >= 0 && x < mar.count_l && y < mar.count_l)
    {
        bool t;
        drl::matrix temp1(mar.count_l - 1, mar.count_r - 1);
        for (int i = 0, i1 = 0; i < mar.count_l; i++)
        {
            for (int j = 0, j1 = 0; j < mar.count_r; j++)
            {
                if (i == x || j == y)
                    t = false;
                else
                {
                    t = true;
                    temp1[i1][j1] = (*this)[i][j];
                }
                if (t)
                {
                    if (j1 < temp1.mar.count_r - 1)
                        j1++;
                    else
                    {
                        i1++;
                        j1 = 0;
                    }
                }
                else
                    continue;
            }
        }
        return temp1;
    }
    else
        return matr::Err;
}

//? 行列抽取
const drl::matrix drl::matrix::exra(int tar, int dim) const
{
    switch (dim)
    {
    case 1:
    {
        if (tar >= 0 && tar < mar.count_l)
        {
            drl::matrix temp1(1, mar.count_r, mar.pos[tar], mar.count_r);
            return temp1;
            break;
        }
        else
            return matr::Err;
    }
    case 2:
    {
        if (tar >= 0 && tar < mar.count_r)
        {
            drl::matrix temp2(mar.count_l, 1);
            for (int i = 0; i < mar.count_l; i++)
                temp2[i][0] = mar.pos[i][tar];
            return temp2;
            break;
        }
        else
            return matr::Err;
    }
    default:
        return matr::Err;
    }
}
//? 行初等
const drl::matrix drl::matrix::lsim(int sor, int tar, double a, double b,
                                    double c, bool exc)
{
    if (sor >= 0 && tar >= 0 && sor < mar.count_l && tar < mar.count_l)
    {
        drl::matrix ma = (*this);
        double temp1[] = {a, b, c};
        ::matr_l_lin(&(ma.mar), sor, tar, temp1);
        if (exc == true)
            (*this) = ma;
        return ma;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::rsim(int sor, int tar, double a, double b,
                                    double c, bool exc)
{
    if (sor >= 0 && tar >= 0 && sor < mar.count_r && tar < mar.count_r)
    {
        drl::matrix ma = (*this);
        for (int i = 0; i < mar.count_l; i++)
            ma[i][tar] = a * ma[i][sor] + b * ma[i][tar] + c;
        if (exc == true)
            (*this) = ma;
        return ma;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::lexc(int sor, int tar, bool exc)
{
    if (sor >= 0 && tar >= 0 && sor < mar.count_l && tar < mar.count_l)
    {
        drl::matrix ma = (*this);
        ::matr_l_exc(&(ma.mar), sor, tar);
        if (exc == true)
            (*this) = ma;
        return ma;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::rexc(int sor, int tar, bool exc)
{
    if (sor >= 0 && tar >= 0 && sor < mar.count_r && tar < mar.count_r)
    {
        drl::matrix ma = (*this);
        ma = ma ^ _TM;
        ::matr_l_exc(&(ma.mar), sor, tar);
        ma = ma ^ _TM;
        if (exc == true)
            (*this) = ma;
        return ma;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::ldel(int tar, bool exc)
{
    if (size(1) == 1)
        return matr::Err;
    else if (tar >= 0 && tar < mar.count_l)
    {
        drl::matrix ma(mar.count_l - 1, mar.count_r);
        drl::matrix line;
        for (int i = 0; i < size(1); i++)
        {
            if (i == tar)
                continue;
            else
            {
                line = exra(i);
                for (int j = 0; j < size(2); j++)
                {
                    if (i > tar)
                        ma[i - 1][j] = line[0][j];
                    else
                        ma[i][j] = line[0][j];
                }
            }
        }
        if (exc == true)
            (*this) = ma;
        return ma;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::rdel(int tar, bool exc)
{
    if (size(2) == 1)
        return matr::Err;
    else if (tar >= 0 && tar < mar.count_r)
    {
        drl::matrix ma(mar.count_l, mar.count_r - 1);
        drl::matrix raw;
        for (int i = 0; i < size(2); i++)
        {
            if (i == tar)
                continue;
            else
            {
                raw = exra(i, 2);
                for (int j = 0; j < size(1); j++)
                {
                    if (i > tar)
                        ma[j][i - 1] = raw[j][0];
                    else
                        ma[j][i] = raw[j][0];
                }
            }
        }
        if (exc == true)
            (*this) = ma;
        return ma;
    }
    else
        return matr::Err;
}

const bool drl::matrix::operator==(mat const &ma) const
{
    bool temp = true;
    if (ma.size(1) == size(1) && ma.size(2) == size(2))
        for (int i = 0; i < size(1); i++)
            for (int j = 0; j < size(2); j++)
                if (fabs(operator[](i)[j] - ma[i][j]) > matr_error &&
                    fabs(operator[](i)[j] - ma[i][j]) > ma.matr_error)
                    return false;
                else
                    continue;
    else
        return false;
    if (temp)
        return temp;
    else
        return false;
}
double drl::matrix::unit_iterator::error_nan = nan("quiet");
double &drl::matrix::unit_iterator::operator*() const
{
    if (pos >= (*mar).size(0))
        return error_nan; // nan
    int x = pos / (*mar).size(2);
    int y = pos % (*mar).size(2);
    return (*(const_cast<drl::matrix *>(mar)))[x][y];
}

double &drl::matrix::unit_iterator::operator[](int x) const
{
    if (pos + x >= (*mar).size(0))
        return error_nan;
    int q = pos + x;
    int x1 = q / (*mar).size(2);
    int y1 = q % (*mar).size(2);
    return (*(const_cast<drl::matrix *>(mar)))[x1][y1];
}

const drl::matrix::line_reference &
drl::matrix::line_reference::operator=(const line_reference &line_ref)
{
    if (pc == 2)
        if (line_ref.x == 1)
        {
            int temp = ::fmin(pmar.mar->size(2), line_ref.pmar.cmar->size(2));
            for (int i = 0; i < temp; i++)
                (*pmar.mar)[x][i] = (*(line_ref.pmar.cmar))[line_ref.x][i];
            return *this;
        }
        else
        {
            int temp = ::fmin(pmar.mar->size(2), line_ref.pmar.mar->size(2));
            for (int i = 0; i < temp; i++)
                (*pmar.mar)[x][i] = (*(line_ref.pmar.mar))[line_ref.x][i];
            return *this;
        }
    else
        return *this;
}

const drl::matrix::raw_reference &
drl::matrix::raw_reference::operator=(const raw_reference &raw_ref)
{
    size_t temp = ::fmin(mar->size(1), raw_ref.mar->size(1));
    for (int i = 0; i < temp; i++)
        (*mar)[i][x] = (*(raw_ref.mar))[i][raw_ref.x];
    return *this;
}

const drl::matrix drl::matrix::lrev(bool exc)
{
    if (exc)
    {
        drl::matrix temp(size(1), size(2));
        for (int i = 0; i < size(1); i++)
            temp.line_begin()[i] = line_end() - i - 1;
        *this = temp;
        return temp;
    }
    else
    {
        drl::matrix temp(size(1), size(2));
        for (int i = 0; i < size(1); i++)
            temp.line_begin()[i] = line_end() - i - 1;
        return temp;
    }
}

const drl::matrix drl::matrix::rrev(bool exc)
{
    if (exc)
    {
        drl::matrix temp(size(1), size(2));
        for (int i = 0; i < size(2); i++)
            temp.raw_begin()[i] = raw_end() - i - 1;
        *this = temp;
        return temp;
    }
    else
    {
        drl::matrix temp(size(1), size(2));
        for (int i = 0; i < size(2); i++)
            temp.raw_begin()[i] = raw_end() - i - 1;
        return temp;
    }
}

const drl::matrix drl::matrix::lins(const line_reference &sor, int tar,
                                    bool exc)
{
    if (tar < 0)
        tar = size(1);
    if (exc)
    {
        drl::matrix temp(size(1) + 1, size(2));
        for (int i = 0; i < size(1) + 1; i++)
        {
            if (i == tar)
                temp.line_begin()[i] = sor;
            else if (i < tar)
                temp.line_begin()[i] = line_begin()[i];
            else
                temp.line_begin()[i] = line_begin()[i - 1];
        }
        *this = temp;
        return temp;
    }
    else
    {
        drl::matrix temp(size(1) + 1, size(2));
        for (int i = 0; i < size(1) + 1; i++)
        {
            if (i == tar)
                temp.line_begin()[i] = sor;
            else if (i < tar)
                temp.line_begin()[i] = line_begin()[i];
            else
                temp.line_begin()[i] = line_begin()[i - 1];
        }
        return temp;
    }
}

const drl::matrix drl::matrix::rins(const raw_reference &sor, int tar, bool exc)
{
    if (tar < 0)
        tar = size(2);
    if (exc)
    {
        drl::matrix temp(size(1), size(2) + 1);
        for (int i = 0; i < size(2) + 1; i++)
        {
            if (i == tar)
                temp.raw_begin()[i] = sor;
            else if (i < tar)
                temp.raw_begin()[i] = raw_begin()[i];
            else
                temp.raw_begin()[i] = raw_begin()[i - 1];
        }
        *this = temp;
        return temp;
    }
    else
    {
        drl::matrix temp(size(1), size(2) + 1);
        for (int i = 0; i < size(2) + 1; i++)
        {
            if (i == tar)
                temp.raw_begin()[i] = sor;
            else if (i < tar)
                temp.raw_begin()[i] = raw_begin()[i];
            else
                temp.raw_begin()[i] = raw_begin()[i - 1];
        }
        return temp;
    }
}
// C = A|B
const drl::matrix drl::matrix::operator|(drl::matrix const &sor) const
{
    drl::matrix temp(size(1), size(2) + sor.size(2));
    for (int i = 0; i < temp.size(1); i++)
        for (int j = 0; j < temp.size(2); j++)
            if (j >= size(2))
                temp[i][j] = sor[i][j - size(2)];
            else
                temp[i][j] = (*this)[i][j];
    return temp;
}

const drl::matrix drl::matrix::lsolve(mat const &sor) const
{
    return (((*this) ^ _TM) / ((sor ^ _TM))) ^ _TM;
}

const drl::matrix drl::matrix::rsolve(void) const
{
    matrix temp1((*this).raw_end() - 1);
    matrix temp2(*this);
    temp2.rdel(temp2.size(2) - 1);
    return temp2 / temp1;
}

const drl::matrix drl::matrix::lsolve(void) const
{
    drl::matrix temp1((*this).raw_end() - 1);
    drl::matrix temp2(*this);
    temp2.rdel(temp2.size(2) - 1);
    return temp1.lsolve(temp2);
}
std::ostream &drl::operator<<(std::ostream &out, const drl::matrix &mar)
{
    mar.print((int)(out.precision()));
    return out;
}

const drl::matrix drl::matrix::operator||(mat const &sor) const
{
    if (size(1) == sor.size(1) && size(2) == sor.size(2))
    {
        drl::matrix temp(size(1), size(2));
        auto a = begin();
        auto b = sor.begin();
        for (int i = 0; i < size(0); i++)
            if (fabs(*(a + i)) > matr_error || fabs(*(b + i)) > sor.matr_error)
                *(temp.begin() + i) = 1;
            else
                *(temp.begin() + i) = 0;
        return temp;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator&&(mat const &sor) const
{
    if (size(1) == sor.size(1) && size(2) == sor.size(2))
    {
        drl::matrix temp(size(1), size(2));
        auto a = begin();
        auto b = sor.begin();
        for (int i = 0; i < size(0); i++)
            if (fabs(*(a + i)) > matr_error && fabs(*(b + i)) > sor.matr_error)
                *(temp.begin() + i) = 1;
            else
                *(temp.begin() + i) = 0;
        return temp;
    }
    else
        return matr::Err;
}
const drl::matrix drl::matrix::operator!() const
{
    auto a = begin();
    drl::matrix temp(size(1), size(2));
    for (int i = 0; i < size(0); i++)
        if (fabs(*(a + i)) < matr_error)
            *(temp.begin() + i) = 1;
        else
            *(temp.begin() + i) = 0;
    return temp;
}

const drl::matrix::line_reference &
drl::matrix::line_reference::operator=(const raw_reference &raw_ref)
{
    int min;
    min = size() < raw_ref.size() ? size() : raw_ref.size();
    for (int i = 0; i < min; i++)
        pmar.mar->operator[](x)[i] = raw_ref.mar->operator[](i)[raw_ref.x];
    return *this;
}

const drl::matrix::raw_reference &
drl::matrix::raw_reference::operator=(const line_reference &line_ref)
{
    int min;
    min = size() < line_ref.size() ? size() : line_ref.size();
    for (int i = 0; i < min; i++)
        mar->operator[](i)[x] = line_ref.pmar.mar->operator[](line_ref.x)[i];
    return *this;
}

bool drl::matrix::printcsv(const std::string &path, int x)
{
    std::ofstream fout;
    fout.open(path, std::fstream::out | std::fstream::app);
    if (fout.good())
    {
        if (x < 0)
            x = exacted;
        fout.precision(x);
        fout.setf(std::ios_base::fixed, std::ios_base::floatfield);
        for (int i = 1; i <= size(0); i++)
        {
            fout << mar.pos[(i - 1) / mar.count_r][(i - 1) % mar.count_r];
            if (i % mar.count_r == 0)
                fout << '\n';
            else
                fout << ',';
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool drl::matrix::readcsv(const std::string &path, int x)
{
    std::ifstream fin;
    fin.open(path, std::ifstream::in);
    if (fin.good())
    {
        std::string l;
        int k = 0;
        getline(fin, l);
        for (int i = 0; i < l.size(); i++)
            if (l[i] == ',')
                k++;
        matrix re(1, k + 1);
        std::istringstream sin(l);
        std::string temp;
        for (int j = 0; j <= k; j++)
        {
            getline(sin, temp, ',');
            re[0][j] = std::stod(temp);
        }
        for (int i = 1; getline(fin, l); i++)
        {
            re.lins();
            std::istringstream sin(l);
            std::string temp;
            for (int j = 0; j <= k; j++)
            {
                getline(sin, temp, ',');
                re[i][j] = std::stod(temp);
            }
        }
        (*this) = re;
        return true;
    }
    else
        return false;
}
drl::matrix::matrix(std::initializer_list<double> list, int c_line, int c_raw,
                    int cont_init)
{
    if (c_line < 0)
        c_line = 1;
    if (c_raw < 0)
        c_raw = list.size();
    if (cont_init < 0)
        cont_init = (int)::fmin(list.size(), c_line * c_raw);
    ::matr_init(&mar, c_line, c_raw, NULL, 0);
    auto iter = list.begin();
    for (int i = 0; i < c_line * c_raw; i++, iter++)
        if (i < cont_init)
            mar.pos[i / c_raw][i % c_raw] = *iter;
        else
            mar.pos[i / c_raw][i % c_raw] = 0;
    inited = true;
}
drl::matrix::matrix(std::initializer_list<std::initializer_list<double>> list,
                    int c_line, int c_raw)
{
    if (c_line < 0)
        c_line = list.size();
    int max_ = list.begin()->size();
    auto list_ls = list.begin();
    list_ls++;
    for (int i = 1; i < list.size(); i++, list_ls++)
        if (max_ < list_ls->size())
            max_ = list_ls->size();
    if (c_raw < 0)
        c_raw = max_;
    ::matr_init(&mar, c_line, c_raw, NULL, 0);
    auto iterl = list.begin();
    for (int i = 0; i < c_line; i++, iterl++)
    {
        auto iterr = (*iterl).begin();
        for (int j = 0; j < c_raw; j++, iterr++)
            if (i < list.size())
                if (j < iterl->size())
                    mar.pos[i][j] = *iterr;
                else
                    mar.pos[i][j] = 0;
            else
                mar.pos[i][j] = 0;
    }
    inited = true;
}