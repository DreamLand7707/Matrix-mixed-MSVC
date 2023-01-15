#include "basic_par.h"

using namespace std;
using namespace filesystem;
int main(void)
{
    std::wcout.imbue(locale(""));
    _TSTRING str(_T("linear @162")), str1;
    _TREGEX divide1(_T(R"((?:\s*(@([0-9]*))\s+)?)") + _TSTRING(_T("(linear|tparab|dparab)")) + _T(R"((?:\s+(@([0-9]*))\s*)?)"));
    _TSMATCH match;
    regex_search(str, match, divide1);
    for (int i = 0; i < match.size(); i++)
    {
        std::wcout << i << _T(": ^") << match[i] << "$=>[size:" << match[i].str().size() << "]" << std::endl;
    }
}