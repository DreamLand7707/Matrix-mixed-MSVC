// 库文件baisc_matr.cpp对应的类定义头文件
#ifndef basic_matr_class
#define basic_matr_class 1
namespace drl
{
    class matrix;
}

namespace matr
{
    extern drl::matrix I;
    extern drl::matrix II;
    extern drl::matrix Err;
    extern drl::matrix Empty;
} // namespace matr

enum class matr_tag {
    T,    //? 转置
    P,    //? 逆矩阵
    I,    //? 单位矩阵
    II,   //? 单位负矩阵
    Err,  //? 错误矩阵
    SP,   //? 三维点矩阵
    PP,   //? 二维点矩阵
    RAN,  //? 随机矩阵
    IRAN, //?整形随机矩阵
    LIN,  //? 行反转矩阵
    RAW   //? 列反转矩阵
};

#include "basic_ma1.h"
#include "basic_matr_tag.h"
namespace drl
{
    class matrix {
     private:
        typedef drl::matrix mat;

     private:
        ::Mat mar;
        bool inited;
        bool free(void) //?释放矩阵内存
        {
            if (inited == true) {
                ::matr_free(&mar);
                inited = false;
                return true;
            }
            else {
                return false;
            }
        }
        bool nand = false;

     public:
        class unit_iterator : public std::iterator<std::random_access_iterator_tag, double,
                                                   size_t, double *, double &>
#pragma region
        {
         private:
            const matrix *mar;
            mutable int pos = 0;
            static double error_nan;

         public:
            unit_iterator()
                : mar(const_cast<const drl::matrix *>(&matr::I)){};
            explicit unit_iterator(const drl::matrix &mat)
                : mar(&mat){};
            explicit unit_iterator(const drl::matrix *pmat)
                : mar(pmat){};
            unit_iterator(const unit_iterator &iterator)
                : mar(iterator.mar), pos(iterator.pos){};
            double &operator[](int x) const;
            double &operator*() const;
            ~unit_iterator() {}
            unit_iterator &operator=(const unit_iterator &iterator) {
                mar = iterator.mar;
                pos = iterator.pos;
                return (*this);
            }
            const unit_iterator operator++() {
                pos++;
                return (*this);
            }
            const unit_iterator operator++(int x) {
                unit_iterator A(*this);
                pos++;
                return A;
            }
            const unit_iterator operator--() {
                pos--;
                return (*this);
            }
            const unit_iterator operator--(int x) {
                unit_iterator A(*this);
                pos--;
                return A;
            }
            unit_iterator operator+(const int x) const {
                unit_iterator A(*this);
                A.pos = pos + x;
                return A;
            }
            unit_iterator operator-(const int x) const {
                unit_iterator A(*this);
                A.pos = pos - x;
                return A;
            }
            bool operator<(const unit_iterator &A) const {
                return pos < A.pos;
            }
            bool operator<=(const unit_iterator &A) const {
                return pos <= A.pos;
            }
            bool operator>(const unit_iterator &A) const {
                return pos > A.pos;
            }
            bool operator>=(const unit_iterator &A) const {
                return pos >= A.pos;
            }
            bool operator==(const unit_iterator &A) const {
                return pos == A.pos;
            }
            bool operator!=(const unit_iterator &A) const {
                return pos != A.pos;
            }
            int operator-(const unit_iterator &iterator) const {
                return pos - iterator.pos;
            }
            //? 交叉使用
        };
#pragma endregion
        typedef unit_iterator iterator;
        class raw_reference;
        class line_reference
#pragma region
        {
         private:
            union _pmar
            {
                drl::matrix *mar;
                const drl::matrix *cmar;
            } pmar;
            char pc;
            mutable int x = 0;

         public:
            friend class drl::matrix::raw_reference;
            line_reference();
            explicit line_reference(const drl::matrix &mat)
                : pc(1) {
                pmar.cmar = &mat;
            }
            explicit line_reference(drl::matrix &mat)
                : pc(2) {
                pmar.mar = &mat;
            }
            explicit line_reference(const drl::matrix *pmat)
                : pc(1) {
                pmar.cmar = pmat;
            }
            explicit line_reference(drl::matrix *pmat)
                : pc(2) {
                pmar.mar = pmat;
            }
            line_reference(const line_reference &line_ref)
                : pc(1), x(line_ref.x) {
                pmar.cmar = line_ref.pmar.cmar;
            }
            line_reference(line_reference &line_ref)
                : pc(2), x(line_ref.x) {
                pmar.mar = line_ref.pmar.mar;
            }
            line_reference(line_reference &&line_ref)
                : pc(2), x(line_ref.x) {
                pmar.cmar = line_ref.pmar.cmar;
            }

            const bool print(int y = -1) const {
                return pmar.mar->exra(x, 1).print(y);
            }
            const drl::matrix *const core() const {
                return pmar.cmar;
            }
            const int size() const {
                return pmar.mar->size(2);
            }
            const int pos() const {
                return x;
            }
            line_reference operator++() {
                x++;
                return *this;
            }
            const line_reference operator++() const {
                x++;
                return *this;
            }
            //******
            line_reference operator++(int x) {
                line_reference temp(*this);
                x++;
                return temp;
            }
            const line_reference operator++(int x) const {
                line_reference temp(*this);
                x++;
                return temp;
            }
            //=====================================================================================================
            line_reference operator--() {
                x--;
                return *this;
            }
            const line_reference operator--() const {
                x--;
                return *this;
            }
            //=====================================================================================================
            line_reference operator--(int x) {
                line_reference temp(*this);
                x--;
                return temp;
            }
            const line_reference operator--(int x) const {
                line_reference temp(*this);
                x--;
                return temp;
            }
            //=====
            const line_reference &operator=(const line_reference &line_ref);
            //=====
            line_reference operator[](const int x) {
                line_reference temp(*this);
                temp.x += x;
                return temp;
            }
            const line_reference operator[](const int x) const {
                const line_reference temp(*this);
                temp.x += x;
                return temp;
            }

            line_reference operator-(const int x) {
                line_reference temp(*this);
                temp.x -= x;
                return temp;
            }
            const line_reference operator-(const int x) const {
                line_reference temp(*this);
                temp.x -= x;
                return temp;
            }

            line_reference operator+(const int x) {
                line_reference temp(*this);
                temp.x += x;
                return temp;
            }
            const line_reference operator+(const int x) const {
                line_reference temp(*this);
                temp.x += x;
                return temp;
            }

            bool operator<(const line_reference &line_ref) const {
                return x < line_ref.x;
            }
            bool operator>(const line_reference &line_ref) const {
                return x > line_ref.x;
            }
            bool operator<=(const line_reference &line_ref) const {
                return x <= line_ref.x;
            }
            bool operator>=(const line_reference &line_ref) const {
                return x >= line_ref.x;
            }
            bool operator==(const line_reference &line_ref) const {
                return x == line_ref.x;
            }
            bool operator!=(const line_reference &line_ref) const {
                return x != line_ref.x;
            }
            const line_reference &operator=(const raw_reference &raw_ref);
        };
#pragma endregion
        class raw_reference
#pragma region
        {
         private:
            drl::matrix *mar;
            mutable int x = 0;

         public:
            friend class drl::matrix::line_reference;
            raw_reference();
            explicit raw_reference(const drl::matrix &mat)
                : mar(&const_cast<drl::matrix &>(mat)){};
            explicit raw_reference(const drl::matrix *pmat)
                : mar(const_cast<drl::matrix *>(pmat)){};
            raw_reference(const raw_reference &raw_ref)
                : mar(raw_ref.mar), x(raw_ref.x){};

            const bool print(int y = -1) const {
                return mar->exra(x, 2).print(y);
            }
            const drl::matrix *const core() const {
                return mar;
            }
            const int size() const {
                return mar->size(2);
            }
            const int pos() const {
                return x;
            }
            raw_reference operator++() {
                x++;
                return *this;
            }
            const raw_reference operator++() const {
                x++;
                return *this;
            }
            raw_reference operator++(int x) {
                raw_reference temp(*this);
                x++;
                return temp;
            }
            const raw_reference operator++(int x) const {
                raw_reference temp(*this);
                x++;
                return temp;
            }
            raw_reference operator--() {
                x--;
                return *this;
            }
            const raw_reference operator--() const {
                x--;
                return *this;
            }
            raw_reference operator--(int x) {
                raw_reference temp(*this);
                x--;
                return temp;
            }
            const raw_reference operator--(int x) const {
                raw_reference temp(*this);
                x--;
                return temp;
            }
            const raw_reference &operator=(const raw_reference &line_ref);
            raw_reference operator[](const int x) {
                raw_reference temp(*this);
                temp.x += x;
                return temp;
            }
            const raw_reference operator[](const int x) const {
                raw_reference temp(*this);
                temp.x += x;
                return temp;
            }
            raw_reference operator-(const int x) {
                raw_reference temp(*this);
                temp.x -= x;
                return temp;
            }
            const raw_reference operator-(const int x) const {
                raw_reference temp(*this);
                temp.x -= x;
                return temp;
            }
            raw_reference operator+(const int x) {
                raw_reference temp(*this);
                temp.x += x;
                return temp;
            }
            const raw_reference operator+(const int x) const {
                raw_reference temp(*this);
                temp.x += x;
                return temp;
            }
            bool operator<(const raw_reference &raw_ref) const {
                return x < raw_ref.x;
            }
            bool operator>(const raw_reference &raw_ref) const {
                return x > raw_ref.x;
            }
            bool operator<=(const raw_reference &raw_ref) const {
                return x <= raw_ref.x;
            }
            bool operator>=(const raw_reference &raw_ref) const {
                return x >= raw_ref.x;
            }
            bool operator==(const raw_reference &raw_ref) const {
                return x == raw_ref.x;
            }
            bool operator!=(const raw_reference &raw_ref) const {
                return x != raw_ref.x;
            }
            const drl::matrix::raw_reference &
            operator=(const drl::matrix::line_reference &raw_ref);
        };
#pragma endregion
//========end & begin
#pragma region
        unit_iterator begin() {
            return unit_iterator(this);
        }
        const unit_iterator begin() const {
            return unit_iterator(this);
        }
        unit_iterator end() {
            return ((unit_iterator(this)) + size(0));
        }
        const unit_iterator end() const {
            return ((unit_iterator(this)) + size(0));
        }
        line_reference line_begin() {
            return line_reference(this);
        }
        const line_reference line_begin() const {
            return line_reference(this);
        }
        line_reference line_end() {
            return (line_reference(this))[size(1)];
        }
        const line_reference line_end() const {
            return (line_reference(this))[size(1)];
        }

        raw_reference raw_begin() {
            return raw_reference(this);
        }
        const raw_reference raw_begin() const {
            return raw_reference(this);
        }
        raw_reference raw_end() {
            return (raw_reference(this))[size(2)];
        }
        const raw_reference raw_end() const {
            return (raw_reference(this))[size(2)];
        }
#pragma endregion
        double matr_error = 1e-6;
        int exacted = 6;
        static int matr_rand_max_intager;
        static int matr_rand_min_intager;
        static double matr_rand_max;
        static double matr_rand_min;
        using value_type = double;
        using pointer = double *;
        using reference = double &;
        using const_reference = const double &;
        using size_type = int;
        using const_pointer = const double *;
        using difference_type = ptrdiff_t;
        /// @brief 默认构造3*3全0矩阵
        matrix();
        /// @brief 从c_line*c_raw矩阵,使用cont指向的内容进行初始化
        /// @param c_line 行数
        /// @param c_raw 列数
        /// @param cont 一维数组
        /// @param cont_init 初始化的数目
        explicit matrix(int c_line, int c_raw = -1,
                        const double *cont = nullptr, int cont_init = -1);
        /// @brief c_line*c_raw的全init_num矩阵
        /// @param c_line 行数
        /// @param c_raw 列数
        /// @param init_num 初始化数字
        matrix(int c_line, int c_raw, double init_num);
        /// @brief 特殊矩阵
        /// @param c_lr 维度
        /// @param  matr_tag 矩阵的标志
        matrix(int c_lr, matr_tag);
        /// @brief 同为特殊矩阵,使用_RAN,_IRAN来定义整数随机矩阵或浮点数随机矩阵
        /// @param c_l 行数
        /// @param c_r 列数
        /// @param  matr_tag 标志
        matrix(int c_l, int c_r, matr_tag);
        matrix(matrix const &ma_sor);
        matrix(matrix const *ma_sor)
            : matrix(*ma_sor){};
        matrix(const matrix &&ma_sor);
        /// @brief 双迭代器的初始化
        /// @param lhs 左迭代器
        /// @param rhs 超尾迭代器
        /// @param c_line 行数
        /// @param c_raw 列数
        /// @param cont_init 初始化数目
        matrix(const unit_iterator &lhs, const unit_iterator &rhs,
               int c_line = 1, int c_raw = -1, int cont_init = -1);
        matrix(const line_reference &line, int c_line = 1, int c_raw = -1,
               int cont_init = -1);
        matrix(const raw_reference &line, int c_line = 1, int c_raw = -1,
               int cont_init = -1);
        //=====================================================================================================
        template <typename T> //?向量构造函数
        matrix(std::vector<T> vec, int c_line, int c_raw = -1,
               int cont_init = -1);
        //? 列表构造函数
        matrix(std::initializer_list<double> vec, int c_line = -1, int c_raw = -1,
               int cont_init = -1);
        matrix(std::initializer_list<std::initializer_list<double>> vec,
               int c_line = -1, int c_raw = -1);
        /// @brief 规定范围内的等距元素矩阵
        /// @param start 开始
        /// @param end 结束
        /// @param delta 元素公差
        /// @param line 行数
        /// @param raw 列数
        matrix(double start, double end, double delta, int line = -1,
               int raw = -1);
        /// @brief 规定范围内的行向量
        /// @param start 开始
        /// @param end 结束
        /// @param count 数目
        matrix(double start, double end, int count);
        /// @brief 规定范围内的自适应公差矩阵
        /// @param start 开始
        /// @param end 结束
        /// @param line 行数
        /// @param raw 列数
        matrix(double start, double end, int line, int raw);
        virtual ~matrix();               //?析构
        virtual bool print_(int x) const //?打印矩阵
        {
            if (inited == true) {
                if (iserr())
                    printf("\033[31m");
                ::matr_print(&mar, x, matr_error);
                if (iserr())
                    printf("\033[0m");
                return true;
            }
            else
                return false;
        }
        virtual bool print_() const //?打印矩阵
        {
            if (inited == true) {
                if (iserr())
                    printf("\033[31m");
                ::matr_print(&mar, exacted, matr_error);
                if (iserr())
                    printf("\033[0m");
                return true;
            }
            else
                return false;
        }
        virtual bool print(int x = -1) const //?整齐打印矩阵，x为小数精确度
        {
            if (inited == true) {
                if (x < 0)
                    x = exacted;
                if (iserr())
                    printf("\033[31m");
                double error = pow(10, -x);
                ::matr_print_s(&mar, x, error);
                if (iserr())
                    printf("\033[0m");
                return true;
            }
            else
                return false;
        }
        virtual bool printcsv(const std::string &, int = -1);
        virtual bool readcsv(const std::string &, int = -1);
        virtual void print_exa(int x) {
            exacted = x;
        }
        const Mat *const core_struct(void) const {
            return &(this->mar);
        }
        const double *const *const core_array(void) const {
            return this->mar.pos;
        }
        const int size(int x = 0) const //?返回矩阵的维度，0为数据的数目，1为行数，2为列数
        {
            if (inited == true)
                if (x == 0)
                    return mar.count_l * mar.count_r;
                else if (x == 1)
                    return mar.count_l;
                else if (x == 2)
                    return mar.count_r;
                else
                    return -1;
            else
                return -1;
        }
        const double max_num(void) const //?矩阵最大值
        {
            return ::matr_spr(&mar, 2, matr_error);
        }
        const double min_num(void) const //?矩阵的最小值
        {
            return ::matr_spr(&mar, 1, matr_error);
        }
        const double aver_num(void) const //?矩阵的平均值
        {
            return ::matr_spr(&mar, 3, matr_error);
        }
        const double mid_num(void) const //?矩阵的中值
        {
            return ::matr_spr(&mar, 4, matr_error);
        }
        const int allin(double low, double high) const //?全在范围
        {
            return ::matr_range(&mar, 1, low, high, matr_error);
        }
        const int allout(double low, double high) const //?全不在范围
        {
            return ::matr_range(&mar, 2, low, high, matr_error);
        }
        const int allran(double low, double high) const //?部分在范围
        {
            return ::matr_range(&mar, 3, low, high, matr_error);
        }

        const matrix exra(int tar, int dim = 1) const;
        //======================================
        const matrix lsim(int sor, int tar, double a, double b, double c,
                          bool exc = true);
        const matrix lsim(int sor, int tar, bool exc = true) {
            return lsim(sor, tar, 1, 1, 0, exc);
        }
        const matrix lsim(int sor, int tar, double a, bool exc = true) {
            return lsim(sor, tar, a, 1, 0, exc);
        }
        const matrix lsim(int sor, int tar, double a, double b, bool exc = true) {
            return lsim(sor, tar, a, b, 0, exc);
        }
        const matrix rsim(int sor, int tar, double a, double b, double c,
                          bool exc = true);
        const matrix rsim(int sor, int tar, bool exc = true) {
            return rsim(sor, tar, 1, 1, 0, exc);
        }
        const matrix rsim(int sor, int tar, double a, bool exc = true) {
            return rsim(sor, tar, a, 1, 0, exc);
        }
        const matrix rsim(int sor, int tar, double a, double b, bool exc = true) {
            return rsim(sor, tar, a, b, 0, exc);
        }
        const matrix lexc(int sor, int tar, bool exc = true);
        const matrix rexc(int sor, int tar, bool exc = true);
        const matrix ldel(int tar, bool exc = true);
        const matrix rdel(int tar, bool exc = true);
        const matrix lrev(bool exc = true); //?上下翻转
        const matrix rrev(bool exc = true); //?左右翻转
        const matrix lins(const line_reference &sor = matr::Empty.line_begin(),
                          int tar = -1, bool exc = true);
        const matrix lins(int tar, bool exc = true) {
            return lins(matr::Empty.line_begin(), tar, exc);
        }
        const matrix rins(const raw_reference &sor = matr::Empty.raw_begin(),
                          int tar = -1, bool exc = true);
        const matrix rins(int tar, bool exc = true) {
            return rins(matr::Empty.raw_begin(), tar, exc);
        }
        //====================================
        const matrix lsim(int sor, int tar, double a, double b, double c) const {
            return (const_cast<matrix &>(*this)).lsim(sor, tar, a, b, c, false);
        }
        const matrix lsim(int sor, int tar) const {
            return lsim(sor, tar, 1, 1, 0);
        }
        const matrix lsim(int sor, int tar, double a) const {
            return lsim(sor, tar, a, 1, 0);
        }
        const matrix lsim(int sor, int tar, double a, double b) const {
            return lsim(sor, tar, a, b, 0);
        }
        const matrix rsim(int sor, int tar, double a, double b, double c) const {
            return (const_cast<matrix &>(*this)).rsim(sor, tar, a, b, c, false);
        }
        const matrix rsim(int sor, int tar) const {
            return rsim(sor, tar, 1, 1, 0);
        }
        const matrix rsim(int sor, int tar, double a) const {
            return rsim(sor, tar, a, 1, 0);
        }
        const matrix rsim(int sor, int tar, double a, double b) const {
            return rsim(sor, tar, a, b, 0);
        }
        const matrix lexc(int sor, int tar) const {
            return (const_cast<matrix &>(*this)).lexc(sor, tar, false);
        }
        const matrix rexc(int sor, int tar) const {
            return (const_cast<matrix &>(*this)).rexc(sor, tar, false);
        }
        const matrix ldel(int tar) const {
            return (const_cast<matrix &>(*this)).ldel(tar, false);
        }
        const matrix rdel(int tar) const {
            return (const_cast<matrix &>(*this)).rdel(tar, false);
        }
        const matrix lrev(void) const {
            return (const_cast<matrix &>(*this)).lrev(false);
        } //?上下翻转
        const matrix rrev(void) const {
            return (const_cast<matrix &>(*this)).rrev(false);
        } //?左右翻转

        const matrix lins(const line_reference &sor = matr::Empty.line_begin(),
                          int tar = -1) const {
            return const_cast<matrix &>(*this).lins(sor, tar, false);
        }
        const matrix lins(int tar) const {
            return const_cast<matrix &>(*this).lins(matr::Empty.line_begin(),
                                                    tar, false);
        }
        const matrix rins(const raw_reference &sor = matr::Empty.raw_begin(),
                          int tar = -1) const {
            return const_cast<matrix &>(*this).rins(sor, tar, false);
        }
        const matrix rins(int tar) const {
            return const_cast<matrix &>(*this).rins(matr::Empty.raw_begin(),
                                                    tar, false);
        }
        //======================================
        matrix &operator=(matrix const &);            //?矩阵赋值
        matrix &operator=(const matrix &&);           //?矩阵移动赋值
        const matrix operator+(matrix const &) const; //?矩阵相加
        const matrix operator-(matrix const &) const; //?矩阵相减
        const matrix operator*(matrix const &) const; //?矩阵相乘
        const matrix operator*(double) const;         //?矩阵数乘
        const matrix operator&(matrix const &) const; //?矩阵笛卡尔乘
        const matrix operator/(matrix const &) const; //?矩阵求解 Ax=B求解
        const matrix operator^(int) const;            //?矩阵乘方
        const matrix operator^(matr_tag) const;       //?矩阵特殊处理
        const matrix operator||(matrix const &) const;
        const matrix operator&&(matrix const &) const;
        const matrix operator!() const;
        const double det() const;          //?矩阵行列式值
        const matrix Rdet(int, int) const; //?矩阵的余子式
        friend const matrix operator*(double,
                                      const drl::matrix &); //?矩阵数乘-友元
        friend const matrix operator-(const drl::matrix &); //?负矩阵
        friend std::ostream &operator<<(std::ostream &out, const matrix &mar);
        const bool operator==(matrix const &) const; //?矩阵相等
        const double *const operator[](int) const;   //?矩阵的数
        double *const operator[](int);               //?矩阵的数

        const matrix operator|(matrix const &sor) const; // 增广
        const matrix operator|=(matrix const &sor) {
            (*this) = (*this) | sor;
            return *this;
        }
        const matrix rsolve(matrix const &sor) const {
            return (*this) / sor;
        }                                          // 右解
        const matrix lsolve(matrix const &) const; // 左解 xA=b
        const matrix rsolve(void) const;           // 右解
        const matrix lsolve(void) const;           // 左解
        const matrix operator%(matrix const &sor) const {
            return lsolve(sor);
        } // 左解一矩阵
        const matrix operator%=(matrix const &sor) {
            *this = lsolve(sor);
            return *this;
        } // 左解

        // TODO:解卷/卷积操作
        /*
      @ const mat convolute(mat const &, double edge = 0.0) const;
      @ const mat disconvolute(mat const &, double edge = 0.0) const;
      */

        const matrix operator+(const double) const;
        const matrix operator-(const double) const;
        const matrix operator/(const double) const;
        const matrix operator%(const int) const;
        const matrix operator^(const double) const;
#pragma region
        const matrix operator+=(matrix const &A) {
            *this = *this + A;
            return *this;
        }
        const matrix operator-=(matrix const &A) {
            *this = *this - A;
            return *this;
        }
        const mat operator*=(mat const &A) {
            *this = *this * A;
            return *this;
        }
        const mat operator*=(double A) {
            *this = *this * A;
            return *this;
        }
        const mat operator&=(mat const &A) {
            *this = *this & A;
            return *this;
        }
        const mat operator/=(mat const &A) {
            *this = *this / A;
            return *this;
        }
        const mat operator^=(int A) {
            *this = *this ^ A;
            return *this;
        }
        const mat operator^=(matr_tag A) {
            *this = *this ^ A;
            return *this;
        }
        const mat operator+=(const double A) {
            *this = *this + A;
            return *this;
        }
        const mat operator-=(const double A) {
            *this = *this - A;
            return *this;
        }
        const mat operator/=(const double A) {
            *this = *this / A;
            return *this;
        }
        const mat operator%=(const int A) {
            *this = *this % A;
            return *this;
        }
        const mat operator^=(const double A) {
            *this = *this ^ A;
            return *this;
        }
#pragma endregion

        const int rank() const //?矩阵的秩
        {
            return ::matr_rank(&mar, matr_error);
        }
        void trans(int c_line = 3, int c_raw = -2, const double *cont = nullptr,
                   int cont_init = 0) //?矩阵变维
        {
            if (cont == nullptr) {
                c_raw = size(0) / c_line + (size(0) % c_line ? 1 : 0);
                matrix A(c_line, c_raw);
                if (cont_init == 0)
                    cont_init = c_line * c_raw;
                int x = c_line * c_raw;
                x = (int)fmin(x, size(0));
                x = (int)fmin(x, cont_init);
                for (int i = 0; i < x; i++)
                    A.begin()[i] = begin()[i];
                *this = A;
            }
            else {
                matrix A(c_line, c_raw, cont, cont_init);
                *this = A;
            }
        }
        void trans(int c_line, int c_raw, double init_num) //?矩阵变维二号
        {
            matrix A(c_line, c_raw, init_num);
            *this = A;
        }
        void trans(int c_lr, matr_tag x) //?矩阵变维三号
        {
            if (x == matr_tag::I) {
                matrix A(c_lr);
                for (int i = 0; i < c_lr; i++)
                    A[i][i] = 1;
                *this = A;
            }
            else if (x == matr_tag::II) {
                matrix A(c_lr);
                for (int i = 0; i < c_lr; i++)
                    A[i][i] = -1;
                *this = A;
            }
        }
        void trans(int c_l, int c_r, matr_tag x) {
            switch (x) {
            case matr_tag::IRAN:
            case matr_tag::RAN: {
                matrix temp(c_l, c_r, x);
                *this = temp;
                break;
            }
            default: {
            }
            }
        }
        void trans(const matrix::line_reference &line, int c_line = -1,
                   int c_raw = -1, int cont_init = -1) {
            matrix A(line, c_line, c_raw, cont_init);
            *this = A;
        }
        void trans(const matrix::raw_reference &raw, int c_line = -1,
                   int c_raw = -1, int cont_init = -1) {
            matrix A(raw, c_line, c_raw, cont_init);
            *this = A;
        }
        void trans(const unit_iterator &lhs, const unit_iterator &rhs,
                   int c_line = -1, int c_raw = -1, int cont_init = -1) {
            matrix A(lhs, rhs, c_line, c_raw, cont_init);
            *this = A;
        }
        template <typename T>
        void trans(std::vector<T> vec, int c_line, int c_raw = -1,
                   int cont_init = -1) {
            matrix temp(vec, c_line, c_raw, cont_init);
            *this = temp;
        }
        template <typename T>
        void trans(std::initializer_list<T> vec, int c_line = -1,
                   int c_raw = -1, int cont_init = -1) {
            matrix temp(vec, c_line, c_raw, cont_init);
            *this = temp;
        }
        template <typename T>
        void trans(std::initializer_list<std::initializer_list<T>> vec,
                   int c_line = -1, int c_raw = -1) {
            matrix temp(vec, c_line, c_raw);
            *this = temp;
        }
        const bool iserr() const {
            if (nand)
                return true;
            else
                return false;
        }
        void cherr(bool is = false) {
            if (is)
                if (nand)
                    nand = false;
                else
                    nand = true;
            else
                nand = true;
        }
    };

    template <typename T>
    matrix::matrix(std::vector<T> vec, int c_line, int c_raw, int cont_init) {
        if (c_raw < 0)
            c_raw = vec.size() / c_line + (vec.size() % c_line ? 1 : 0);
        if (cont_init < 0)
            cont_init = (int)::fmin(vec.size(), c_line * c_raw);
        ::matr_init(&mar, c_line, c_raw, NULL, 0);
        for (int i = 0; i < c_line * c_raw; i++)
            if (i < cont_init)
                mar.pos[i / c_raw][i % c_raw] = vec[i];
            else
                mar.pos[i / c_raw][i % c_raw] = 0;
        inited = true;
    }
    const matrix operator*(double, const drl::matrix &);
    const matrix operator-(const drl::matrix &);
    std::ostream &operator<<(std::ostream &out, const matrix &mar);
} // namespace drl


// typedef drl::matrix mat;

#endif