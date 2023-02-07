#include "basic_par_algout.h"
#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"

int main(int argc, char *argv[]) {
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
                            _T("point1"));

    input_box_module point2(100, 200, 600, 275, 50, 5,
                            WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                            BLACK, BLACK, BLACK,
                            _T("point2"));

    input_box_module point3(100, 300, 600, 375, 50, 5,
                            WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                            BLACK, BLACK, BLACK,
                            _T("point3"));

    input_box_module RGB1(750, 100, 1000, 175, 50, 5,
                          WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                          BLACK, BLACK, BLACK,
                          _T("RGB1"));

    input_box_module ARG1(750, 200, 1000, 275, 50, 5,
                          WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                          BLACK, BLACK, BLACK,
                          _T("ARG1"));
    input_box_module ARG2(750, 300, 1000, 375, 50, 5,
                          WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                          BLACK, BLACK, BLACK,
                          _T("ARG2"));
    input_box_module NAME1(100, 400, 1000, 475, 50, 5,
                           WHITE, WHITE, WHITE, LIGHTRED, LIGHTBLUE, LIGHTMAGENTA,
                           BLACK, BLACK, BLACK,
                           _T("NAME1"));
    button_module clears[8] =
        {{625, 100, 625 + 75, 175, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("POINT1"),
          _T("button1")},
         {625, 200, 625 + 75, 275, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("POINT2"),
          _T("button2")},
         {625, 300, 625 + 75, 375, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes1[0],
          _T("button3")},
         {1025, 100, 1025 + 75, 175, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("RGB"),
          _T("button6")},
         {1025, 200, 1025 + 75, 275, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("C_A"),
          _T("button7")},
         {1025, 300, 1025 + 75, 375, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("TSE"),
          _T("button8")},
         {1125, 500, 1125 + 75, 575, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("CLS"),
          _T("button9")},
         {1025, 400, 1025 + 75, 475, 10, 10, 25,
          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), _T("NAME"),
          _T("button10")}};

    button_module get1(1025, 500, 1025 + 75, 575, 10, 10, 25,
                       0xddea89, BGR(0xab896d), BGR(0x0ad55d), 0x00aaaa, BGR(0xffff00), BGR(0x986422), _T("GET"),
                       _T("button4"));
    button_module switch1(1025, 700, 1175, 775, 10, 10, 25,
                          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes[0],
                          _T("button5"), _TSTRING(_T("等线")));
    button_module switch2(1025, 800, 1175, 875, 10, 10, 25,
                          0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), 0x000000, BGR(0xffff00), BGR(0xf638a3), mode_mes2[0],
                          _T("button8"), _TSTRING(_T("等线")));

    button_module copy1(1025, 600, 1025 + 75, 675, 10, 10, 25,
                        0xddea89, BGR(0xab896d), BGR(0x0ad55d), 0x00aaaa, BGR(0xffff00), BGR(0x986422), _T("COPY"),
                        _T("button6"));

    output_box_module command1(100, 500, 1000, 900, 40, 5,
                               0xdddddd, 0xdddddd, 0xdddddd, BGR(0x56adcf), BGR(0x0ad55d), BGR(0x56adcf),
                               BLACK, BLACK, BLACK,
                               _T("command1"));
    int mode_swit = 0;
    int game_mode = 0;

    clears[0].change_target(point1.id()).send_message_context_down.add_source_word(_T("0"));
    clears[1].change_target(point2.id()).send_message_context_down.add_source_word(_T("1"));
    clears[2].change_target(point3.id()).send_message_context_down.add_source_word(_T("2"));
    clears[3].change_target(RGB1.id()).send_message_context_down.add_source_word(_T("3"));
    clears[4].change_target(ARG1.id()).send_message_context_down.add_source_word(_T("4"));
    clears[5].change_target(ARG2.id()).send_message_context_down.add_source_word(_T("5"));
    clears[6].change_target(command1.id()).send_message_context_down.add_source_word(_T("6"));
    clears[7].change_target(NAME1.id()).send_message_context_down.add_source_word(_T("7"));
    get1.change_target(command1.id());

    init_group(1);

    matrix point_and_h(3, matr_tag::SP);
    matr::paramatr args(matr::empty_paramatr_1165);
    O_partmatr out_matr(point_and_h, matr::empty_paramatr_1165);

    auto suit_the_condition = [](TCHAR i) -> bool
    {
        if (!((i >= L'0' && i <= L'9') || i == L'.' || i == L'-' || (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') ||
              i == L'+' || i == L'*' || i == L'/' || i == L' ' || i == L'^' || i == L'(' || i == L')'))
            return false;
        return true;
    };

    auto clear1_fun_1 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        if (rhs->sign.source == clears[std::stoi(rhs->exac_fin_word())].send_message_context_down.sign.source) {
            input_box_module *pointer = dynamic_cast<input_box_module *>(lhs);
            output_box_module *pointer2 = dynamic_cast<output_box_module *>(lhs);
            if (pointer)
                pointer->change_text(_T(""));
            if (pointer2)
                pointer2->change_text(_T(""));
        }
        return gui_signal();
    };

    auto get1_fun_1 = [&](gui_module *lhs, const gui_signal *rhs) -> gui_signal
    {
        static strmatr A;
        _TSTRINGSTREAM &sin = drl::public_tstream();
        static _TSTRING temp_str;
        drl::output_box_module *pointer = dynamic_cast<output_box_module *>(lhs);
        TCHAR mode;
        double temp2 = 0;
        args.parname(NAME1.input_string.c_str());
        sin.clear();
        temp_str = RGB1.input_string;
        for (auto &i : temp_str) {
            if (suit_the_condition(i))
                i = L' ';
        }
        sin.str(temp_str);
        sin >> args[2][1] >> args[2][2] >> args[2][3];
        sin.clear();
        temp_str = ARG1.input_string;
        for (auto &i : temp_str) {
            if (suit_the_condition(i))
                i = L' ';
        }
        sin.str(temp_str);
        sin >> args[0][3] >> args[0][2] >> args[3][0];
        sin.clear();
        temp_str = ARG2.input_string;
        for (auto &i : temp_str) {
            if (suit_the_condition(i))
                i = L' ';
        }
        sin.str(temp_str);
        sin >> args[0][0] >> args[0][1];
        out_matr.assign_para(args);
        sin.clear();
        if (mode_swit == 0) {
            temp_str = point1.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            out_matr.assign_point(point_and_h);
            A = out_matr.linear();
            pointer->change_text(dynamic_cast<_TSTRING &>(A));
        }
        if (mode_swit == 1) {
            temp_str = point1.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            sin.clear();
            temp_str = point3.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
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
        if (mode_swit == 2) {
            temp_str = point1.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[0][0] >> point_and_h[0][1] >> point_and_h[0][2];
            sin.clear();
            temp_str = point2.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
                    i = L' ';
            }
            sin.str(temp_str);
            sin >> point_and_h[1][0] >> point_and_h[1][1] >> point_and_h[1][2];
            sin.clear();
            temp_str = point3.input_string;
            for (auto &i : temp_str) {
                if (suit_the_condition(i))
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
        make_pair(get1.send_message_type, get1.id()),
        get1_fun_1));
    for (int i = 0; i < 8; i++)
        user_fun_reg().insert(make_pair(
            make_pair(clears[i].send_message_type, clears[i].id()),
            clear1_fun_1));

    ExMessage sys_mes;
    gui_signal cur_mes, last_mes, res_mes;
    for (;;) {
        getmessage(&sys_mes, EX_MOUSE | EX_KEY);
        message_push_back(sys_mes);
        for (; !message_deque().empty(); last_mes = message_pop_front()) {
            cur_mes = message_pop_front(true);
            if (cur_mes.make_sence) {
                auto &&fun_use = system_fun_reg(1);
                for (; fun_use.first != fun_use.second; fun_use.first++) {
                    res_mes = fun_use.first->second(cur_mes);
                    if (res_mes.make_sence)
                        message_push_back(res_mes);
                    /*additional 1*/
                }
            }
            /*additional 2*/
            if (cur_mes.sign.source == switch1.send_message_context_down.sign.source) {
                mode_swit++;
                if (mode_swit > 2)
                    mode_swit = 0;
                switch1.change_text(mode_mes[mode_swit]);
                clears[2].change_text(mode_mes1[mode_swit]);
            }
            if (cur_mes.sign.source == switch2.send_message_context_down.sign.source) {
                game_mode = !game_mode;
                switch2.change_text(mode_mes2[game_mode]);
                if (game_mode)
                    args[2][0] = 1122.0;
                else
                    args[2][0] = 1165.0;
            }
            if (cur_mes.sign.source == copy1.send_message_context_down.sign.source) {
                static int timess = 0;
                HWND hwnd = NULL;
                int i = 0;
                HGLOBAL hG = GlobalAlloc(GHND, 4096);
                wchar_t *p = (wchar_t *)GlobalLock(hG);
                for (i = 0; i < command1.output_string.size(); i++) {
                    p[i] = command1.output_string[i];
                }
                p[i] = 0;
                GlobalUnlock(hG);
                OpenClipboard(hwnd);
                EmptyClipboard();
                SetClipboardData(CF_UNICODETEXT, hG);
                CloseClipboard();
                GlobalFree(hG);
                if (timess) {
                    HWND hwnd = NULL;
                    int i = 0;
                    HGLOBAL hG = GlobalAlloc(GHND, 4096);
                    wchar_t *p = (wchar_t *)GlobalLock(hG);
                    for (i = 0; i < command1.output_string.size(); i++) {
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