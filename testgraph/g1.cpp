#include "basic_par.h"
#include "drl_graph/drl_gui_module.hpp"
#include "drl_graph/drl_gui_signal.hpp"

int main(int argc, char *argv[])
{
    using namespace drl;
    using std::make_pair;
    initgraph(1280, 960);
    BeginBatchDraw();
    setbkcolor(WHITE);
    cleardevice();
    FlushBatchDraw();
    const TCHAR *font_g = _T("微软雅黑");
    global_font(font_g);
    std::vector<_TSTRING> mode_mes = {_T("MODE : LIN"), _T("MODE : SQR1"), _T("MODE : SQR2")};
    std::vector<_TSTRING> mode_mes3 = {_T("*"), _T("HEIGHT"), _T("POINT3")};
    input_box_module point1(100, 100, 600, 175, 50, 5,
                            WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                            BLACK, BLACK, BLACK,
                            _T(" point1"));

    input_box_module point2(100, 200, 600, 275, 50, 5,
                            WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                            BLACK, BLACK, BLACK,
                            _T(" point2"));

    input_box_module point3(100, 300, 600, 375, 50, 5,
                            WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                            BLACK, BLACK, BLACK,
                            _T(" point3"));

    button_module clear1(650, 100, 650 + 75, 175, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("POINT1"),
                         _T(" button1"));

    button_module clear2(650, 200, 650 + 75, 275, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("POINT2"),
                         _T(" button2"));

    button_module clear3(650, 300, 650 + 75, 375, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes3[0],
                         _T(" button3"));
    button_module get1(750, 300, 750 + 75, 375, 10, 10, 25,
                       0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("GET"),
                       _T(" button4"));
    button_module switch1(850, 300, 1000, 375, 10, 10, 25,
                          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes[0],
                          _T(" button5"), _T("等线"));

    button_module copy1(1050, 400, 1050 + 75, 475, 10, 10, 25,
                        0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("COPY"),
                        _T(" button6"));


    output_box_module command1(100, 400, 1000, 900, 40, 5,
                               0xdddddd, 0xdddddd, 0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), BGR(0x56adcf),
                               BLACK, BLACK, BLACK,
                               _T(" command1"));
    int mode_swit = 0;

    point1.inited();
    point2.inited();
    point3.inited();
    clear1.inited();
    clear2.inited();
    clear3.inited();
    get1.inited();
    switch1.inited();
    command1.inited();
    copy1.inited();
    clear1.change_target(point1.id);
    clear2.change_target(point2.id);
    clear3.change_target(point3.id);
    get1.change_target(command1.id);
    copy1.change_target(_T(" copy_mode"));
    switch1.change_target(_T(" switch_mode"));
    system_fun_reg<input_box_module>(&point1, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&point2, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&point3, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<button_module>(&clear1, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear2, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear3, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&get1, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&switch1, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&copy1, &button_module::condition, &button_module::effect);
    system_fun_reg<output_box_module>(&command1, &output_box_module::condition, &output_box_module::effect);

    matrix point_and_h(3, matr_tag::SP);
    O_partmatr out_matr(point_and_h, matr::empty_paramatr_1165);

    auto clear1_fun_1 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear1.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
        }
        return gui_signal();
    };
    auto clear1_fun_2 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear2.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
        }
        return gui_signal();
    };
    auto clear1_fun_3 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear3.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
        }
        return gui_signal();
    };
    auto get1_fun_1 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        static strmatr A;
        static _TSTRINGSTREAM sin;
        static _TSTRING temp_str;
        drl::output_box_module *pointer = dynamic_cast<output_box_module *>(lhs);
        double t1, t2, t3;
        double temp2 = 0;
        sin.clear();
        if (mode_swit == 0)
        {
            temp_str = point1.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            out_matr.assign_point(point_and_h);
            A = out_matr.linear();
            pointer->change_text(dynamic_cast<_TSTRING &>(A));
        }
        if (mode_swit == 1)
        {
            temp_str = point1.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            sin.clear();
            temp_str = point3.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[2][0] >> point_and_h[2][1];
            out_matr.assign_point(point_and_h);
            A = out_matr.quadhet(point_and_h[2][0], point_and_h[2][1]);
            pointer->change_text(dynamic_cast<_TSTRING &>(A));
        }
        if (mode_swit == 2)
        {
            temp_str = point1.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            sin.clear();
            temp_str = point3.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[2][0] >> point_and_h[2][1] >> point_and_h[2][2] >> temp2;
            out_matr.assign_point(point_and_h);
            A = out_matr.quadthr(temp2);
            pointer->change_text(dynamic_cast<_TSTRING &>(A));
        }
        return gui_signal();
    };

    user_fun_reg().insert(make_pair(
        make_pair(clear1.send_message_type, clear1.send_message_context_down.sign.source),
        clear1_fun_1));
    user_fun_reg().insert(make_pair(
        make_pair(clear2.send_message_type, clear2.send_message_context_down.sign.source),
        clear1_fun_2));
    user_fun_reg().insert(make_pair(
        make_pair(clear3.send_message_type, clear3.send_message_context_down.sign.source),
        clear1_fun_3));
    user_fun_reg().insert(make_pair(
        make_pair(get1.send_message_type, get1.send_message_context_down.sign.source),
        get1_fun_1));

    ExMessage sys_mes;
    gui_signal cur_mes, last_mes, res_mes;
    for (;;)
    {
        getmessage(&sys_mes, EX_MOUSE | EX_KEY);
        message_push_back(sys_mes);
        for (; !message_deque().empty(); last_mes = message_pop_front())
        {
            cur_mes = message_pop_front(true);
            if (cur_mes.make_sence)
            {
                for (auto cur_sys_fun : system_fun_reg())
                {
                    res_mes = cur_sys_fun(cur_mes);
                    if (res_mes.make_sence)
                        message_push_back(res_mes);
                    /*additional 1*/
                }
            }
            /*additional 2*/
            if (cur_mes.sign.target == _T(" switch_mode"))
            {
                mode_swit++;
                if (mode_swit > 2)
                    mode_swit = 0;
                switch1.change_text(mode_mes[mode_swit]);
                clear3.change_text(mode_mes3[mode_swit]);
            }
            if (cur_mes.sign.target == _T(" copy_mode"))
            {
                HWND hwnd = NULL;
                int i = 0;
                HGLOBAL hG = GlobalAlloc(GHND, 1024);
                wchar_t *p = (wchar_t *)GlobalLock(hG);
                for (i = 0; i < command1.output_string.size(); i++)
                {
                    p[i] = command1.output_string[i];
                }
                p[i] = 0;
                GlobalUnlock(hG);
                OpenClipboard(hwnd);
                EmptyClipboard();
                SetClipboardData(CF_UNICODETEXT, hG);
                CloseClipboard();
                GlobalFree(hG);
            }
        }
        /*additional 3*/
        FlushBatchDraw();
    }
}