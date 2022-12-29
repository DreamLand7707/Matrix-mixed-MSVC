#include "../include/drl_graph/drl_gui_module.hpp"
#include "../include/drl_graph/drl_gui_signal.hpp"
#include <easyx.h>
#include <fstream>
#include <string>
#include <utility>

int main(void)
{
    using namespace drl;
    using std::make_pair;
    _TSTRINGSTREAM tcout;
    tcout.setf(std::ios::fixed, std::ios::floatfield);
    tcout.precision(3);
    initgraph(960, 960);
    BeginBatchDraw();
    setbkcolor(WHITE);
    cleardevice();
    FlushBatchDraw();
    drl::button_module A(250, 250, 450, 350, 30, 30, 50,
                         0xDDDDDD, 0xAAAAAa, 0x555555, GREEN, GREEN, GREEN, _T("LAST"), _T("微软雅黑"));
    drl::button_module B(250, 400, 450, 500, 30, 30, 50,
                         LIGHTBLUE, LIGHTMAGENTA, LIGHTCYAN, RED, BLUE, YELLOW, _T("NEXT"), _T("微软雅黑"));
    drl::button_module C(250, 550, 450, 650, 30, 30, 50,
                         LIGHTRED, LIGHTMAGENTA, LIGHTBLUE, GREEN, DARKGRAY, YELLOW, _T("QUIT"), _T("微软雅黑"));
    drl::input_box_module D(250, 700, 650, 750, 30, 3, 0xAAAAAA, 0x555555, 0x111111,
                            LIGHTRED, LIGHTRED, LIGHTRED, LIGHTBLUE, WHITE, WHITE, _T("微软雅黑"));
    drl::output_box_module E(600, 350, 900, 650, 30, 5, 0xDDDDDD, 0xDDDDDD, 0xDDDDDD,
                             LIGHTRED, LIGHTRED, LIGHTRED, BLACK, BLACK, BLACK, _T("微软雅黑"));
    drl::button_module F(50, 50, 100, 100, 30, 30, 50,
                         0xDDDDDD, 0xAAAAAa, 0x555555, GREEN, GREEN, GREEN, _T("="), _T("微软雅黑"));
    A.change_id(_T(" Basic"));
    B.change_id(_T(" Basic_2"));
    C.change_id(_T(" QUIT"));
    D.change_id(_T(" #1"));
    E.change_id(_T(" output#1"));
    F.change_id(_T(" ="));
    A.change_target(E.id);
    B.change_target(E.id);
    F.change_target(D.id);
    int t = 0, l = 0;
    A.inited();
    B.inited();
    C.inited();
    D.inited();
    E.inited();
    F.inited();
    drl::system_fun_reg<drl::button_module>(&A, &drl::button_module::condition, &drl::button_module::effect);
    drl::system_fun_reg<drl::button_module>(&B, &drl::button_module::condition, &drl::button_module::effect);
    drl::system_fun_reg<drl::button_module>(&C, &drl::button_module::condition, &drl::button_module::effect);
    drl::system_fun_reg<drl::input_box_module>(&D, &drl::input_box_module::condition, &drl::input_box_module::effect);
    drl::system_fun_reg<drl::output_box_module>(&E, &drl::output_box_module::condition, &drl::output_box_module::effect);
    drl::system_fun_reg<drl::button_module>(&F, &drl::button_module::condition, &drl::button_module::effect);

    TCHAR message[5][200] = {_T("Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!"),
                             _T("mixed_MSVC"),
                             _T("Rin and Len"),
                             _T("QUIT?"),
                             _T("QWERTY")};
    int temp18 = 0;
    drl::user_fun_reg().insert(
        make_pair(
            make_pair(1, A.send_message_context_down.sign.source),
            [&](drl::gui_module *pointer, const drl::gui_signal *a) -> drl::gui_signal
            {
                temp18--;
                if (temp18 < 0)
                    temp18 += 5;
                dynamic_cast<drl::output_box_module *>(pointer)->change_text(message[temp18]);
                return drl::gui_signal();
            }));
    drl::user_fun_reg().insert(
        make_pair(
            make_pair(1, B.send_message_context_down.sign.source),
            [&](drl::gui_module *pointer, const drl::gui_signal *a) -> drl::gui_signal
            {
                (temp18)++;
                if (temp18 > 4)
                    temp18 -= 5;
                dynamic_cast<drl::output_box_module *>(pointer)->change_text(message[temp18]);
                return drl::gui_signal();
            }));
    drl::user_fun_reg().insert(
        make_pair(
            make_pair(1, F.send_message_context_down.sign.source),
            [&](drl::gui_module *pointer, const drl::gui_signal *a) -> drl::gui_signal
            {
                drl::gui_signal res(1, D.module_basic + D.id + _T("_button=") + _T(" ") + D.input_string,
                                    E.id, true, true);
                res.kind = drl::gui_signal::effect_message;
                return res;
            }));

    char str1[300];
    char str2[400];

    drl::user_fun_reg().insert(
        make_pair(
            make_pair(1, D.module_basic + D.id + _T("_button=")),
            [&](drl::gui_module *pointer, const drl::gui_signal *a) -> drl::gui_signal
            {
                _TSTRINGSTREAM l;
                _TSTRING k;
                l.str(a->sign.source);
                l >> k >> k;
                k.clear();
                std::getline(l, k);

                auto p = WideCharToMultiByte(936, 0, k.c_str() + 1, k.size() - 1,
                                             str1, 300, NULL, NULL);
                sprintf(str2, "\"\"./Debug/cppdebug1.exe\" \"%.*s\" > ./source/1.txt\"", p, str1);
                system(str2);

                std::wfstream ld("./source/1.txt", std::wfstream::in);
                k.clear();
                std::getline(ld, k);


                dynamic_cast<output_box_module *>(pointer)->change_text(k);
                return drl::gui_signal();
            }));

    ExMessage temp1;
    while (1)
    {
        getmessage(&temp1, EM_MOUSE | EM_KEY);
        t++;
        drl::message_push_back(temp1);
        for (auto i = drl::message_pop_front();; i = drl::message_pop_front())
        {
            FlushBatchDraw();
            if (i.make_sence)
            {
                l++;
                for (auto j : drl::system_fun_reg())
                {
                    auto k = j(i);
                    if (k.make_sence)
                        message_push_back(k);
                }
            }
            if (i.sign.source == C.send_message_context_up.sign.source)
                exit(0);
            // if (i.sign.mess_type == drl::button_module::send_message_type)
            //     l++;
            {
                _TCOUT << i.sign.source << std::endl;
                _TCOUT << t << "|" << l << std::endl;
            }
            if (drl::message_deque().empty())
                break;
        }
    }
    EndBatchDraw();
    return 0;
}