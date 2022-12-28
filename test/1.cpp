#include <functional>
class A
{

 public:
    int p;
    int print(int c)
    {
        return c + p;
    }
    int print()
    {
        return p;
    }
};
int main(void)
{
    int (A::*ol)(int) = &A::print;
    int (A::*ol1)() = &A::print;
    A m;
    std::function<int(int)> n(std::bind(ol, m, std::placeholders::_1));
}