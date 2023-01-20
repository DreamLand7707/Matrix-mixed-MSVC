#include <bitset>
#include <iostream>
#include <string>

int main(void)
{
    using namespace std;
    bitset<5> e("11111");
    cout << (e << 3).to_ulong();
}