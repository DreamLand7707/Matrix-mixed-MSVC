#include "../include/drl_graph/drl_gui_module.hpp"
#include "../include/drl_graph/drl_gui_signal.hpp"
#include <easyx.h>
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
                         0xDDDDDD, 0xAAAAAa, 0x555555, GREEN, GREEN, GREEN, _T("OK1"), _T("微软雅黑"));
    drl::button_module B(250, 400, 450, 500, 30, 30, 50,
                         LIGHTBLUE, LIGHTMAGENTA, LIGHTCYAN, RED, BLUE, YELLOW, _T("OK2"), _T("微软雅黑"));
    drl::button_module C(250, 550, 450, 650, 30, 30, 50,
                         LIGHTRED, LIGHTMAGENTA, LIGHTBLUE, GREEN, DARKGRAY, YELLOW, _T("QUIT"), _T("微软雅黑"));
    RECT text_area = {600, 100, 800, 200};
    RECT text_area_2 = {600, 200, 800, 300};
    A.change_id(_T(" Basic"));
    B.change_id(_T(" Basic_2"));
    C.change_id(_T(" QUIT"));
    A.change_target(drl::button_module::module_basic + A.id);
    int t = 0, l = 0;
    A.inited();
    B.inited();
    C.inited();
    drl::system_fun_reg<drl::button_module>(&A, &drl::button_module::condition, &drl::button_module::effect);
    drl::system_fun_reg<drl::button_module>(&B, &drl::button_module::condition, &drl::button_module::effect);
    drl::system_fun_reg<drl::button_module>(&C, &drl::button_module::condition, &drl::button_module::effect);
    drl::user_fun_reg().insert(
        make_pair(
            make_pair(1, A.send_message_context_down.sign.source),
            [](drl::gui_module *pointer, const drl::gui_signal *a) -> drl::gui_signal
            {
                // if (dynamic_cast<drl::button_module *>(pointer)->label_name == _T("OK"))
                _TCOUT << "You pressed OK!" << std::endl;
                return drl::gui_signal();
            }));
    time_t start_clock = clock();
    bool lk = false;
    ExMessage temp1;
    while (1)
    {
        lk = peekmessage(&temp1, EM_MOUSE);
        clearrectangle(text_area_2.left, text_area_2.top, text_area_2.right, text_area_2.bottom);
        settextstyle(50, 0, _T("微软雅黑"));
        settextcolor(LIGHTBLUE);
        tcout.str(_T(""));
        tcout << double(clock() - start_clock) / CLOCKS_PER_SEC;
        drawtext(tcout.str().c_str(), &text_area_2,
                 DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
        FlushBatchDraw();
        if (lk)
        {
            drl::message_push_back(temp1);
            for (auto i = drl::message_pop_front();; i = drl::message_pop_front())
            {
                if (i.make_sence)
                    for (auto j : drl::system_fun_reg())
                    {
                        auto k = j(i);
                        if (k.make_sence)
                            message_push_back(k);
                    }

                if (i.sign.source == C.send_message_context_up.sign.source)
                {
                    t++;
                }
                if (i.sign.mess_type == drl::button_module::send_message_type)
                {
                    l++;
                }
                if (i.sign.source != drl::gui_signal::system_message_label)
                {
                    _TCOUT << i.sign.source << std::endl;
                    _TCOUT << t << "|" << l << std::endl;
                    clearrectangle(text_area.left, text_area.top, text_area.right, text_area.bottom);
                    settextstyle(75, 0, _T("微软雅黑"));
                    settextcolor(LIGHTRED);
                    tcout.str(_T(""));
                    tcout << l;
                    drawtext(tcout.str().c_str(), &text_area, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);

                    FlushBatchDraw();
                }
                if (drl::message_deque().empty())
                    break;
            }
        }
        if (t == 1)
            break;
        if (l == 200)
            break;
    }
    EndBatchDraw();
    return 0;
}