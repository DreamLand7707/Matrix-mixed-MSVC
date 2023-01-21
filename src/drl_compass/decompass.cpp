// LZW文本解压缩
// 选取字典代码数为INT_MAX，字符选择为locale("C")

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

constexpr int code_size = 16;
constexpr int char_size = 8;
constexpr unsigned int max_count = 1 << code_size;

using tcode = int;
using tkey = int;

std::vector<unsigned char> opd;

void discompass(std::ifstream &fin, std::ofstream &fout);

int main(int argc, char *argv[])
{
    using namespace std;
    ifstream fin;
    ofstream fout;
    if (argc > 1)
    {
        fin.open(argv[1], std::ios::in | std::ios::binary);
        if (argc > 2)
            fout.open(argv[2], std::ios::out | std::ios::binary);
        else
            fout.open(string(argv[1]) + ".txt", std::ios::out | std::ios::binary);
    }
    else
    {
        std::cout << "Please putin the path to the text" << std::endl;
        std::string c;
        getline(cin, c);
        fin.open(c, std::ios::in | std::ios::binary);
        fout.open(c + ".txt", std::ios::out | std::ios::binary);
    }

    discompass(fin, fout);

    fin.close();
    fout.close();
    return 0;
}
void output(long code, std::ofstream &fout, const std::map<tkey, tcode> &dict)
{
    const int pite1 = 0b111111111111111100000000;
    const int pite2 = 0b000000000000000011111111;
    opd.clear();
    while (code >= 256)
    {
        opd.push_back(dict.at(code) & pite2);
        code = (dict.at(code) & pite1) >> char_size;
    }
    opd.push_back(code & pite2);

    for (auto i = opd.rbegin(); i != opd.rend(); i++)
    {
        fout.put(*i);
    }
}
bool getcode(long &code, std::ifstream &fin)
{
    code = 0;
    int _1, _2;
    _1 = fin.get();
    _2 = fin.get();
    (code |= (int(_1) << 8)) |= _2;
    if (!fin)
        return false;
    return true;
}
void discompass(std::ifstream &fin, std::ofstream &fout)
{
    using namespace std;
    map<tkey, tcode> dict;
    for (short i = 0; i < 256; i++)
        dict[i] = i;
    long t1, t2;
    if (getcode(t1, fin))
    {
        output(t1, fout, dict);
        for (bool i = getcode(t2, fin); i; i = getcode(t2, fin))
        {
            if (dict.find(t2) == dict.end())
            { // 没找到
                if (dict.size() < max_count)
                {
                    dict.insert({dict.size(), t1 << 8 | opd.back()});
                }
                output(t2, fout, dict);
            }
            else
            { // 找到了
                output(t2, fout, dict);
                if (dict.size() < max_count)
                {
                    dict.insert({dict.size(), t1 << 8 | opd.back()});
                }
            }
            t1 = t2;
        }
    }
}