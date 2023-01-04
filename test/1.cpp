#include <clocale>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

int main(void)
{
    using namespace std;
    try
    {
        std::wcout.imbue(std::locale(std::setlocale(LC_ALL, "")));
    }
    catch (...)
    {
        std::cout << "H";
    }
    std::wcout << L"中文文字";
    return 0;
}