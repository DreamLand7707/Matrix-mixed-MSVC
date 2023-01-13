#include <filesystem>
#include <fstream>
#include <iostream>
#include <tchar.h>

using namespace std;
using namespace filesystem;
int main(void)
{
    ifstream fin("./source/1.txt", std::ios::in);
    string t;
    for (; fin; getline(fin, t))
    {
        std::cout << fin.tellg() << std::endl;
    }
    return 0;
}