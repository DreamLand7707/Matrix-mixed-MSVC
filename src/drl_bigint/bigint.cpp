#include "bigint.hpp"
using namespace drl;
void bigint::drl_num_make(std::string number) {
    if (number.size()) {
        if (number[0] == '-') {
            num.assign(number.rbegin(), number.rend() - 1);
            is_negative = true;
        }
        else {
            num.assign(number.rbegin(), number.rend());
            is_negative = false;
        }
    }
}
std::ostream &drl::operator<<(std::ostream &out, const bigint &num) {
    if (num.is_negative)
        out << '-';
    out << std::string(num.num.rbegin(), num.num.rend());
    return out;
}
bigint::operator bool() const {
    for (auto i : num)
        if (i - '0')
            return true;
    return false;
}

bigint bigint::operator+(const bigint &number) const {
    bool up = false, br = false, ne1 = !is_negative, ne2 = !number.is_negative;
    char re, t1, t2;
    bool same = (is_negative && number.is_negative) || (!is_negative && !number.is_negative);
    bigint res;
    // 不同符号
    if (same) {
        for (std::string::size_type i = 0; (i < num.size() || i < number.num.size()); i++) {
            t1 = t2 = '0';
            if (i < num.size())
                t1 = num[i];
            if (i < number.num.size())
                t2 = number.num[i];
            re = ((t1 - '0') + (t2 - '0')) + up;
            if (re > 9) {
                re = re % 10;
                up = true;
            }
            else {
                up = false;
            }
            res.num.push_back(char(re + '0'));
        }
        if (up)
            res.num.push_back('1');
        res.is_negative = is_negative;
    }
    else {
        for (std::string::size_type i = 0; (i < num.size() || i < number.num.size()); i++) {
            t1 = t2 = '0';
            if (i < num.size())
                t1 = num[i];
            if (i < number.num.size())
                t2 = number.num[i];
            re = (((t1 - '0') - (ne1 * up)) *
                      (ne1 ? 1 : -1) +
                  ((t2 - '0') - (ne2 * up)) *
                      (ne2 ? 1 : -1));
            if (re < 0) {
                re += 10;
                up = true;
            }
            else {
                up = false;
            }
            res.num.push_back(char(re + '0'));
        }
        if (up) {
            res.is_negative = true;
            for (std::string::size_type i = 0; i < res.size(); i++)
                if (i)
                    res.num[i] = 9 - (res.num[i] - '0') + '0';
                else
                    res.num[i] = 10 - (res.num[i] - '0') + '0';
        }
        else
            res.is_negative = false;
    }

    return res;
}