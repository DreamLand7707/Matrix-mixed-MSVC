#include "basic_matr_tag.h"
int main(void)
{
    using namespace std;
    fstream fout("./source/in.txt", std::ios::out | std::ios::trunc);
    default_random_engine engine;
    uniform_int<char> unch(32, 126);
    for (int i = 0; i < 100000000; i++)
    {
        fout.put(unch(engine));
    }
    return 0;
}