#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

int main(void)
{
    using namespace std;
    double color[4], pos[3], cpt, t1 = 0, r, pi = 3.1415926;
    string path;
    int num;

    cout << "putin color of particle R G B A" << endl;
    for (auto &i : color)
        cin >> i;

    cout << "putin pos of particle R G B A" << endl;
    for (auto &i : pos)
        cin >> i;
    cin.ignore(1);

    cout << "putin path of file" << endl;
    getline(cin, path);

    cout << "set the density of particle" << endl;
    cin >> num;

    cout << "putin r" << endl;
    cin >> r;

    cpt = 2 * pi / num;
    ofstream fout(path, std::ios::out);
    for (int i = 0; i < num; i++, t1 += cpt)
        fout << "particle minecraft:dust " << color[0] << ' ' << color[1] << ' ' << color[2] << ' ' << color[3] << ' '
             << pos[0] + r * sin(t1) << ' ' << pos[1] << ' ' << pos[2] + r * cos(t1) << ' '
             << "0 0 0 0 1 force" << endl;
    return 0;
}