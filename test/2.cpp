#include <iostream>
using namespace std;
int main(void)
{
#ifdef LOCAL
    freopen("./source/stdin.txt", "r", stdin);
    freopen("./source/stdout1.txt", "w+", stdout);
#endif
    return 0;
}