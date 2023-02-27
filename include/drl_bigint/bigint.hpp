#ifndef DRL_BIGINT
#define DRL_BIGINT 1
#include <bitset>
#include <iostream>
#include <string>
#include <vector>


namespace drl
{
    class bigint {
        std::string num;
        bool is_negative;
        void drl_num_make(std::string);

     public:
        bigint() : num(), is_negative() {}
        bigint(const std::string &number) { drl_num_make(number); }
        bigint(long long number) { drl_num_make(std::to_string(number)); }
        bigint(long number) { drl_num_make(std::to_string(number)); }
        bigint(int number) { drl_num_make(std::to_string(number)); }
        bigint(short number) { drl_num_make(std::to_string(number)); }
        bigint(char number) { drl_num_make(std::to_string(number)); }

        bigint(unsigned int number, bool negative = false)
            : num(std::to_string(number)), is_negative(negative) {}
        bigint(unsigned long number, bool negative = false)
            : num(std::to_string(number)), is_negative(negative) {}
        bigint(unsigned short number, bool negative = false)
            : num(std::to_string(number)), is_negative(negative) {}
        bigint(unsigned char number, bool negative = false)
            : num(std::to_string(number)), is_negative(negative) {}
        bigint(unsigned long long number, bool negative = false)
            : num(std::to_string(number)), is_negative(negative) {}

        bigint(const bigint &number) : num(number.num), is_negative(number.is_negative) {}
        bigint(bigint &&number) : num(number.num), is_negative(number.is_negative) {}

        // 基本运算
        bigint operator+(const bigint &number) const;
        bigint operator-(const bigint &number) const;
        bigint operator*(const bigint &number) const;
        bigint operator/(const bigint &number) const;
        bigint operator%(const bigint &number) const;
        bool operator>(const bigint &number) const;
        bool operator<(const bigint &number) const;
        bool operator==(const bigint &number) const;
        bool operator!=(const bigint &number) const;
        bool operator>=(const bigint &number) const;
        bool operator<=(const bigint &number) const;
        bool operator!() const;
        bigint operator|(const bigint &number) const;
        bigint operator&(const bigint &number) const;
        bigint operator^(const bigint &number) const;
        bigint operator~();
        bigint operator<<(const bigint &number) const;
        bigint operator>>(const bigint &number) const;

        // 赋值
        bigint &operator=(const bigint &number) {
            num = number.num;
            is_negative = number.is_negative;
            return *this;
        }
        bigint &operator=(bigint &&number) {
            num = number.num;
            is_negative = number.is_negative;
            return *this;
        }
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
        bigint operator-() const {
            bigint result(*this);
            result.is_negative = !is_negative;
            return result;
        }

        // 位置
        char operator[](std::string::size_type index) const { return num[index]; }
        char &operator[](std::string::size_type index) { return num[index]; };

        // 类型转换
        operator bool() const;
        bool bitobit() const { return *this; }
        explicit operator long long() const { return std::stoll(num) * (is_negative ? -1 : 1); }
        long long bitoll() const { return (long long)*this; }
        explicit operator unsigned long long() const { return std::stoull(num); }
        long long bitoull() const { return (unsigned long long)*this; }

        // 大小和内核
        std::string::size_type size() const { return num.size(); }
        const std::string &core() const { return num; }
        int pos(std::string::size_type) const { return 0; }

        bool negative() const { return is_negative; }
        friend std::ostream &operator<<(std::ostream &out, const bigint &num);

        ~bigint() {}
    };
    std::ostream &operator<<(std::ostream &out, const bigint &num);
} // namespace drl

#endif