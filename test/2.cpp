#include <iostream>
#include <string>

int main(void)
{
    using namespace std;
    string a("HELLOWORLD!");
    string b(a, a.size() - 5, std::string::npos);
    std::cout << b;
    return 0;
}