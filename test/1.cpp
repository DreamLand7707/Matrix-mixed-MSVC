#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <tchar.h>

int main(void)
{
    std::cout << std::filesystem::current_path().string();
    return 0;
}