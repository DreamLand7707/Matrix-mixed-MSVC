#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <sstream>
using namespace std;
int main(void)
{
    initgraph(640, 480);
    setbkcolor(WHITE);
    cleardevice();
    BeginBatchDraw();
    ExMessage mess;
    wstringstream wsout;
    wstring wmes;
    wsout.setf(std::ios::hex, std::ios::basefield);
    RECT coord{100, 100, 500, 500};
    settextcolor(BLACK);
    settextstyle(75, 0, L"微软雅黑");
    FlushBatchDraw();
    while (1)
    {
        wsout.str(L"");
        getmessage(&mess, EX_KEY);
        if (mess.message == WM_KEYDOWN)
        {
            clearrectangle(coord.left, coord.top, coord.right, coord.bottom);
            wsout << L"HEX" << endl
                  << L"vkc: " << mess.vkcode << std::endl
                  << L"scanc: " << mess.scancode;
            drawtext(wsout.str().c_str(), &coord, DT_LEFT | DT_WORDBREAK);
            FlushBatchDraw();
        }
    }
    EndBatchDraw();
    return 0;
}