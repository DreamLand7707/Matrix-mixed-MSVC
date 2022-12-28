#include <basic_matr_class.h>
#include <clocale>
#include <cmath>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <cwchar>
#include <graphics.h>
#include <random>
#include <string>
#include <tchar.h>
#include <vector>
#include <windows.h>

using namespace std;
using namespace drl;
void putin(int &dim, int &maxi, int &level_delta, double &thgma1, double &thgma2, double &mui1, double &mui2, double &maxx, double &minx, double &maxy, double &miny, wchar_t *name)
{
    cout << "Please enter the dimension of the matrix/picture(int)" << endl;
    cin >> dim;
    cout << "Please enter the time of test(int)" << endl;
    cin >> maxi;
    cout << "Please enter the thgma1 & miu1(double/double)" << endl;
    cin >> thgma1 >> mui1;
    cout << "Please enter the thgma2 & miu2(double/double)" << endl;
    cin >> thgma2 >> mui2;
    cout << "Please enter the minimum and maximum of x and y(double/double/double/double)" << endl;
    cin >> minx >> maxx >> miny >> maxy;
    cout << "Please enter delta of level" << endl;
    cin >> level_delta;
    cout << "Please enter the name of picture" << endl;
    setlocale(LC_ALL, "");
    wscanf(L"%ls", name);
}
int main(void)
{
    int diml = 960;                                        // 1
    int maxi = 20;                                         // 1
    double thgma1 = 5, thgma2 = 5, mui1 = 5, mui2 = -5;    // 4
    double maxx = 20, minx = -20, maxy = 20, miny = -20;   // 4
    int level_delta = 50;                                  // 1
    wchar_t name[31]{};
    putin(diml, maxi, level_delta, thgma1, thgma2, mui1, mui2, maxx, minx, maxy, miny, name);
    drl::matrix temp(diml, diml, 0.0);
    default_random_engine rande((unsigned int)time(nullptr));
    normal_distribution<double> nq1(mui1, thgma1), nq2(mui2, thgma2);
    const int times_ = diml * diml * maxi;
    for (int i = 0; i < times_; i++)
    {
        int x = (int)floor((nq1(rande) - minx) / ((maxx - minx) / diml));
        int y = (int)floor((nq2(rande) - miny) / ((maxy - miny) / diml));
        if (x < 0 || x >= diml || y < 0 || y >= diml)
        {
            i--;
            continue;
        }
        temp[x][y]++;
    }
    LOGFONT text{0,
                 0,
                 0,
                 0,
                 700,
                 false,
                 false,
                 false,
                 GB2312_CHARSET,
                 OUT_DEFAULT_PRECIS,
                 CLIP_DEFAULT_PRECIS,
                 ANTIALIASED_QUALITY,
                 DEFAULT_PITCH | FF_DONTCARE,
                 _T("小考拉体")};
    {
        COLORREF level[] = {BLACK, LIGHTBLUE, LIGHTGREEN,
                            LIGHTRED, LIGHTCYAN, LIGHTMAGENTA,
                            YELLOW, CYAN, WHITE};
        IMAGE pict(diml, diml);
        int max_height = (int)temp.max_num(), min_height = (int)temp.min_num();
        SetWorkingImage(&pict);
        for (int i = 0, level_ans = 0; i < diml; i++)
        {
            for (int j = 0; j < diml; j++)
            {
                level_ans = ((int)temp[i][j] / level_delta) %
                            (sizeof(level) / sizeof(level[0]));
                putpixel(i, j, level[level_ans]);
            }
        }
        settextstyle(&text);
        settextcolor(WHITE);
        wchar_t t[200]{};
        setbkmode(TRANSPARENT);
        swprintf(t, L"μ1 = %.3f ， σ1 = %.3f \r\n μ2 = %.3f ， σ2 = %.3f", mui1,
                 thgma1, mui2, thgma2);
        outtextxy(100, 50, t);
        saveimage(name, &pict);
        cout << min_height << " ~ " << max_height << endl;
    }
    return 0;
}
