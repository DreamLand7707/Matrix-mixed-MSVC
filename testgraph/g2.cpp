#include <conio.h>
#include <easyx.h>
#include <graphics.h>

int main(void)
{
    using namespace std;
    initgraph(720, 720);
    setbkcolor(WHITE);
    cleardevice();
    settextcolor(BLACK);
    settextstyle(30, 0, _T("微软雅黑"), 0, 0, 0, 0, 0, 0);
    RECT p = {100, 100, 500, 200};
    setlinecolor(BLACK);
    rectangle(p.left, p.top, p.right, p.bottom);
    setbkmode(TRANSPARENT);
    drawtext(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ12345678910"), &p, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    _getch();
}