#include <filesystem>
#include <fstream>
#include <iostream>
#include <tchar.h>

using namespace std;
using namespace filesystem;
int main(void)
{
    path source(_T("./source/1/2/3/4/5/6/7/8/9"));
    for (auto i : source)
    {
        static decltype(i) o(_T(""));
        o /= i;
        create_directory((o));
    }
    return 0;
}