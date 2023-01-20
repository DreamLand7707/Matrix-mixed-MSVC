#include <fstream>
#include <iostream>
#include <map>

const short EXCESS = 4,
            BYTE_SIZE = 8,
            ALPHA = 256,
            MASK1 = 255,
            MASK2 = 15;
bool bitsLeftOver = false;
short leftOver;
std::ofstream fout("./source/out.txt");
std::ifstream fin("./source/in.txt");
void output(int pcode)
{
    short c, d;
    if (bitsLeftOver)
    {
        d = short(pcode & MASK1);
        c = short((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
        fout.put(c);
        fout.put(d);
        bitsLeftOver = false;
    }
    else
    {
        leftOver = pcode & MASK2;
        c = short(pcode >> EXCESS);
        fout.put(c);
        bitsLeftOver = true;
    }
}
void compress()
{
    using namespace std;
    map<int, short> h;
    for (int i = 0; i < ALPHA; i++)
    {
        h.insert(pair(i, i));
    }
    short codesUsed = ALPHA;

    short c = fin.get();
    if (c != EOF)
    {
        int pcode = c;
        while ((c = fin.get()) != EOF)
        {
            int theKey = (pcode << BYTE_SIZE) + c;
            auto thepair = h.find(theKey);
            if (thepair == h.end())
            {
                output(pcode);
                h.insert(std::pair((pcode << BYTE_SIZE) | c, codesUsed++));
                pcode = c;
            }
            else
                pcode = thepair->second;
        }
        output(pcode);
        if (bitsLeftOver)
            fout.put(leftOver << EXCESS);
    }
    fout.close();
    fin.close();
}
int main(void)
{
    compress();
}