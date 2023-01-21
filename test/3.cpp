#include "basic_matr_tag.h"
int main(void)
{
    using namespace std;
    default_random_engine eng;
    uniform_int<int> unint(32, 126);
    fstream fout("./source/test.txt", std::ios::out);
    for (int i = 0; i < 10000; i++)
    {
        fout.put(static_cast<char>(unint(eng)));
    }
    return 0;
}