#include "basic_par.h"

using namespace std;
using namespace filesystem;
int main(void)
{
    std::wcout.imbue(locale(""));
    _TSTRING str(_T("[1.2 1.3 0.6]"));
    _TREGEX divide1(_T(R"(^(\S+?):(.+))"));
    _TREGEX divide2(_T(R"(^(\S+?),(.+))"));
    _TSMATCH match;
    if (regex_match(str, match, divide1))
    {
        wcout << match.size() << endl;
        for (auto i : match)
        {
            std::wcout << i << std::endl;
        }
    }
    else
        wcout << L"None";
}