#include <iostream>
template <int pp>
class A
{
 public:
    static int p;
    A() {}
};
class B : public A<1>
{
 public:
    int k;
};
class C : public A<2>
{
 public:
    int k;
};
template <int pp>
int A<pp>::p = pp;
int main(void)
{
    C l;
    B k;
    k.p = 16;
    std::cout << l.p << std::endl;
    return 0;
}