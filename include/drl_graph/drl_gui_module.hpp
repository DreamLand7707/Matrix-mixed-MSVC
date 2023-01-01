#include "drl_gui_signal.hpp"
#include <easyx.h>
#include <functional>
#include <initializer_list>
#include <type_traits>
#ifndef DRL_GUI_MODULE
#define DRL_GUI_MODULE 1

namespace drl
{

    _TSTRING &global_font(void);
    const _TSTRING global_font(const _TSTRING &);
    template <unsigned long long NUMBER>
    class gui_module_base
    {
     public:
        using message_type = drl::gui_signal;
        using label_num_type_ = drl::label_num_type;
        using label_str_type_ = drl::label_str_type;
        const static label_str_type_ module_basic;
        const label_str_type_ &id(void)
        {
            return id_in;
        }
        virtual gui_module_base &change_id(const _TSTRING &new_id, bool change = true)
        {
            id_in = module_basic + new_id;
            return *this;
        }

     protected:
        label_str_type_ id_in;
    };

    template <unsigned long long NUMBER>
    const drl::label_str_type gui_module_base<NUMBER>::module_basic = _T("BASIC");
    template <>
    const drl::label_str_type drl::gui_module_base<0>::module_basic;
    template <>
    const drl::label_str_type drl::gui_module_base<1>::module_basic;
    template <>
    const drl::label_str_type drl::gui_module_base<2>::module_basic;
    class gui_module
    {
     public:
        using message_type = drl::gui_signal;
        using label_num_type_ = drl::label_num_type;
        using label_str_type_ = drl::label_str_type;

     protected:
     private:
        bool virtual _condition(const message_type &) = 0;

     public:
        bool sys_type_filter_use;
        bool source_filter_use;
        bool lately_state;
        unsigned long long group;
        message_type lately_sign;
        std::vector<label_num_type_> sys_type_filter;
        std::vector<label_str_type_> source_filter;
        gui_module(unsigned long long group_ = 0,
                   std::initializer_list<label_num_type_> a = {}, std::initializer_list<label_str_type_> b = {})
            : sys_type_filter_use(false),
              source_filter_use(false),
              lately_state(false),
              group(group_),
              lately_sign(),
              sys_type_filter(a),
              source_filter(b) {}
        bool virtual condition(const message_type &mess)
        {
            lately_sign = mess;
            return (lately_state = _condition(mess));
        }
        const message_type &sign() { return lately_sign; }
        void clear_sign() { lately_sign = message_type(); }
        message_type virtual effect(const message_type &) = 0;
        message_type virtual inited() = 0;
    };
    template <class T>
    void system_fun_reg(
        T *obj,
        bool (T::*lhs_fp)(const gui_module::message_type &),
        gui_module::message_type (T::*rhs_fp)(const gui_module::message_type &),
        gui_module::message_type (T::*init_fp)(), size_t pt);
    class button_module : public gui_module, public gui_module_base<0>
    {
     protected:
        bool virtual _condition(const message_type &);

     public:
        struct button_style
        {
            RECT coord;
            int ellipsewidth;
            int ellipseheight;
            int text_size;
            COLORREF color[3];
            COLORREF text_color[3];
        } style;
        short mode = 0;
        _TSTRING label_name;
        _TSTRING font;
        message_type send_message_context_down;
        message_type send_message_context_up;

        message_type virtual effect(const message_type &);
        message_type virtual inited();
        _TSTRING virtual get_font()
        {
            if (font.size())
                return font;
            else
                return global_font();
        }
        const static label_num_type_ send_message_type;
        const static label_num_type_ no_message;
        // const static label_str_type_ module_basic;
        const static label_str_type_ down;
        const static label_str_type_ up;

        button_module(int left_, int top_, int right_, int bottom_, int ellipsewidth_,
                      int ellipseheight_, int text_size_,
                      COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                      COLORREF text_color1, COLORREF text_color2, COLORREF text_color3, _TSTRING label_name_,
                      label_str_type_ id_, _TSTRING font_ = {}, unsigned long long group = 1, bool regist = true)
            : gui_module(group),
              style({{left_, top_, right_, bottom_},
                     ellipsewidth_,
                     ellipseheight_,
                     text_size_,
                     {fill_color1, fill_color2, fill_color3},
                     {text_color1, text_color2, text_color3}}),
              label_name(label_name_),
              font(font_),
              send_message_context_down(send_message_type, module_basic + id_ + down),
              send_message_context_up(send_message_type, module_basic + id_ + up)
        {
            gui_module_base::id_in = module_basic + id_;
            if (regist)
            {
                drl::system_fun_reg<button_module>(this, &button_module::condition, &button_module::effect, &button_module::inited, group);
            }
        }

        button_module(int left_, int top_, int right_, int bottom_, int ellipsewidth_,
                      int ellipseheight_, int text_size_,
                      COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                      COLORREF text_color1, COLORREF text_color2, COLORREF text_color3, _TSTRING label_name_,
                      label_str_type_ id_, unsigned long long group, bool regist = true, _TSTRING font_ = {})
            : button_module(left_, top_, right_, bottom_, ellipsewidth_,
                            ellipseheight_, text_size_,
                            fill_color1, fill_color2, fill_color3,
                            text_color1, text_color2, text_color3, label_name_,
                            id_, font_, group, regist) {}

        button_module(int left_, int top_, int right_, int bottom_, int ellipsewidth_,
                      int ellipseheight_, int text_size_,
                      COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                      COLORREF text_color1, COLORREF text_color2, COLORREF text_color3, _TSTRING label_name_,
                      label_str_type_ id_, bool regist, unsigned long long group = 1, _TSTRING font_ = {})
            : button_module(left_, top_, right_, bottom_, ellipsewidth_,
                            ellipseheight_, text_size_,
                            fill_color1, fill_color2, fill_color3,
                            text_color1, text_color2, text_color3, label_name_,
                            id_, font_, group, regist) {}
        button_module(button_style sty) : style(sty) {}
        virtual gui_module_base &change_id(const _TSTRING &new_id, bool change = true)
        {
            id_in = module_basic + new_id;
            if (change)
            {
                send_message_context_down.sign.source = module_basic + new_id + down;
                send_message_context_up.sign.source = module_basic + new_id + up;
            }
            return *this;
        }
        virtual button_module &flush(void)
        {
            FlushBatchDraw(style.coord.left, style.coord.top,
                           style.coord.right, style.coord.bottom);
            return *this;
        }
        button_module &change_text(_TSTRING text = _T(""), bool with_gra = true)
        {
            label_name = text;
            if (with_gra)
            {
                change_color(style.color[mode]);
                make_text(style.text_color[mode]);
            }
            flush();
            return *this;
        }
        button_module &change_target(const _TSTRING &new_target)
        {
            send_message_context_down.sign.target = new_target;
            send_message_context_down.target_use = true;
            send_message_context_up.sign.target = new_target;
            send_message_context_up.target_use = true;
            return *this;
        }
        button_module &change_color(COLORREF color)
        {
            setfillcolor(color);
            solidroundrect(style.coord.left, style.coord.top, style.coord.right,
                           style.coord.bottom, style.ellipsewidth, style.ellipseheight);
            return *this;
        }
        button_module &make_text(COLORREF color)
        {
            setbkmode(TRANSPARENT);
            settextcolor(color);
            settextstyle(style.text_size, 0, get_font().c_str());
            drawtext(label_name.c_str(), &(style.coord),
                     DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
            return *this;
        }
    };

    class input_box_module : public gui_module, public gui_module_base<1>
    {
     protected:
        bool virtual _condition(const message_type &);

     public:
        using KKKKK = input_box_module;
        struct input_box_style
        {
            RECT coord;
            int text_size;
            int line_width;
            COLORREF fill_color[3];
            COLORREF line_color[3];
            COLORREF text_color[3];
        } style;
        short mode = 0;
        _TSTRING input_string;
        _TSTRING font;
        message_type send_message_context;

        const static label_num_type_ send_message_type;
        const static label_num_type_ no_message;
        // const static label_str_type_ module_basic;
        const static label_str_type_ selected;

        message_type virtual effect(const message_type &);
        message_type virtual inited();
        input_box_module(int left_, int top_, int right_, int bottom_,
                         int text_size_, int line_width_,
                         COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                         COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                         COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                         label_str_type_ id_, _TSTRING font_ = {}, unsigned long long group = 1, bool regist = true)
            : gui_module(group),
              style({{left_, top_, right_, bottom_},
                     text_size_,
                     line_width_,
                     {fill_color1, fill_color2, fill_color3},
                     {line_color1, line_color2, line_color3},
                     {text_color1, text_color2, text_color3}}),
              input_string(),
              font(font_),
              send_message_context(send_message_type, module_basic + id_ + selected)
        {
            gui_module_base::id_in = module_basic + id_;
            if (regist)
            {
                drl::system_fun_reg<input_box_module>(this, &input_box_module::condition, &input_box_module::effect, &input_box_module::inited, group);
            }
        }
        input_box_module(int left_, int top_, int right_, int bottom_,
                         int text_size_, int line_width_,
                         COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                         COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                         COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                         label_str_type_ id_, unsigned long long group, bool regist = true, _TSTRING font_ = {})
            : input_box_module(left_, top_, right_, bottom_,
                               text_size_, line_width_,
                               fill_color1, fill_color2, fill_color3,
                               line_color1, line_color2, line_color3,
                               text_color1, text_color2, text_color3,
                               id_, font_, group, regist) {}
        input_box_module(int left_, int top_, int right_, int bottom_,
                         int text_size_, int line_width_,
                         COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                         COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                         COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                         label_str_type_ id_, bool regist, unsigned long long group = 1, _TSTRING font_ = {})
            : input_box_module(left_, top_, right_, bottom_,
                               text_size_, line_width_,
                               fill_color1, fill_color2, fill_color3,
                               line_color1, line_color2, line_color3,
                               text_color1, text_color2, text_color3,
                               id_, font_, group, regist) {}

        input_box_module(input_box_style sty) : style(sty)
        {}
        _TSTRING virtual get_font()
        {
            if (font.size())
                return font;
            else
                return global_font();
        }
        virtual gui_module_base &change_id(const _TSTRING &new_id, bool change = true)
        {
            id_in = module_basic + new_id;
            if (change)
                send_message_context.sign.source = module_basic + new_id;
            return *this;
        }
        virtual input_box_module &flush(void)
        {
            FlushBatchDraw(style.coord.left, style.coord.top,
                           style.coord.right, style.coord.bottom);
            return *this;
        }
        input_box_module &change_text(_TSTRING text = _T(""), bool with_gra = true)
        {
            input_string = text;
            if (with_gra)
            {
                change_color(style.fill_color[mode], style.line_color[mode]);
                make_text(style.text_color[mode]);
            }
            flush();
            return *this;
        }
        input_box_module &change_target(const _TSTRING &new_target)
        {
            send_message_context.sign.target = new_target;
            send_message_context.target_use = true;
            return *this;
        }
        input_box_module &change_color(COLORREF color1, COLORREF color2)
        {
            setfillcolor(color1);
            setlinestyle(PS_SOLID, style.line_width);
            setlinecolor(color2);
            fillrectangle(style.coord.left, style.coord.top, style.coord.right, style.coord.bottom);
            return *this;
        }
        input_box_module &make_text(COLORREF color, int l = 1)
        { // l == 1则靠左 l == 0则靠右
            static RECT coord_text;
            coord_text = {
                style.coord.left + style.line_width,
                style.coord.top + style.line_width,
                style.coord.right - style.line_width,
                style.coord.bottom - style.line_width};
            if (l)
                l = DT_LEFT | DT_WORD_ELLIPSIS;
            else
                l = DT_RIGHT;
            setbkmode(TRANSPARENT);
            settextcolor(color);
            settextstyle(style.text_size, 0, get_font().c_str());
            drawtext(input_string.c_str(), &coord_text, l | DT_VCENTER | DT_SINGLELINE);
            return *this;
        }
    };

    class output_box_module : public gui_module, public gui_module_base<2>
    {
     protected:
        bool virtual _condition(const message_type &);

     public:
        struct output_box_style
        {
            RECT coord;
            int text_size;
            int line_width;
            COLORREF fill_color[3];
            COLORREF line_color[3];
            COLORREF text_color[3];
        } style;
        short mode = 0;
        _TSTRING output_string;
        _TSTRING font;
        const static label_num_type_ no_message;
        // const static label_str_type_ module_basic;

        message_type virtual effect(const message_type &);
        message_type virtual inited();

        output_box_module(int left_, int top_, int right_, int bottom_,
                          int text_size_, int line_width_,
                          COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                          COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                          COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                          label_str_type_ id_, _TSTRING font_ = {}, unsigned long long group = 1, bool regist = true)
            : gui_module(group),
              style({{left_, top_, right_, bottom_},
                     text_size_,
                     line_width_,
                     {fill_color1, fill_color2, fill_color3},
                     {line_color1, line_color2, line_color3},
                     {text_color1, text_color2, text_color3}}),
              output_string(),
              font(font_)
        {
            gui_module_base::id_in = module_basic + id_;
            if (regist)
            {
                drl::system_fun_reg<output_box_module>(this, &output_box_module::condition, &output_box_module::effect, &output_box_module::inited, group);
            }
        }
        output_box_module(int left_, int top_, int right_, int bottom_,
                          int text_size_, int line_width_,
                          COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                          COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                          COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                          label_str_type_ id_, unsigned long long group, bool regist = true, _TSTRING font_ = {})
            : output_box_module(left_, top_, right_, bottom_,
                                text_size_, line_width_,
                                fill_color1, fill_color2, fill_color3,
                                line_color1, line_color2, line_color3,
                                text_color1, text_color2, text_color3,
                                id_, font_, group, regist) {}
        output_box_module(int left_, int top_, int right_, int bottom_,
                          int text_size_, int line_width_,
                          COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                          COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                          COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                          label_str_type_ id_, bool regist, unsigned long long group = 1, _TSTRING font_ = {})
            : output_box_module(left_, top_, right_, bottom_,
                                text_size_, line_width_,
                                fill_color1, fill_color2, fill_color3,
                                line_color1, line_color2, line_color3,
                                text_color1, text_color2, text_color3,
                                id_, font_, group, regist) {}
        output_box_module(output_box_style sty) : style(sty) {}
        _TSTRING virtual get_font()
        {
            if (font.size())
                return font;
            else
                return global_font();
        }
        virtual gui_module_base &change_id(const _TSTRING &new_id, bool change = true)
        {
            id_in = module_basic + new_id;
            return *this;
        }
        virtual output_box_module &flush(void)
        {
            FlushBatchDraw(style.coord.left, style.coord.top,
                           style.coord.right, style.coord.bottom);
            return *this;
        }
        output_box_module &change_text(_TSTRING text = _T(""), bool with_gra = true)
        {
            output_string = text;
            if (with_gra)
            {
                change_color(style.fill_color[mode], style.line_color[mode]);
                make_text(style.text_color[mode]);
            }
            flush();
            return *this;
        }
        output_box_module &change_color(COLORREF color1, COLORREF color2)
        {
            setfillcolor(color1);
            setlinestyle(PS_SOLID, style.line_width);
            setlinecolor(color2);
            fillrectangle(style.coord.left, style.coord.top, style.coord.right, style.coord.bottom);
            return *this;
        }
        output_box_module &make_text(COLORREF color)
        { // l == 1则靠左 l == 0则靠右
            static RECT coord_text;
            coord_text = {
                style.coord.left + style.line_width,
                style.coord.top + style.line_width,
                style.coord.right - style.line_width,
                style.coord.bottom - style.line_width,
            };
            setbkmode(TRANSPARENT);
            settextcolor(color);
            settextstyle(style.text_size, 0, get_font().c_str());
            drawtext(output_string.c_str(), &coord_text,
                     DT_LEFT | DT_WORDBREAK | DT_WORD_ELLIPSIS);
            return *this;
        }
    };
#pragma region
    inline std::multimap<
        std::pair<const label_num_type, const label_str_type>,
        std::function<gui_signal(drl::gui_module *, const drl::gui_signal *)>> &
    user_fun_reg()
    {
        static std::multimap<
            std::pair<const label_num_type, const label_str_type>,
            std::function<gui_signal(drl::gui_module *, const drl::gui_signal *)>>
            fun_tab;
        return fun_tab;
    }
    inline gui_signal user_fun_reg(drl::gui_module *lhs, const drl::gui_signal *a)
    {
        try
        {
            auto lr = user_fun_reg().equal_range(std::make_pair(a->sign.mess_type, mess_detail(a->sign.source)));
            if (lr.first == lr.second)
                return gui_signal();
            lr.second--;
            gui_signal res;
            for (;; lr.first++)
            {
                if (lr.first == lr.second)
                {
                    res = lr.first->second(lhs, a);
                    break;
                }
                else
                    lr.first->second(lhs, a);
            }
            return res;
        }
        catch (...)
        {
            return gui_signal();
        }
    }


    inline std::multimap<size_t, std::function<gui_module::message_type()>> &inited_fun_reg()
    {
        static std::multimap<size_t, std::function<gui_module::message_type()>> init_fun_list;
        return init_fun_list;
    }
    inline void inited_fun_reg(const std::function<gui_module::message_type()> &fun, size_t pt)
    {
        inited_fun_reg().insert(std::make_pair(pt, fun));
    }
    template <class T>
    void system_fun_reg(
        T *obj,
        bool (T::*lhs_fp)(const gui_module::message_type &),
        gui_module::message_type (T::*rhs_fp)(const gui_module::message_type &),
        gui_module::message_type (T::*init_fp)(), size_t pt)
    {
        std::function<bool(gui_module::message_type)> lfun(
            std::bind(lhs_fp, obj, std::placeholders::_1));
        std::function<gui_module::message_type(gui_module::message_type)> rfun(
            std::bind(rhs_fp, obj, std::placeholders::_1));
        std::function<gui_module::message_type()> initfun(
            std::bind(init_fp, obj));
        inited_fun_reg(initfun, pt);
        system_fun_reg(lfun, rfun, pt);
    }

    inline std::pair<std::remove_reference<decltype(system_fun_reg())>::type::iterator,
                     std::remove_reference<decltype(system_fun_reg())>::type::iterator>
    system_fun_reg(size_t l, size_t r)
    {

        std::remove_reference<decltype(system_fun_reg())>::type::iterator
            lhs(system_fun_reg().lower_bound(l)),
            rhs(system_fun_reg().upper_bound(r));
        return std::pair(lhs, rhs);
    }
    inline std::pair<std::remove_reference<decltype(system_fun_reg())>::type::iterator,
                     std::remove_reference<decltype(system_fun_reg())>::type::iterator>
    system_fun_reg(size_t l)
    {

        std::remove_reference<decltype(system_fun_reg())>::type::iterator
            lhs(system_fun_reg().lower_bound(l)),
            rhs(system_fun_reg().upper_bound(l));
        return std::pair(lhs, rhs);
    }

    inline void init_group(size_t g1)
    {
        std::remove_reference<decltype(inited_fun_reg())>::type::iterator
            lhs(inited_fun_reg().lower_bound(g1)),
            rhs(inited_fun_reg().upper_bound(g1));
        for (; lhs != rhs; lhs++)
            lhs->second();
    }
    inline void init_group(size_t g1, size_t g2)
    {
        std::remove_reference<decltype(inited_fun_reg())>::type::iterator
            lhs(inited_fun_reg().lower_bound(g1)),
            rhs(inited_fun_reg().upper_bound(g2));
        for (; lhs != rhs; lhs++)
            lhs->second();
    }
#pragma endregion
} // namespace drl

#endif