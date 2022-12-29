#include "../include/drl_graph/drl_gui_module.hpp"
#include "../include/drl_graph/drl_gui_signal.hpp"
#include <algorithm>
#include <easyx.h>

_TOSTREAM drl::gui_signal::tcout(_TCOUT.rdbuf());

drl::button_module::label_str_type_ drl::gui_signal::system_message_label = _T("#s");

const drl::button_module::label_num_type_ drl::button_module::send_message_type = 1;
const drl::button_module::label_num_type_ drl::button_module::no_message = 0;
const drl::button_module::label_str_type_ drl::button_module::module_basic = _T("button");
const drl::button_module::label_str_type_ drl::button_module::down = _T(" down");
const drl::button_module::label_str_type_ drl::button_module::up = _T(" up");


const drl::input_box_module::label_num_type_ drl::input_box_module::send_message_type = 1;
const drl::input_box_module::label_num_type_ drl::input_box_module::no_message = 0;
const drl::input_box_module::label_str_type_ drl::input_box_module::module_basic = _T("input_box");
const drl::input_box_module::label_str_type_ drl::input_box_module::selected = _T(" selected");

const drl::output_box_module::label_num_type_ drl::output_box_module::no_message = 0;
const drl::output_box_module::label_str_type_ drl::output_box_module::module_basic = _T("output_box");

#define graflu FlushBatchDraw()
#pragma region signal

std::ostream &
drl::operator<<(std::ostream &out, drl::gui_signal rhs)
{
    rhs.print();
    return out;
}

std::deque<drl::gui_signal> &drl::message_deque()
{
    static std::deque<gui_signal> message_deque;
    return message_deque;
}

bool drl::message_push_back(const drl::gui_signal &mess) noexcept
{
    try
    {
        drl::message_deque().push_back(mess);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool drl::message_push_front(const drl::gui_signal &mess) noexcept
{
    try
    {
        drl::message_deque().push_front(mess);
        return true;
    }
    catch (...)
    {
        return false;
    }
}


drl::gui_signal drl::message_pop_back(bool save) noexcept
{
    try
    {
        if (save)
            return drl::message_deque().back();
        else
        {
            auto s = drl::message_deque().back();
            drl::message_deque().pop_back();
            return s;
        }
    }
    catch (...)
    {
        return drl::gui_signal();
    }
}
drl::gui_signal drl::message_pop_front(bool save) noexcept
{
    try
    {
        if (save)
            return drl::message_deque().front();
        else
        {
            auto s = drl::message_deque().front();
            drl::message_deque().pop_front();
            return s;
        }
    }
    catch (...)
    {
        return drl::gui_signal();
    }
}

#pragma endregion signal

#pragma region global

_TSTRING &drl::global_font()
{
    static _TSTRING global_font_(_T("微软雅黑"));
    return global_font_;
}

const _TSTRING drl::global_font(const _TSTRING &font)
{
    _TSTRING res;
    res = drl::global_font();
    drl::global_font() = font;
    return res;
}

const _TSTRING drl::mess_detail(const _TSTRING &d)
{
    if (d.size())
    {
        static _TSTRINGSTREAM ting;
        ting.clear();
        ting.str(d);
        _TSTRING res, res1;
        ting >> res;
        ting >> res1;
        if (res.size() && res1.size())
            res = res + _T(" ") + res1;
        return res;
    }
    else
        return _TSTRING();
}

#pragma endregion global

#pragma region module

#pragma region button
drl::button_module::message_type drl::button_module::inited()
{
    change_color(style.color[0]);
    make_text(style.text_color[0]);
    graflu;
    return message_type();
}

bool drl::button_module::_condition(const message_type &mess)
{
    if (mess.make_sence && ((message_class(mess.sys().message) == EX_MOUSE) ||
                            mess.kind == message_type::effect_message))
    {
        if (sys_type_filter_use && mess.mess_type_use)
        {
            if (std::find(sys_type_filter.begin(), sys_type_filter.end(), mess.sign.mess_type) == sys_type_filter.end())
                return false;
        }
        if (source_filter_use)
        {
            if (std::find(source_filter.begin(), source_filter.end(),
                          mess_detail(mess.sign.source)) == source_filter.end())
                return false;
        }
        if (mess.target_use)
        {
            if (id != mess.sign.target)
                return false;
        }
        return true;
    }
    else
        return false;
}

drl::button_module::message_type drl::button_module::effect(const message_type &mess)
{
    drl::gui_signal res(drl::button_module::no_message, drl::button_module::module_basic + id);
    res.kind = drl::gui_signal::effect_message;
    res.make_sence = false;
    if (mess.form() == drl::gui_signal::mess_base::system_message)
    {
        if (mode == 0)
        {
            if (mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom)
            {
                mode = 1;
                change_color(style.color[1]);
                make_text(style.text_color[1]);
            }
        }
        else if (mode == 1)
        {
            if (!(mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                  mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom))
            {
                mode = 0;
                change_color(style.color[0]);
                make_text(style.text_color[0]);
            }
            else
            {
                if (mess.sys().message == WM_LBUTTONDOWN)
                {
                    mode = 2;
                    change_color(style.color[2]);
                    make_text(style.text_color[2]);
                    flush();
                    return send_message_context_down;
                }
            }
        }
        else if (mode == 2)
        {
            if (mess.sys().message == WM_LBUTTONUP)
            {
                if (mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                    mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom)
                {
                    mode = 1;
                    change_color(style.color[1]);
                    make_text(style.text_color[1]);
                }
                else
                {
                    mode = 0;
                    change_color(style.color[0]);
                    make_text(style.text_color[0]);
                }
                flush();
                return send_message_context_up;
            }
        }
    }
    else if (mess.form() == drl::gui_signal::mess_base::effect_message)
    {
        res = drl::user_fun_reg(this, &mess);
    }
    flush();
    return res;
}
#pragma endregion button

#pragma region input_box

bool drl::input_box_module::_condition(const message_type &mess)
{
    if (mess.make_sence)
    {
        if ((message_class(mess.sys().message) == EX_MOUSE) ||
            (message_class(mess.sys().message) == EX_KEY) ||
            (mess.kind == message_type::effect_message))
        {
            if ((message_class(mess.sys().message) == EX_KEY) && (mode != 2))
            {
                return false;
            }
            if (sys_type_filter_use && mess.mess_type_use)
            {
                if (std::find(sys_type_filter.begin(), sys_type_filter.end(), mess.sign.mess_type) == sys_type_filter.end())
                    return false;
            }
            if (source_filter_use)
            {
                if (std::find(source_filter.begin(), source_filter.end(),
                              mess_detail(mess.sign.source)) == source_filter.end())
                    return false;
            }
            if (mess.target_use)
            {
                if (id != mess.sign.target)
                    return false;
            }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

drl::input_box_module::message_type drl::input_box_module::inited()
{
    change_color(style.fill_color[0], style.line_color[0]);
    make_text(style.text_color[0]);
    flush();
    return message_type();
}

drl::input_box_module::message_type drl::input_box_module::effect(const message_type &mess)
{
    message_type res(no_message, module_basic + id);
    res.make_sence = false;
    res.kind = drl::gui_signal::effect_message;
    if (mess.kind == drl::gui_signal::system_message)
    {
        if (message_class(mess.sys().message) == EX_MOUSE)
        {
            if (mode == 0)
            {
                if (mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                    mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom)
                {
                    mode = 1;
                    change_color(style.fill_color[1], style.line_color[1]);
                    make_text(style.text_color[1]);
                }
            }
            else if (mode == 1)
            {
                if (!(mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                      mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom))
                {
                    mode = 0;
                    change_color(style.fill_color[0], style.line_color[0]);
                    make_text(style.text_color[0]);
                }
                else if (mess.sys().message == WM_LBUTTONDOWN)
                {
                    static unsigned char modec;
                    settextstyle(style.text_size, 0, get_font().c_str());
                    modec = (textwidth(input_string.c_str()) >
                             (style.coord.right - style.coord.left - 2 * style.line_width))
                                ? 0
                                : 1;
                    mode = 2;
                    change_color(style.fill_color[2], style.line_color[2]);
                    make_text(style.text_color[2], modec);
                    flush();
                    return send_message_context;
                }
            }
            else if (mode == 2)
            {
                if (!(mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                      mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom) &&
                    mess.sys().message == WM_LBUTTONDOWN)
                {
                    mode = 0;
                    change_color(style.fill_color[0], style.line_color[0]);
                    make_text(style.text_color[0]);
                }
            }
        }
        else if (message_class(mess.sys().message) == EX_KEY)
        {
            if (mode == 2 && mess.sys().message == WM_KEYDOWN)
            {
                static BYTE code;
                static unsigned char modec;
                mode = 2;
                code = mess.sys().vkcode;
                if (code >= 0x30 && code <= 0x39)
                    input_string.push_back(code - 0x30 + L'0');
                else if (code >= 0x60 && code <= 0x69)
                    input_string.push_back(code - 0x60 + L'0');
                else if (code == 0xBE || code == 0x6E)
                    input_string.push_back(L'.');
                else if (code == VK_BACK)
                {
                    if (input_string.size())
                        input_string.pop_back();
                }
                settextstyle(style.text_size, 0, get_font().c_str());
                modec = (textwidth(input_string.c_str()) >
                         (style.coord.right - style.coord.left - 2 * style.line_width))
                            ? 0
                            : 1;
                change_color(style.fill_color[2], style.line_color[2]);
                make_text(style.text_color[2], modec);
            }
        }
    }
    else if (mess.kind == drl::gui_signal::effect_message)
    {
        res = drl::user_fun_reg(this, &mess);
    }
    flush();
    return res;
}

#pragma endregion input_box

#pragma region output_box

drl::output_box_module::message_type drl::output_box_module::inited()
{
    change_color(style.fill_color[0], style.line_color[0]);
    make_text(style.text_color[0]);
    flush();
    return message_type();
}

bool drl::output_box_module::_condition(const message_type &mess)
{
    if (mess.make_sence)
    {
        if ((message_class(mess.sys().message) == EX_MOUSE) ||
            (mess.kind == message_type::effect_message))
        {
            if ((message_class(mess.sys().message) == EX_KEY) && (mode != 2))
            {
                return false;
            }
            if (sys_type_filter_use && mess.mess_type_use)
            {
                if (std::find(sys_type_filter.begin(), sys_type_filter.end(), mess.sign.mess_type) == sys_type_filter.end())
                    return false;
            }
            if (source_filter_use)
            {
                if (std::find(source_filter.begin(), source_filter.end(),
                              mess_detail(mess.sign.source)) == source_filter.end())
                    return false;
            }
            if (mess.target_use)
            {
                if (id != mess.sign.target)
                    return false;
            }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

drl::output_box_module::message_type drl::output_box_module::effect(const message_type &mess)
{
    message_type res(no_message, module_basic + id);
    res.make_sence = false;
    res.kind = drl::gui_signal::effect_message;
    if (mess.kind == drl::gui_signal::system_message)
    {
        if (message_class(mess.sys().message) == EX_MOUSE)
        {
            if (mode == 0)
            {
                if (mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                    mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom)
                {
                    mode = 1;
                    change_color(style.fill_color[1], style.line_color[1]);
                    make_text(style.text_color[1]);
                }
            }
            else if (mode == 1)
            {
                if (!(mess.sys().x >= style.coord.left && mess.sys().x <= style.coord.right &&
                      mess.sys().y >= style.coord.top && mess.sys().y <= style.coord.bottom))
                {
                    mode = 0;
                    change_color(style.fill_color[0], style.line_color[0]);
                    make_text(style.text_color[0]);
                }
            }
        }
    }
    else if (mess.kind == drl::gui_signal::effect_message)
    {
        res = drl::user_fun_reg(this, &mess);
    }
    flush();
    return res;
}

#pragma endregion output_box

#pragma endregion module
