// LZW文本压缩
// 选取字典代码数为INT_MAX，字符选择为locale("C")

#include <fstream>
#include <iostream>
#include <map>
#include <string>

constexpr int code_size = 16;
constexpr int char_size = 8;
constexpr unsigned int max_count = 1 << code_size;

using tcode = int;
using tkey = int;

void compass(std::ifstream &fin, std::ofstream &fout);

int main(int argc, char *argv[]) {
    std::ifstream fin;
    std::ofstream fout;
    if (argc > 1) {
        fin.open(argv[1], std::ios::in | std::ios::binary);
        if (argc > 2)
            fout.open(argv[2], std::ios::out | std::ios::binary);
        else
            fout.open(std::string(argv[1]) + ".bin", std::ios::out | std::ios::binary);
    }
    else {
        std::cout << "Please putin the path to the text" << std::endl;
        std::string c;
        using namespace std;
        getline(cin, c);
        fin.open(c, std::ios::in | std::ios::binary);
        fout.open(c + ".bin", std::ios::out | std::ios::binary);
    }
    compass(fin, fout);
    fin.close();
    fout.close();
    return 0;
}
void output(const unsigned long &mess, std::ofstream &fout) {
    const int pite1 = 0x00ff;
    const int pite2 = 0xff00;
    fout.put((mess & pite2) >> 8);
    fout.put(mess & pite1);
}
void compass(std::ifstream &fin, std::ofstream &fout) {
    using namespace std;
    map<tkey, tcode> dict;
    for (short i = 0; i < 256; i++) {
        pair<tkey, tcode> y(i, i);
        dict.insert(y);
    } // 0-255的所有字符
    int t1 = fin.get();
    if (t1 != EOF) {
        int t2 = t1;
        int count = 256;
        map<tkey, tcode>::iterator pos;
        for (t1 = fin.get(); fin; t1 = fin.get()) {
            pos = dict.find(t2 << char_size | t1);
            if (pos == dict.end()) { // 没找到
                output(t2, fout);
                if (count < max_count) {
                    dict.insert(pair<tkey, tcode>(
                        t2 << char_size | t1,
                        count++));
                }
                t2 = t1;
            }
            else { // 找到了
                t2 = pos->second;
            }
        }
        output(t2, fout);
    }
}