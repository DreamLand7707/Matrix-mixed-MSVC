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
    std::vector<_TSTRING> mode_mes1 = {_T("*"), _T("H_DIR"), _T("P3_DEG")};
    std::vector<_TSTRING> mode_mes2 = {_T("1.16.5"), _T("1.12.2")};
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

    input_box_module RGB1(750, 100, 1000, 175, 50, 5,
                          WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                          BLACK, BLACK, BLACK,
                          _T(" RGB1"));

    input_box_module ARG1(750, 200, 1000, 275, 50, 5,
                          WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                          BLACK, BLACK, BLACK,
                          _T(" ARG1"));
    input_box_module ARG2(750, 300, 1000, 375, 50, 5,
                          WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                          BLACK, BLACK, BLACK,
                          _T(" ARG2"));
    input_box_module NAME1(100, 400, 1000, 475, 50, 5,
                           WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                           BLACK, BLACK, BLACK,
                           _T(" NAME1"));

    button_module clear1(625, 100, 625 + 75, 175, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("POINT1"),
                         _T(" button1"));

    button_module clear2(625, 200, 625 + 75, 275, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("POINT2"),
                         _T(" button2"));

    button_module clear3(625, 300, 625 + 75, 375, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes1[0],
                         _T(" button3"));
    button_module get1(1025, 500, 1025 + 75, 575, 10, 10, 25,
                       0xddea89, BGR(0xab896d), BGR(0x0ad55d), 0x00aaaa, BGR(0xffff00), BGR(0x986422), _T("GET"),
                       _T(" button4"));
    button_module switch1(1025, 700, 1175, 775, 10, 10, 25,
                          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes[0],
                          _T(" button5"), _T("等线"));
    button_module switch2(1025, 800, 1175, 875, 10, 10, 25,
                          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes2[0],
                          _T(" button8"), _T("等线"));


    button_module clear4(1025, 100, 1025 + 75, 175, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("RGB"),
                         _T(" button6"));
    button_module clear5(1025, 200, 1025 + 75, 275, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("C_A"),
                         _T(" button7"));
    button_module clear6(1025, 300, 1025 + 75, 375, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("TSE"),
                         _T(" button8"));
    button_module clear7(1125, 500, 1125 + 75, 575, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("CLS"),
                         _T(" button9"));
    button_module clear8(1025, 400, 1025 + 75, 475, 10, 10, 25,
                         0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("NAME"),
                         _T(" button10"));


    button_module copy1(1025, 600, 1025 + 75, 675, 10, 10, 25,
                        0xddea89, BGR(0xab896d), BGR(0x0ad55d), 0x00aaaa, BGR(0xffff00), BGR(0x986422), _T("COPY"),
                        _T(" button6"));


    output_box_module command1(100, 500, 1000, 900, 40, 5,
                               0xdddddd, 0xdddddd, 0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), BGR(0x56adcf),
                               BLACK, BLACK, BLACK,
                               _T(" command1"));
    int mode_swit = 0;
    int game_mode = 0;

    point1.inited();
    point2.inited();
    point3.inited();
    ARG1.inited();
    ARG2.inited();
    RGB1.inited();
    NAME1.inited();
    clear1.inited();
    clear2.inited();
    clear3.inited();
    clear4.inited();
    clear5.inited();
    clear6.inited();
    clear7.inited();
    clear8.inited();
    get1.inited();
    switch1.inited();
    switch2.inited();
    command1.inited();
    copy1.inited();

    clear1.change_target(point1.id);
    clear2.change_target(point2.id);
    clear3.change_target(point3.id);
    clear4.change_target(RGB1.id);
    clear5.change_target(ARG1.id);
    clear6.change_target(ARG2.id);
    clear7.change_target(command1.id);
    clear8.change_target(NAME1.id);
    get1.change_target(command1.id);
    copy1.change_target(_T(" copy_mode"));
    switch1.change_target(_T(" switch1_mode"));
    switch2.change_target(_T(" switch2_mode"));
    system_fun_reg<input_box_module>(&point1, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&point2, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&point3, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&RGB1, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&ARG1, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&ARG2, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<input_box_module>(&NAME1, &input_box_module::condition, &input_box_module::effect);
    system_fun_reg<button_module>(&clear1, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear2, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear3, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear4, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear5, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear6, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear7, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&clear8, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&get1, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&switch1, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&switch2, &button_module::condition, &button_module::effect);
    system_fun_reg<button_module>(&copy1, &button_module::condition, &button_module::effect);
    system_fun_reg<output_box_module>(&command1, &output_box_module::condition, &output_box_module::effect);

    matrix point_and_h(3, matr_tag::SP);
    matr::paramatr args(matr::empty_paramatr_1165);
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
    auto clear1_fun_4 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear4.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
        }
        return gui_signal();
    };
    auto clear1_fun_5 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear5.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
        }
        return gui_signal();
    };
    auto clear1_fun_6 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear6.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
        }
        return gui_signal();
    };
    auto clear1_fun_7 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear7.send_message_context_down.sign.source)
        {
            output_box_module *pointer = dynamic_cast<output_box_module *>(lhs);
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
        TCHAR mode;
        double temp2 = 0;
        args.parname(NAME1.input_string.c_str());
        sin.clear();
        temp_str = RGB1.input_string;
        for (auto &i : temp_str)
        {
            if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                  i == L'x' || i == L'X' ||
                  i == L'y' || i == L'Y' ||
                  i == L'z' || i == L'Z'))
                i = L' ';
        }
        sin.str(temp_str);
        sin >> args[2][1] >> args[2][2] >> args[2][3];
        sin.clear();
        temp_str = ARG1.input_string;
        for (auto &i : temp_str)
        {
            if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                  i == L'x' || i == L'X' ||
                  i == L'y' || i == L'Y' ||
                  i == L'z' || i == L'Z'))
                i = L' ';
        }
        sin.str(temp_str);
        sin >> args[0][3] >> args[0][2] >> args[3][0];
        sin.clear();
        temp_str = ARG2.input_string;
        for (auto &i : temp_str)
        {
            if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                  i == L'x' || i == L'X' ||
                  i == L'y' || i == L'Y' ||
                  i == L'z' || i == L'Z'))
                i = L' ';
        }
        sin.str(temp_str);
        sin >> args[0][0] >> args[0][1];
        out_matr.assign_para(args);
        sin.clear();
        if (mode_swit == 0)
        {
            temp_str = point1.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
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
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            sin.clear();
            temp_str = point3.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[2][0] >> mode;
            out_matr.assign_point(point_and_h);
            if (mode == 'X' || mode == 'x')
                mode = 0;
            if (mode == 'Y' || mode == 'y')
                mode = 1;
            if (mode == 'Z' || mode == 'z')
                mode = 2;
            A = out_matr.quadhet(point_and_h[2][0], mode);
            pointer->change_text(dynamic_cast<_TSTRING &>(A));
        }
        if (mode_swit == 2)
        {
            temp_str = point1.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            sin.clear();
            temp_str = point3.input_string;
            for (auto &i : temp_str)
            {
                if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' ||
                      i == L'x' || i == L'X' ||
                      i == L'y' || i == L'Y' ||
                      i == L'z' || i == L'Z'))
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
    auto clear1_fun_8 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clear8.send_message_context_down.sign.source)
        {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
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
        make_pair(clear4.send_message_type, clear4.send_message_context_down.sign.source),
        clear1_fun_4));
    user_fun_reg().insert(make_pair(
        make_pair(clear5.send_message_type, clear5.send_message_context_down.sign.source),
        clear1_fun_5));
    user_fun_reg().insert(make_pair(
        make_pair(clear6.send_message_type, clear6.send_message_context_down.sign.source),
        clear1_fun_6));
    user_fun_reg().insert(make_pair(
        make_pair(get1.send_message_type, get1.send_message_context_down.sign.source),
        get1_fun_1));
    user_fun_reg().insert(make_pair(
        make_pair(clear7.send_message_type, clear7.send_message_context_down.sign.source),
        clear1_fun_7));
    user_fun_reg().insert(make_pair(
        make_pair(clear8.send_message_type, clear8.send_message_context_down.sign.source),
        clear1_fun_8));

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
            if (cur_mes.sign.source == switch1.send_message_context_down.sign.source)
            {
                mode_swit++;
                if (mode_swit > 2)
                    mode_swit = 0;
                switch1.change_text(mode_mes[mode_swit]);
                clear3.change_text(mode_mes1[mode_swit]);
            }
            if (cur_mes.sign.source == switch2.send_message_context_down.sign.source)
            {
                game_mode = !game_mode;
                switch2.change_text(mode_mes2[game_mode]);
                if (game_mode)
                    args[2][0] = 1122.0;
                else
                    args[2][0] = 1165.0;
            }
            if (cur_mes.sign.source == copy1.send_message_context_down.sign.source)
            {
                static int timess = 0;
                HWND hwnd = NULL;
                int i = 0;
                HGLOBAL hG = GlobalAlloc(GHND, 4096);
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
                if (timess)
                {
                    HWND hwnd = NULL;
                    int i = 0;
                    HGLOBAL hG = GlobalAlloc(GHND, 4096);
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
                if (timess == 0)
                    timess = 1;
            }
        }
        /*additional 3*/
        FlushBatchDraw();
    }
}