#include "../include/drl_graph/coord.h"
#include <deque>
#include <functional>
#include <graphics.h>
#include <iostream>
#include <map>
#include <ostream>
#include <ratio>
#include <sstream>
#include <string>
#include <tchar.h>
#include <utility>
#include <vector>


#ifndef DRL_GUI_SIGNAL
#define DRL_GUI_SIGNAL 1

#ifdef UNICODE
using _TSTRING = std::wstring;
using _TOSTRINGSTREAM = std::wostringstream;
using _TISTRINGSTREAM = std::wistringstream;
using _TSTRINGSTREAM = std::wstringstream;
using _TOSTREAM = std::wostream;
#define _TO_TSTRING std::to_wstring
#define _TCOUT std::wcout
#else
using _TSTRING = std::string;
using _TOSTRINGSTREAM = std::ostringstream;
using _TISTRINGSTREAM = std::istringstream;
using _TSTRINGSTREAM = std::stringstream;
using _TOSTREAM = std::ostream;
#define _TCOUT std::cout
#define _TO_TSTRING std::to_string
#endif

#if __cplusplus == 202002L
#define can_concept 1
#else
#define concept 0
#endif

namespace drl
{
    using label_num_type = int;
    using label_str_type = _TSTRING;

#if can_concept
    template <class T, class U>
    concept can_print = requires(T t, U u) { _TCOUT << t << u; };
#endif
    class gui_signal
    {
     public:
        enum mess_base
        {
            system_message = 0,
            effect_message = 1
        };
        struct signal_t
        {
            ExMessage sys_mes;
            label_num_type mess_type;
            label_str_type source;
            label_str_type target;
        };
        friend std::ostream &operator<<(std::ostream &out, drl::gui_signal rhs);
        mess_base kind;
        signal_t sign;
        bool make_sence;
        bool mess_type_use;
        bool target_use;
        static label_str_type system_message_label;


     public:
#pragma region
        gui_signal()
            : kind(mess_base::system_message),
              sign({}),
              make_sence(false),
              mess_type_use(false),
              target_use(false)
        {}
        gui_signal(ExMessage sys_mes_, label_str_type source_,
                   label_num_type mess_type_ = label_num_type(), label_str_type target_ = label_str_type(),
                   bool mess_type_use_ = true, bool target_use_ = false)
            : make_sence(true),
              mess_type_use(mess_type_use_),
              target_use(target_use_)
        {
            sign.sys_mes = sys_mes_;
            sign.mess_type = mess_type_;
            sign.source = source_;
            sign.target = target_;
            kind = mess_base::system_message;
        }
        gui_signal(label_num_type mess_type_, label_str_type source_,
                   label_str_type target_ = label_str_type(),
                   bool mess_type_use_ = true, bool target_use_ = false)
            : make_sence(true),
              mess_type_use(mess_type_use_),
              target_use(target_use_)
        {
            sign.mess_type = mess_type_;
            sign.source = source_;
            sign.target = target_;
            kind = mess_base::effect_message;
        }
        gui_signal(ExMessage sys_mes_)
            : make_sence(true),
              mess_type_use(false),
              target_use(false)
        {
            sign.sys_mes = sys_mes_;
            sign.mess_type = 0;
            sign.source = system_message_label;
            sign.target = _T("");
            kind = mess_base::system_message;
        }
        gui_signal(const gui_signal &) = default;
        gui_signal(gui_signal &&) = default;
        gui_signal &operator=(const gui_signal &) = default;
        gui_signal &operator=(gui_signal &&) = default;
        int form() const
        {
            return kind;
        }
        const ExMessage &sys() const
        {
            return sign.sys_mes;
        }
        const label_str_type &source() const
        {
            return sign.source;
        }
        const label_num_type &mes_type() const
        {
            return sign.mess_type;
        }
        const label_str_type &target() const
        {
            return sign.target;
        }
        void clear(bool all = false)
        {
            mess_type_use = false;
            target_use = false;
            if (all)
            {
                sign.mess_type = label_num_type();
                sign.target = label_str_type();
            }
        }
        gui_signal &add_source_word(const _TSTRING &word)
        {
            sign.source += (_T(" ") + word);
            return *this;
        }
        gui_signal &del_fin_source_word(_TSTRING &deld)
        {
            auto c = sign.source.find_last_of(_T(' '));
            if (c != _TSTRING::npos)
            {
                deld.assign(sign.source, c);
                sign.source.erase(sign.source.find_last_of(_T(' ')), _TSTRING::npos);
            }
            else
            {
                deld.assign(_T(""));
            }
            return *this;
        }
        _TSTRING exac_word(unsigned long long num) const
        {
            num = num + 1;
            _TSTRING rec = _T("");
            unsigned long long temp1 = 0;
            _TSTRING::size_type l = 0;
            _TSTRING::size_type temp2 = _TSTRING::npos, temp3 = _TSTRING::npos;
            for (; l < sign.source.size(); l++)
            {
                if (temp1 == num - 1 && temp2 == _TSTRING::npos)
                    temp2 = l;
                if (temp1 == num && temp3 == _TSTRING::npos)
                    temp3 = l;
                if (sign.source[l] == _T(' '))
                    temp1++;
            }
            if (temp2 != _TSTRING::npos)
            {
                rec.assign(sign.source, temp2, temp3 - temp2 - 1);
            }

            return rec;
        }
        _TSTRING exac_fin_word() const
        {
            _TSTRING::size_type x = sign.source.find_last_of(_T(' '));
            if (x == _TSTRING::npos)
                return _TSTRING(sign.source, 0);
            return _TSTRING(sign.source, x + 1);
        }
        _TSTRING exac_word(unsigned long long l, unsigned long long r) const
        {
            l = l + 1;
            r = r + 1;
            _TSTRING rec;
            _TSTRING temp;
            rec = exac_word(l - 1);
            for (auto i = l + 1; i <= r; i++)
            {
                temp = exac_word(i - 1);
                if (temp.size())
                    rec += (_T(" ") + temp);
                else
                    break;
            }
            return rec;
        }

#pragma endregion
    };
    std::deque<gui_signal> &message_deque();
    std::ostream &operator<<(std::ostream &out, drl::gui_signal rhs);
    bool message_push_back(const gui_signal &message = gui_signal()) noexcept;
    bool message_push_front(const gui_signal &message = gui_signal()) noexcept;
    gui_signal message_pop_back(bool save = false) noexcept;
    gui_signal message_pop_front(bool save = false) noexcept;

    inline std::multimap<size_t, std::function<gui_signal(gui_signal)>> &system_fun_reg(void)
    {
        static std::multimap<size_t, std::function<gui_signal(gui_signal)>> func_ta;
        return func_ta;
    }
    inline void system_fun_reg(const std::function<bool(gui_signal)> &lhs,
                               const std::function<gui_signal(gui_signal)> &rhs, size_t pt)
    {
        auto c = [=](gui_signal p) -> gui_signal
        {
            if (lhs(p))
            {
                return rhs(p);
            }
            else
                return gui_signal();
        };
        system_fun_reg().insert(std::make_pair(pt, c));
    }



} // namespace drl

#undef concept

#endif