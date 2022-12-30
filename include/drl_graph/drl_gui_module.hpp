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
    class gui_module
    {
     public:
        using message_type = drl::gui_signal;
        using label_num_type_ = drl::label_num_type;
        using label_str_type_ = drl::label_str_type;

     private:
        bool virtual _condition(const message_type &) = 0;

     public:
        bool sys_type_filter_use;
        bool source_filter_use;
        bool lately_state;
        message_type lately_sign;
        label_str_type_ id;
        std::vector<label_num_type_> sys_type_filter;
        std::vector<label_str_type_> source_filter;
        gui_module(label_str_type_ id_ = {},
                   std::initializer_list<label_num_type_> a = {}, std::initializer_list<label_str_type_> b = {})
            : sys_type_filter_use(false),
              source_filter_use(false),
              lately_state(false),
              lately_sign(),
              id(id_),
              sys_type_filter(a),
              source_filter(b) {}
        bool virtual condition(const message_type &mess)
        {
            lately_sign = mess;
            return (lately_state = _condition(mess));
        }
        const message_type &sign() { return lately_sign; }
        void virtual change_id(const _TSTRING &new_id, bool change = true) { id = new_id; }
        void clear_sign() { lately_sign = message_type(); }
        void assign(std::vector<label_num_type_> lab_a, label_str_type_ lab_b,
                    std::vector<label_str_type_> label_rec_b_, bool lab_a_bool,
                    bool lab_b_bool)
        {
            sys_type_filter = lab_a;
            id = lab_b;
            source_filter = label_rec_b_;
            sys_type_filter_use = lab_a_bool;
            source_filter_use = lab_b_bool;
        }
        message_type virtual effect(const message_type &) = 0;
        message_type virtual inited() = 0;
    };

    class button_module : public gui_module
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
        const static label_str_type_ module_basic;
        const static label_str_type_ down;
        const static label_str_type_ up;

        button_module(int left_, int top_, int right_, int bottom_, int ellipsewidth_,
                      int ellipseheight_, int text_size_,
                      COLORREF color1, COLORREF color2, COLORREF color3,
                      COLORREF color4, COLORREF color5, COLORREF color6, _TSTRING label_name_,
                      label_str_type_ id_ = {}, _TSTRING font_ = {})
            : style({{left_, top_, right_, bottom_},
                     ellipsewidth_,
                     ellipseheight_,
                     text_size_,
                     {color1, color2, color3},
                     {color4, color5, color6}}),
              label_name(label_name_),
              font(font_),
              send_message_context_down(send_message_type, module_basic + id_ + down),
              send_message_context_up(send_message_type, module_basic + id_ + up) { gui_module::id = id_; }

        button_module(button_style sty) : style(sty) {}
        void virtual change_id(const _TSTRING &new_id, bool change = true)
        {
            id = new_id;
            if (change)
            {
                send_message_context_down.sign.source = module_basic + new_id + down;
                send_message_context_up.sign.source = module_basic + new_id + up;
            }
        }
        void virtual flush(void)
        {
            FlushBatchDraw(style.coord.left, style.coord.top,
                           style.coord.right, style.coord.bottom);
        }
        void change_text(_TSTRING text = _T(""), bool with_gra = true)
        {
            label_name = text;
            if (with_gra)
            {
                change_color(style.color[mode]);
                make_text(style.text_color[mode]);
            }
            flush();
        }
        void change_target(const _TSTRING &new_target)
        {
            send_message_context_down.sign.target = new_target;
            send_message_context_down.target_use = true;
            send_message_context_up.sign.target = new_target;
            send_message_context_up.target_use = true;
        }
        void change_color(COLORREF color)
        {
            setfillcolor(color);
            solidroundrect(style.coord.left, style.coord.top, style.coord.right,
                           style.coord.bottom, style.ellipsewidth, style.ellipseheight);
        }
        void make_text(COLORREF color)
        {
            setbkmode(TRANSPARENT);
            settextcolor(color);
            settextstyle(style.text_size, 0, get_font().c_str());
            drawtext(label_name.c_str(), &(style.coord),
                     DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
        }
    };

    class input_box_module : public gui_module
    {
     protected:
        bool virtual _condition(const message_type &);

     public:
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
        const static label_str_type_ module_basic;
        const static label_str_type_ selected;

        message_type virtual effect(const message_type &);
        message_type virtual inited();
        input_box_module(int left_, int top_, int right_, int bottom_,
                         int text_size_, int line_width_,
                         COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                         COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                         COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                         label_str_type_ id_ = {}, _TSTRING font_ = {})
            : style({{left_, top_, right_, bottom_},
                     text_size_,
                     line_width_,
                     {fill_color1, fill_color2, fill_color3},
                     {line_color1, line_color2, line_color3},
                     {text_color1, text_color2, text_color3}}),
              input_string(),
              font(font_),
              send_message_context(send_message_type, module_basic + id_ + selected)
        {
            gui_module::id = id_;
        }
        input_box_module(input_box_style sty) : style(sty) {}
        _TSTRING virtual get_font()
        {
            if (font.size())
                return font;
            else
                return global_font();
        }
        void virtual change_id(const _TSTRING &new_id, bool change = true)
        {
            id = new_id;
            if (change)
                send_message_context.sign.source = module_basic + new_id;
        }
        void virtual flush(void)
        {
            FlushBatchDraw(style.coord.left, style.coord.top,
                           style.coord.right, style.coord.bottom);
        }
        void change_text(_TSTRING text = _T(""), bool with_gra = true)
        {
            input_string = text;
            if (with_gra)
            {
                change_color(style.fill_color[mode], style.line_color[mode]);
                make_text(style.text_color[mode]);
            }
            flush();
        }
        void change_target(const _TSTRING &new_target)
        {
            send_message_context.sign.target = new_target;
            send_message_context.target_use = true;
        }
        void change_color(COLORREF color1, COLORREF color2)
        {
            setfillcolor(color1);
            setlinestyle(PS_SOLID, style.line_width);
            setlinecolor(color2);
            fillrectangle(style.coord.left, style.coord.top, style.coord.right, style.coord.bottom);
        }
        void make_text(COLORREF color, int l = 1)
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
        }
    };

    class output_box_module : public gui_module
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
        const static label_str_type_ module_basic;

        message_type virtual effect(const message_type &);
        message_type virtual inited();

        output_box_module(int left_, int top_, int right_, int bottom_,
                          int text_size_, int line_width_,
                          COLORREF fill_color1, COLORREF fill_color2, COLORREF fill_color3,
                          COLORREF line_color1, COLORREF line_color2, COLORREF line_color3,
                          COLORREF text_color1, COLORREF text_color2, COLORREF text_color3,
                          label_str_type_ id_ = {}, _TSTRING font_ = {})
            : style({{left_, top_, right_, bottom_},
                     text_size_,
                     line_width_,
                     {fill_color1, fill_color2, fill_color3},
                     {line_color1, line_color2, line_color3},
                     {text_color1, text_color2, text_color3}}),
              output_string(),
              font(font_)
        {
            gui_module::id = id_;
        }
        output_box_module(output_box_style sty) : style(sty) {}
        _TSTRING virtual get_font()
        {
            if (font.size())
                return font;
            else
                return global_font();
        }
        void virtual change_id(const _TSTRING &new_id, bool change = true)
        {
            id = new_id;
        }
        void virtual flush(void)
        {
            FlushBatchDraw(style.coord.left, style.coord.top,
                           style.coord.right, style.coord.bottom);
        }
        void change_text(_TSTRING text = _T(""), bool with_gra = true)
        {
            output_string = text;
            if (with_gra)
            {
                change_color(style.fill_color[mode], style.line_color[mode]);
                make_text(style.text_color[mode]);
            }
            flush();
        }
        void change_color(COLORREF color1, COLORREF color2)
        {
            setfillcolor(color1);
            setlinestyle(PS_SOLID, style.line_width);
            setlinecolor(color2);
            fillrectangle(style.coord.left, style.coord.top, style.coord.right, style.coord.bottom);
        }
        void make_text(COLORREF color)
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
        }
    };
#pragma region
    inline std::map<
        std::pair<const label_num_type, const label_str_type>,
        std::function<gui_signal(drl::gui_module *, const drl::gui_signal *)>> &
    user_fun_reg()
    {
        static std::map<
            std::pair<const label_num_type, const label_str_type>,
            std::function<gui_signal(drl::gui_module *, const drl::gui_signal *)>>
            fun_tab;
        return fun_tab;
    }
    inline gui_signal user_fun_reg(drl::gui_module *lhs, const drl::gui_signal *a)
    {
        try
        {
            return user_fun_reg().at(std::make_pair(a->sign.mess_type, mess_detail(a->sign.source)))(lhs, a);
        }
        catch (...)
        {
            return gui_signal();
        }
    }

    template <class T>
    inline void system_fun_reg(
        T *obj, bool (T::*lhs_fp)(const gui_module::message_type &),
        gui_module::message_type (T::*rhs_fp)(const gui_module::message_type &))
    {
        std::function<bool(gui_module::message_type)> lfun(
            std::bind(lhs_fp, obj, std::placeholders::_1));
        std::function<gui_module::message_type(gui_module::message_type)> rfun(
            std::bind(rhs_fp, obj, std::placeholders::_1));
        system_fun_reg(lfun, rfun);
    }
#pragma endregion
} // namespace drl

#endif