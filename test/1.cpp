#include "basic_par.h"

using namespace std;
using namespace filesystem;
int main(void)
{
    std::wcout.imbue(locale(""));
    _TSTRING str(_T("12 23 45 56 67 78 DC:[0.1 10] TSE:[0.1 10]")), str1;
    _TREGEX divide1(_T(R"(^([\d.]+\s*?\b){6}\s+([^\d.]+:.+|$))"));
    _TSMATCH match;
    if (regex_search(str, match, divide1))
    {
        for (auto i : match)
        {
            wcout << '[' << i << ']' << endl;
        }
    }
    else
        wcout << "None";
}