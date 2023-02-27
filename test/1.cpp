#include "./drl_bigint/bigint.hpp"
int main(void) {
    drl::bigint a(599), b(-4584915);
    std::cout << a << " " << b << std::endl;
    std::cout << a + b << std::endl;
}