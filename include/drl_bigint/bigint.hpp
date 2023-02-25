#ifndef DRL_BIGINT
#define DRL_BIGINT 1
#include <iostream>
#include <string>
#include <vector>

namespace drl
{
    class bigint {
        std::string num;
        bool negative;

     public:
        bigint(const std::string &number, bool keep_signed = false);
        bigint(long long number = 0);
        bigint(unsigned long long number);
        bigint(const bigint &number) : num(number.num), negative(number.negative) {}
        bigint(bigint &&number) : num(number.num), negative(number.negative) {}

        // 基本运算
        bigint operator+(const bigint &number);
        bigint operator-(const bigint &number);
        bigint operator*(const bigint &number);
        bigint operator/(const bigint &number);
        bigint operator%(const bigint &number);
        bool operator>(const bigint &number);
        bool operator<(const bigint &number);
        bool operator==(const bigint &number);
        bool operator!=(const bigint &number);
        bool operator>=(const bigint &number);
        bool operator<=(const bigint &number);
        bool operator!();
        bigint operator|(const bigint &number);
        bigint operator&(const bigint &number);
        bigint operator^(const bigint &number);
        bigint operator<<(const bigint &number);
        bigint operator>>(const bigint &number);

        // 赋值
        bigint &operator=(const bigint &number);
        bigint &operator+=(const bigint &number);
        bigint &operator-=(const bigint &number);
        bigint &operator*=(const bigint &number);
        bigint &operator/=(const bigint &number);
        bigint &operator%=(const bigint &number);
        bigint &operator|=(const bigint &number);
        bigint &operator&=(const bigint &number);
        bigint &operator^=(const bigint &number);
        bigint operator<<=(const bigint &number);
        bigint operator>>=(const bigint &number);

        // 自增自减
        bigint &operator++();
        bigint &operator--();
        bigint operator++(int);
        bigint operator--(int);

        // 负数
        bigint operator-();

        // 位置
        int operator[](std::string::size_type index);

        // 类型转换
        operator bool();
        bool bitobit();
        explicit operator long long();
        long long bitoll();
        explicit operator unsigned long long();
        long long bitoull();

        // 大小和内核
        std::string::size_type size();
        const std::string &core();
        int pos(std::string::size_type);

        ~bigint();
    };
} // namespace drl

#endif