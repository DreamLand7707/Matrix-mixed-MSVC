#ifndef drl_coord
#define drl_coord

#include <algorithm>
#include <cmath>
#include <graphics.h>
#include <initializer_list>
#include <iostream>
#include <numbers>
#include <numeric>
#include <sstream>
#include <string>
#include <tchar.h>
#include <utility>
#include <vector>

#ifdef UNICODE
using _TSTRING = std::wstring;
using _TOSTRINGSTREAM = std::wostringstream;
#else
using _TSTRING = std::string;
using _TOSTRINGSTREAM = std::ostringstream;
#endif

#ifdef __cplusplus
#endif

#pragma region // 类/函数定义部分

inline long double operator""_R(long double x)
{
    return std::numbers::pi_v<long double> * x / 180.0l;
}
inline long double operator""_R(unsigned long long x)
{
    return std::numbers::pi_v<long double> * x / 180.0l;
}

namespace drl // 线性运算主要部分
{
#pragma region // 对数倒数预定义函数
    template <class _x>
    inline _x ln_d(_x x)
    {
        __cplusplus;
        return log(fabs(x)) / log(exp(1));
    }
    template <class _x>
    inline _x pow_1_d(_x x)
    {
        return pow(x, -1);
    }
    template <class _x>
    inline _x x_sta_d(_x x)
    {
        return x;
    }
    typedef unsigned short ushort;
#pragma endregion
    namespace plot2_messages // 样式类定义
    {
#pragma region // graphstyle_s
        class graphstyle_s
        {
         public:
            enum class linestyle_
            {
                SOLID = PS_SOLID,
                DASH = PS_DASH,
                DOT = PS_DOT,
                DASHDOT = PS_DASHDOT,
                DASHDOTDOT = PS_DASHDOTDOT
            };
            enum class pointstyle_
            {
                SOLID = 0,
                SQUARE = 1,
                TRIA = 2,
                CIRCLE = 3,
                CROSS = 4,
                CIRCLECROSS = 5,
                SQUARECROSS = 6,
                TRIACROSS = 7,
                Star = 8,
                Nazi = 9,
            };
            COLORREF linecolor;     // 线颜色
            ushort linewidth;       // 线宽度
            linestyle_ linestyle;   // 线形状
            COLORREF pointcolor;    // 点颜色
            ushort pointsize;       // 点大小
            pointstyle_ pointstyle; // 点的样式

            linestyle_ scale_line_style_x;
            linestyle_ scale_line_style_y;

            linestyle_ main_scale_line_style_x;
            linestyle_ main_scale_line_style_y;

            unsigned int num_of_x;      // x轴信息的数量
            unsigned int num_of_y;      // y轴信息的数量
            unsigned int point_density; // 点密度

            unsigned int xnum_density;         // x轴信息的x点坐标的密度
            unsigned int ynum_density;         // y轴信息的y点坐标的密度
            unsigned int x_scaleplace_density; // x轴信息的x主坐标线的密度
            unsigned int y_scaleplace_density; // y轴信息的y主坐标线的密度

            ushort frame_width;               // 边框宽度
            ushort x_scaleplate_width;        // 坐标线的宽
            ushort x_main_scaleplate_width;   // 主坐标线的宽
            ushort y_scaleplate_width;        // 坐标线的宽
            ushort y_main_scaleplate_width;   // 主坐标线的宽
            COLORREF frame_color;             // 边框颜色
            COLORREF scaleplate_color;        // 坐标线的颜色
            COLORREF bkcolor;                 // 背景颜色
            COLORREF colorxtext;              // x轴文字的颜色
            COLORREF colorytext;              // y轴文字的颜色
            COLORREF colortitle;              // title的颜色
            COLORREF colorxnum;               // x轴坐标值的颜色
            COLORREF colorynum;               // y轴坐标值的颜色
            COLORREF color_main_x_scaleplace; // x轴主坐标线的颜色
            COLORREF color_main_y_scaleplace; // y轴主坐标线的颜色
            _TSTRING lougfont;                // 字体
            int point_line_width;             // 对于某种样式来说，线宽

            int width_window = 1920;
            int height_window = 1080;

            std::vector<double> line_ref_x;
            std::vector<double> line_ref_y;
            COLORREF color_line_ref_x;
            COLORREF color_line_ref_y;
            ushort line_ref_x_width;
            ushort line_ref_y_width;

            linestyle_ ref_line_style_x;
            linestyle_ ref_line_style_y;

            graphstyle_s(COLORREF linecolor_ = LIGHTBLUE,
                         ushort linewidth_ = 6,
                         linestyle_ linestyle__ = linestyle_::SOLID,
                         COLORREF pointcolor_ = LIGHTRED,
                         ushort pointsize_ = 8,
                         pointstyle_ pointstyle_ = pointstyle_::SOLID,

                         linestyle_ scale_line_style_x_ = linestyle_::SOLID,
                         linestyle_ scale_line_style_y_ = linestyle_::SOLID,

                         linestyle_ main_scale_line_style_x_ = linestyle_::SOLID,
                         linestyle_ main_scale_line_style_y_ = linestyle_::SOLID,
                         unsigned int num_of_x_ = 6,
                         unsigned int num_of_y_ = 6,
                         unsigned int point_density_ = 1,

                         unsigned int xnum_density_ = 1,
                         unsigned int ynum_density_ = 1,
                         unsigned int x_scaleplace_density_ = 3,
                         unsigned int y_scaleplace_density_ = 3,

                         ushort frame_width_ = 8,
                         ushort x_scaleplate_width_ = 4,
                         ushort x_main_scaleplate_width_ = 4,
                         ushort y_scaleplate_width_ = 4,
                         ushort y_main_scaleplate_width_ = 4,
                         COLORREF frame_color_ = RGB(0x33, 0x33, 0x33),
                         COLORREF scaleplate_color_ = LIGHTGRAY,
                         COLORREF bkcolor_ = RGB(0xEE, 0xEE, 0xEE),
                         COLORREF colorxtext_ = BLACK,
                         COLORREF colorytext_ = BLACK,
                         COLORREF colortitle_ = BLACK,
                         COLORREF colorxnum_ = BLACK,
                         COLORREF colorynum_ = BLACK,

                         COLORREF color_main_x_scaleplace_ = RGB(0x11, 0x11, 0x11),
                         COLORREF color_main_y_scaleplace_ = RGB(0x11, 0x11, 0x11),

                         _TSTRING lougfont_ = _T("微软雅黑"),
                         int point_line_width_ = 3,

                         std::initializer_list<double> ref_of_x = {},
                         std::initializer_list<double> ref_of_y = {},

                         COLORREF color_ref_x = GREEN,
                         COLORREF color_ref_y = MAGENTA,
                         ushort line_ref_x_width_ = 2,
                         ushort line_ref_Y_width = 2,

                         linestyle_ ref_line_style_x_ = linestyle_::SOLID,
                         linestyle_ ref_line_style_y_ = linestyle_::SOLID)
                : linecolor(linecolor_), linewidth(linewidth_), linestyle(linestyle__), pointcolor(pointcolor_), pointsize(pointsize_), pointstyle(pointstyle_), scale_line_style_x(scale_line_style_x_), scale_line_style_y(scale_line_style_y_), main_scale_line_style_x(main_scale_line_style_x_), main_scale_line_style_y(main_scale_line_style_y_), num_of_x(num_of_x_), num_of_y(num_of_y_), point_density(point_density_), xnum_density(xnum_density_), ynum_density(ynum_density_), x_scaleplace_density(x_scaleplace_density_), y_scaleplace_density(y_scaleplace_density_), frame_width(frame_width_), x_scaleplate_width(x_scaleplate_width_), x_main_scaleplate_width(x_main_scaleplate_width_), y_scaleplate_width(y_scaleplate_width_), y_main_scaleplate_width(y_main_scaleplate_width_), frame_color(frame_color_), scaleplate_color(scaleplate_color_), bkcolor(bkcolor_), colorxtext(colorxtext_), colorytext(colorytext_), colortitle(colortitle_), colorxnum(colorxnum_), colorynum(colorynum_), color_main_x_scaleplace(color_main_x_scaleplace_), color_main_y_scaleplace(color_main_y_scaleplace_), lougfont(lougfont_), point_line_width(point_line_width_), line_ref_x(ref_of_x), line_ref_y(ref_of_y), color_line_ref_x(color_ref_x), color_line_ref_y(color_ref_y), line_ref_x_width(line_ref_x_width_), line_ref_y_width(line_ref_Y_width), ref_line_style_x(ref_line_style_x_), ref_line_style_y(ref_line_style_y_)
            {
            }
        };
#pragma endregion
#pragma region // range_para
        class range_para
        {
         public:
            std::pair<double, double> x_minmax;
            std::pair<double, double> y_minmax;
            bool xdefaulted = true;
            bool ydefaulted = true;
            double x_ratio;
            double y_ratio;
            int pres; // 精度
            decltype(std::ios::floatfield) output;

         public:
            range_para(const std::pair<double, double> &l = std::pair<double, double>({0.0, 0.0}),
                       const std::pair<double, double> &r = std::pair<double, double>({0.0, 0.0}),
                       const bool &xde = true, const bool &yde = true, int pres_ = 3,
                       const double x_ratio_ = 1.1, const double y_ratio_ = 1.1,
                       decltype(std::ios::floatfield) output_ = std::ios::fixed)
                : x_minmax(l), y_minmax(r), xdefaulted(xde), ydefaulted(yde), x_ratio(x_ratio_), y_ratio(y_ratio_), pres(pres_), output(output_)
            {
            }
        };
#pragma endregion
#pragma region // act_para
        class act_para
        {
         public:
            bool title;        // 启用标题？
            bool axis;         // 启用坐标轴？
            bool mess_x;       // 启用x坐标轴文本？
            bool mess_y;       // 启用y坐标轴文本？
            bool x_;           // 启用x坐标轴线？
            bool y_;           // 启用y坐标轴线？
            bool x_num;        // 启用x坐标轴数？
            bool y_num;        // 启用y坐标轴数？
            bool point_;       // 启用描点？
            bool draw_line_;   // 启用画线？
            bool clear_all;    // 是否清除全部？
            bool x_main_scale; // 是否启用x主坐标线
            bool y_main_scale; // 是否启用y主坐标线
            bool clip;         // 是否启用裁剪
            bool clip_detail;  // 裁剪细节
            bool polar;        // TODO启用极坐标
            bool part_graph;   // 部分绘图
            bool x_ref_line;
            bool y_ref_line;
            act_para(bool titled = true, bool axised = true, bool mess_xd = true, bool mess_yd = true,
                     bool x_d = true, bool y_d = true, bool x_numd = true, bool y_numd = true,
                     bool point_d = false, bool draw_line_d = true,
                     bool clear_alld = true,
                     bool x_main_scaled = true, bool y_main_scaled = true,
                     bool clipd = true, bool clip_detailed = false,
                     bool polard = false, bool part_graphd = false,
                     bool x_ref = true, bool y_ref = true)
                : title(titled), axis(axised), mess_x(mess_xd), mess_y(mess_yd), x_(x_d), y_(y_d), x_num(x_numd), y_num(y_numd), point_(point_d), draw_line_(draw_line_d), clear_all(clear_alld), x_main_scale(x_main_scaled), y_main_scale(y_main_scaled), clip(clipd), clip_detail(clip_detailed), polar(polard), part_graph(part_graphd), x_ref_line(x_ref), y_ref_line(y_ref)
            {
            }
        };
#pragma endregion
#pragma region // image_message
        class image_message
        {
         public:
            _TSTRING x_mess;
            _TSTRING y_mess;
            _TSTRING title;
            image_message(const _TSTRING &x = _T("X"), const _TSTRING &y = _T("Y"), const _TSTRING &title_ = _T(""))
            {
                x_mess = x;
                y_mess = y;
                if (title_.size())
                    title = title_;
                else
                    title = x + _T(" - ") + y;
            }
        };
#pragma endregion
    }          // namespace plot2_messages
#pragma region // 预定义样式
    inline const plot2_messages::graphstyle_s default_graphstyle;
    inline const plot2_messages::range_para default_range_para;
    inline const plot2_messages::act_para default_act_para;
    inline const plot2_messages::image_message default_image_message;

    inline const drl::plot2_messages::graphstyle_s
        darkmode_graphstyle(LIGHTCYAN, 6, ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID,
                            LIGHTRED, 8, ::drl::plot2_messages::graphstyle_s::pointstyle_::SOLID,
                            ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID,
                            ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID,
                            ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID,
                            ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID,
                            6, 6, 1, 1, 1, 3, 3, 8, 4, 4, 4, 4, RGB(0xcc, 0xcc, 0xcc), DARKGRAY, RGB(0x11, 0x11, 0x11),
                            WHITE, WHITE, WHITE, WHITE, WHITE, RGB(0xee, 0xee, 0xee), RGB(0xee, 0xee, 0xee),
                            _T("微软雅黑"), 3, {}, {}, LIGHTGREEN, LIGHTMAGENTA, 2, 2,
                            ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID,
                            ::drl::plot2_messages::graphstyle_s::linestyle_::SOLID);
    inline const std::pair<int, int> basic_wh{8, 7};

#pragma endregion
#pragma region // xy绘图
    template <class _x, class _y>
    auto pict_curve_xy(IMAGE *image, const std::pair<_x, _x> &x, const std::pair<_y, _y> &y,
                       const plot2_messages::graphstyle_s &graph_style = default_graphstyle,
                       const plot2_messages::range_para &range_ = default_range_para,
                       const plot2_messages::image_message &messages = default_image_message,
                       const plot2_messages::act_para &act_paras_ = default_act_para,
                       bool ucover = false)
        -> std::pair<std::pair<typename _x::value_type,
                               typename _x::value_type>,
                     std::pair<typename _y::value_type,
                               typename _y::value_type>>

    {
#pragma region // IMAGE控制
        if (image)
        {
            if (image->getwidth() > 25600)
                image->Resize(25600, image->getheight());
            if (image->getheight() > 16000)
                image->Resize(image->getwidth(), 16000);
        }
        std::pair<typename _y::value_type, typename _y::value_type> returnd;
#pragma endregion
#pragma region // 变量定义

        int window[2]{};
        if (image)
        {
            window[0] = (image->getwidth());
            window[1] = (image->getheight());
        }
        else
        {
            window[0] = graph_style.width_window;
            window[1] = graph_style.height_window;
        }
        float aspectratio[2]; // 变化前的缩放因子
        IMAGE *image_before;
        FILLSTYLE *fillstyle_before = new FILLSTYLE;
        LINESTYLE *linestyle_before = new LINESTYLE;
        LOGFONT *LOGFONT_before = new LOGFONT;
        int bkmode_before;
        std::vector<COLORREF> colors_before;
        image_before = GetWorkingImage();
#pragma endregion
#pragma region // 设置基本信息
        SetWorkingImage(image);
        getaspectratio(aspectratio, aspectratio + 1);
        getfillstyle(fillstyle_before);
        getlinestyle(linestyle_before);
        gettextstyle(LOGFONT_before);
        bkmode_before = getbkmode();
        colors_before.push_back(getbkcolor());
        colors_before.push_back(getfillcolor());
        colors_before.push_back(getlinecolor());
        colors_before.push_back(gettextcolor());
        if (act_paras_.clear_all && !ucover && !act_paras_.part_graph)
        {
            setbkcolor(graph_style.bkcolor);
            cleardevice();
        }
        else if (act_paras_.part_graph)
        {
            double k = -graph_style.frame_width / 2.0;
            k = graph_style.frame_width / 2.0 + graph_style.pointsize;
            setbkcolor(graph_style.bkcolor);
            clearrectangle(int(window[0] * 0.1 - k),
                           int(window[1] * 0.2 - k),
                           int(window[0] * 0.9 + k),
                           int(window[1] * 0.9 + k));
        }
        setbkmode(TRANSPARENT);
#pragma endregion
#pragma region // 开始绘图
        if (!image)
            BeginBatchDraw();
        if (!ucover && !act_paras_.part_graph)
        {
            if (act_paras_.title) // 是否启用Titie？
            {
                settextcolor(graph_style.colortitle);
                int text_points[2]{};
                text_points[0] = static_cast<int>(floor(window[1] * 0.08));

                textwidth(messages.title.c_str());  //
                textheight(messages.title.c_str()); //

                settextstyle(text_points[0], 0, graph_style.lougfont.c_str());

                textwidth(messages.title.c_str());  //
                textheight(messages.title.c_str()); //

                for (int i = text_points[0]; textwidth(messages.title.c_str()) > window[1]; i -= 4)
                    settextstyle(i, 0, graph_style.lougfont.c_str());
                auto width_temp1 = textwidth(messages.title.c_str());
                text_points[0] = window[0] / 2 - width_temp1 / 2;
                text_points[1] = static_cast<int>(floor(window[1] * 0.01));
                outtextxy(text_points[0], text_points[1], messages.title.c_str());
            }
        }
        if (!ucover)
        {
            if (act_paras_.axis)
            {
                if (act_paras_.x_ || act_paras_.y_ || act_paras_.x_num || act_paras_.y_num ||
                    act_paras_.x_ref_line || act_paras_.y_ref_line) // 是否启用坐标轴？
                {
                    setlinecolor(graph_style.frame_color);
                    setlinestyle(PS_SOLID, graph_style.frame_width);
                    int posts[4]{};
                    posts[0] = (int)(window[0] * 0.1);
                    posts[1] = (int)(window[1] * 0.2);
                    posts[2] = (int)(window[0] * 0.9);
                    posts[3] = (int)(window[1] * 0.9);
                    rectangle(posts[0], posts[1], posts[2], posts[3]);
                    std::vector<std::vector<int>> points(2);
                    // setlinestyle(int(graph_style.scale_line_style_x), graph_style.scaleplate_width);
                    int width_of_num;
                    int height_of_num;
                    _TSTRING coordnum;
                    if (act_paras_.x_ || act_paras_.x_num || act_paras_.x_ref_line)
                    {
                        settextcolor(graph_style.colorxnum);
                        for (unsigned int i = 0; i <= graph_style.num_of_x; i++)
                        {
                            if (act_paras_.x_)
                            {
                                if (i != 0 && i != graph_style.num_of_x)
                                {
                                    if (!act_paras_.x_main_scale || i % graph_style.x_scaleplace_density != 0)
                                    {
                                        setlinestyle(int(graph_style.scale_line_style_x), graph_style.x_scaleplate_width);
                                        setlinecolor(graph_style.scaleplate_color);
                                    }
                                    else
                                    {
                                        setlinestyle(int(graph_style.main_scale_line_style_x), graph_style.x_main_scaleplate_width);
                                        setlinecolor(graph_style.color_main_x_scaleplace);
                                    }
                                    line(int(window[0] * (0.1 + i * (0.9 - 0.1) / graph_style.num_of_x)),
                                         posts[1] + graph_style.frame_width / 2,
                                         int(window[0] * (0.1 + i * (0.9 - 0.1) / graph_style.num_of_x)),
                                         posts[3] - graph_style.frame_width / 2);
                                }
                            }
                            if (act_paras_.x_num && !act_paras_.part_graph)
                            {
                                if (i % graph_style.xnum_density == 0 || i == graph_style.num_of_x)
                                {
                                    double max, min, deltad;
                                    if (range_.xdefaulted)
                                    {
                                        max = (double)*(std::max_element(x.first, x.second));
                                        min = (double)*(std::min_element(x.first, x.second));
                                        double temp1 = max - min;
                                        max += temp1 * (range_.x_ratio - 1) / 2.0;
                                        min -= temp1 * (range_.x_ratio - 1) / 2.0;
                                    }
                                    else
                                    {
                                        min = range_.x_minmax.first;
                                        max = range_.x_minmax.second;
                                        double temp1 = max - min;
                                        max += temp1 * (range_.x_ratio - 1) / 2.0;
                                        min -= temp1 * (range_.x_ratio - 1) / 2.0;
                                    }
                                    deltad = (max - min) / graph_style.num_of_x;
                                    {
                                        _TOSTRINGSTREAM tcout;
                                        tcout.precision(range_.pres);
                                        tcout.setf(range_.output, std::ios::floatfield);
                                        tcout << (min + i * deltad);
                                        coordnum = tcout.str();
                                    }
                                    settextstyle(static_cast<int>(window[1] * 0.04), 0, graph_style.lougfont.c_str());
                                    for (int i = static_cast<int>(window[1] * 0.04);
                                         textwidth(coordnum.c_str()) > int(window[0] * graph_style.xnum_density * 0.8 / graph_style.num_of_x) * 4 / 5; i = i - 4)
                                        settextstyle(i, 0, graph_style.lougfont.c_str());
                                    width_of_num = textwidth(coordnum.c_str());
                                    outtextxy((int)(window[0] * (0.1 + i * (0.9 - 0.1) / graph_style.num_of_x) - width_of_num / 2.0),
                                              (int)(window[1] * 0.93), coordnum.c_str());
                                }
                            }
                        }
                        if (act_paras_.x_ref_line)
                        {
                            // setlinestyle(int(graph_style.ref_line_style_x), graph_style.scaleplate_width);
                            setlinecolor(graph_style.color_line_ref_x);
                            setlinestyle(int(graph_style.ref_line_style_x), graph_style.line_ref_x_width);
                            double x_min, x_max;
                            double x_ratio;
                            if (range_.xdefaulted)
                            {
                                x_max = (double)*(std::max_element(x.first, x.second));
                                x_min = (double)*(std::min_element(x.first, x.second));
                                double temp1 = x_max - x_min;
                                x_max += temp1 * (range_.x_ratio - 1) / 2.0;
                                x_min -= temp1 * (range_.x_ratio - 1) / 2.0;
                            }
                            else
                            {
                                x_min = range_.x_minmax.first;
                                x_max = range_.x_minmax.second;
                                double temp1 = x_max - x_min;
                                x_max += temp1 * (range_.x_ratio - 1) / 2.0;
                                x_min -= temp1 * (range_.x_ratio - 1) / 2.0;
                            }
                            x_ratio = (window[0] * 0.8) / (x_max - x_min);
                            for (int i = 0; i < graph_style.line_ref_x.size(); i++)
                                line(int(x_ratio * (-x_min + *(graph_style.line_ref_x.begin() + i)) + posts[0]),
                                     posts[1] + graph_style.frame_width / 2,
                                     int(x_ratio * (-x_min + *(graph_style.line_ref_x.begin() + i)) + posts[0]),
                                     posts[3] - graph_style.frame_width / 2);
                        }
                    }
                    // setlinestyle(int(graph_style.scale_line_style_y), graph_style.scaleplate_width);
                    if (act_paras_.y_ || act_paras_.y_num || act_paras_.y_ref_line)
                    {
                        settextcolor(graph_style.colorynum);
                        for (unsigned int i = 0; i <= graph_style.num_of_y; i++)
                        {
                            if (act_paras_.y_)
                            {
                                if (i != 0 && i != graph_style.num_of_y)
                                {
                                    if (!act_paras_.y_main_scale || i % graph_style.y_scaleplace_density != 0)
                                    {
                                        setlinestyle(int(graph_style.scale_line_style_y), graph_style.y_scaleplate_width);
                                        setlinecolor(graph_style.scaleplate_color);
                                    }
                                    else
                                    {
                                        setlinestyle(int(graph_style.main_scale_line_style_y), graph_style.y_main_scaleplate_width);
                                        setlinecolor(graph_style.color_main_y_scaleplace);
                                    }
                                    line(posts[0] + graph_style.frame_width / 2,
                                         (int)(window[1] * (0.2 + i * (0.9 - 0.2) / graph_style.num_of_y)),
                                         posts[2] - graph_style.frame_width / 2,
                                         (int)(window[1] * (0.2 + i * (0.9 - 0.2) / graph_style.num_of_y)));
                                }
                            }
                            if (act_paras_.y_num && !act_paras_.part_graph)
                            {
                                if (i % graph_style.ynum_density == 0 || i == graph_style.num_of_y)
                                {
                                    double max, min, deltad;
                                    if (range_.ydefaulted)
                                    {
                                        max = (double)*(std::max_element(y.first, y.second));
                                        min = (double)*(std::min_element(y.first, y.second));
                                        double temp1 = max - min;
                                        max += temp1 * (range_.y_ratio - 1) / 2.0;
                                        min -= temp1 * (range_.y_ratio - 1) / 2.0;
                                    }
                                    else
                                    {
                                        min = range_.y_minmax.first;
                                        max = range_.y_minmax.second;
                                        double temp1 = max - min;
                                        max += temp1 * (range_.y_ratio - 1) / 2.0;
                                        min -= temp1 * (range_.y_ratio - 1) / 2.0;
                                    }
                                    deltad = (max - min) / graph_style.num_of_y;
                                    {
                                        _TOSTRINGSTREAM tcout;
                                        tcout.precision(range_.pres);
                                        tcout.setf(range_.output, std::ios::floatfield);
                                        tcout << max - i * deltad;
                                        coordnum = tcout.str();
                                    }
                                    settextstyle(int(window[1] * 0.1) * 3 / 5, 0, graph_style.lougfont.c_str());
                                    for (int i = (int)(window[1] * graph_style.ynum_density * ((0.9 - 0.2) / graph_style.num_of_y)) * 4 / 5; textwidth(coordnum.c_str()) > window[0] * 0.06; i = i - 4)
                                        settextstyle(i, 0, graph_style.lougfont.c_str());
                                    height_of_num = textheight(coordnum.c_str());
                                    width_of_num = textwidth(coordnum.c_str());
                                    outtextxy(posts[0] - width_of_num - int(window[0] * 0.02),
                                              (int)(window[1] * (0.2 + i * (0.9 - 0.2) / graph_style.num_of_y)) - height_of_num / 2,
                                              coordnum.c_str());
                                }
                            }
                        }
                        if (act_paras_.y_ref_line)
                        {
                            setlinecolor(graph_style.color_line_ref_y);
                            setlinestyle(int(graph_style.ref_line_style_y), graph_style.line_ref_y_width);
                            double y_min, y_max;
                            double y_ratio;
                            if (range_.ydefaulted)
                            {
                                y_max = (double)*(std::max_element(y.first, y.second));
                                y_min = (double)*(std::min_element(y.first, y.second));
                                double temp1 = y_max - y_min;
                                y_max += temp1 * (range_.y_ratio - 1) / 2.0;
                                y_min -= temp1 * (range_.y_ratio - 1) / 2.0;
                            }
                            else
                            {
                                y_min = range_.y_minmax.first;
                                y_max = range_.y_minmax.second;
                                double temp1 = y_max - y_min;
                                y_max += temp1 * (range_.y_ratio - 1) / 2.0;
                                y_min -= temp1 * (range_.y_ratio - 1) / 2.0;
                            }
                            y_ratio = (window[1] * 0.7) / (y_max - y_min);
                            for (int i = 0; i < graph_style.line_ref_y.size(); i++)
                                line(posts[0] + graph_style.frame_width / 2,
                                     int(y_ratio * (y_max - *(graph_style.line_ref_y.begin() + i)) + window[1] * 0.2),
                                     posts[2] - graph_style.frame_width / 2,
                                     int(y_ratio * (y_max - *(graph_style.line_ref_y.begin() + i)) + window[1] * 0.2));
                        }
                    }
                    if ((act_paras_.mess_x || act_paras_.mess_y) && !act_paras_.part_graph) // 是否启用坐标轴信息？
                    {
                        int text_points[2]{};
                        if (act_paras_.mess_y)
                        {
                            settextcolor(graph_style.colorytext);
                            text_points[0] = static_cast<int>(window[1] * 0.08);
                            settextstyle(text_points[0], 0, graph_style.lougfont.c_str());
                            for (int i = text_points[0] - 4; textwidth(messages.y_mess.c_str()) > window[0] * 0.9; i = i - 4)
                                settextstyle(i, 0, graph_style.lougfont.c_str());
                            text_points[0] = static_cast<int>(window[0] * 0.1);
                            text_points[1] = static_cast<int>(window[1] * 0.12);
                            outtextxy(text_points[0], text_points[1], messages.y_mess.c_str());
                        }
                        if (act_paras_.mess_x)
                        {
                            settextstyle(int(window[1] * 0.1), 0, graph_style.lougfont.c_str());
                            for (int i = int(window[1] * 0.1) - 4;
                                 textwidth(messages.x_mess.c_str()) > window[0] * 0.08;
                                 i = i - 4)
                                settextstyle(i, 0, graph_style.lougfont.c_str());
                            auto width_temp1 = textheight(messages.x_mess.c_str());
                            text_points[0] = static_cast<int>(floor(window[0] * 0.92));
                            text_points[1] = static_cast<int>(floor(window[1] * 0.9 - width_temp1));
                            settextcolor(graph_style.colorxtext);
                            outtextxy(text_points[0], text_points[1], messages.x_mess.c_str());
                        }
                    }
                }
            }
        }
        if (act_paras_.draw_line_ || act_paras_.point_) // 是否启用描点|画线？
        {
            if (act_paras_.clip)
            {
                double k = -graph_style.frame_width / 2.0;
                if (act_paras_.clip_detail)
                    k = graph_style.frame_width / 2.0 + graph_style.pointsize;
                HRGN rgn = CreateRectRgn(int(window[0] * 0.1 - k),
                                         int(window[1] * 0.2 - k),
                                         int(window[0] * 0.9 + k),
                                         int(window[1] * 0.9 + k));
                setcliprgn(rgn);
                DeleteObject(rgn);
            }
            double x_min, x_max, y_min, y_max;
            double x_ratio, y_ratio;
            if (range_.xdefaulted)
            {
                x_max = (double)*(std::max_element(x.first, x.second));
                x_min = (double)*(std::min_element(x.first, x.second));
                double temp1 = x_max - x_min;
                x_max += temp1 * (range_.x_ratio - 1) / 2.0;
                x_min -= temp1 * (range_.x_ratio - 1) / 2.0;
            }
            else
            {
                x_min = range_.x_minmax.first;
                x_max = range_.x_minmax.second;
                double temp1 = x_max - x_min;
                x_max += temp1 * (range_.x_ratio - 1) / 2.0;
                x_min -= temp1 * (range_.x_ratio - 1) / 2.0;
            }
            if (range_.ydefaulted)
            {
                y_max = (double)*(std::max_element(y.first, y.second));
                y_min = (double)*(std::min_element(y.first, y.second));
                double temp1 = y_max - y_min;
                y_max += temp1 * (range_.y_ratio - 1) / 2.0;
                y_min -= temp1 * (range_.y_ratio - 1) / 2.0;
            }
            else
            {
                y_min = range_.y_minmax.first;
                y_max = range_.y_minmax.second;
                double temp1 = y_max - y_min;
                y_max += temp1 * (range_.y_ratio - 1) / 2.0;
                y_min -= temp1 * (range_.y_ratio - 1) / 2.0;
            }
            x_ratio = (window[0] * 0.8) / (x_max - x_min);
            y_ratio = (window[1] * 0.7) / (y_max - y_min);
            auto distan = x.second - x.first;

            if (act_paras_.draw_line_)
            {
                setlinecolor(graph_style.linecolor);
                setlinestyle((int)graph_style.linestyle, graph_style.linewidth);
                for (int i = 1; i < distan; i++)
                    line(int(x_ratio * (-x_min + *(x.first + (i - 1))) + window[0] * 0.1),
                         int(y_ratio * (y_max - *(y.first + (i - 1))) + window[1] * 0.2),
                         int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                         int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2));
            }
            if (act_paras_.point_)
            {
                setfillcolor(graph_style.pointcolor);
                for (int i = 0; i < distan; i++)
                {
                    if (i % graph_style.point_density == 0 || i == distan - 1)
                        switch (graph_style.pointstyle)
                        {
                        case drl::plot2_messages::graphstyle_s::pointstyle_::SOLID: {
                            solidcircle(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                        int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                        graph_style.pointsize);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::CIRCLE: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            circle(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                   int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                   graph_style.pointsize);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::TRIA: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            POINT s[3]{};
                            s[0].x = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1);
                            s[0].y = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize;
                            s[1].x = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize;
                            s[1].y = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize;
                            s[2].x = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize;
                            s[2].y = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize;
                            polygon(s, 3);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::SQUARE: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            rectangle(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                      int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                      int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                      int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::CROSS: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            line(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                 int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);

                            line(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                 int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::CIRCLECROSS: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            line(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                 int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            line(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                 int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            circle(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                   int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                   graph_style.pointsize);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::SQUARECROSS: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            line(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                 int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            line(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                 int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                 int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            rectangle(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize,
                                      int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize,
                                      int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize,
                                      int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::TRIACROSS: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            int x0 = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                y0 = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                size = graph_style.pointsize;
                            POINT s[3]{};
                            s[0].x = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1);
                            s[0].y = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) - graph_style.pointsize;
                            s[1].x = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) - graph_style.pointsize;
                            s[1].y = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize;
                            s[2].x = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1) + graph_style.pointsize;
                            s[2].y = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2) + graph_style.pointsize;
                            polygon(s, 3);
                            line(x0, y0, x0, y0 - size);
                            line(x0, y0, x0 - size, y0 + size);
                            line(x0, y0, x0 + size, y0 + size);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::Star: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            int x0 = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                y0 = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                size = graph_style.pointsize / 2;
                            line(x0 - size, y0 - size / 2, x0 + size, y0 + size / 2);
                            line(x0 + size, y0 - size / 2, x0 - size, y0 + size / 2);
                            line(x0, y0 + size, x0, y0 - size);
                            break;
                        }
                        case drl::plot2_messages::graphstyle_s::pointstyle_::Nazi: {
                            setlinecolor(graph_style.pointcolor);
                            setlinestyle(PS_SOLID, graph_style.point_line_width);
                            int x0 = int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                y0 = int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                size = graph_style.pointsize / 2;
                            line(x0 - size, y0 - size, x0 + size, y0 + size);
                            line(x0 + size, y0 - size, x0 - size, y0 + size);
                            line(x0, y0 - 2 * size, x0 - size, y0 - size);
                            line(x0 + 2 * size, y0, x0 + size, y0 - size);
                            line(x0, y0 + 2 * size, x0 + size, y0 + size);
                            line(x0 - size, y0 + size, x0 - 2 * size, y0);
                            break;
                        }
                        default:
                            solidcircle(int(x_ratio * (-x_min + *(x.first + i)) + window[0] * 0.1),
                                        int(y_ratio * (y_max - *(y.first + i)) + window[1] * 0.2),
                                        graph_style.pointsize);
                            break;
                        }
                }
            }
            setcliprgn(NULL);
        }
#pragma endregion
#pragma region // 恢复状态
        if (range_.ydefaulted)
        {
            returnd.second = (double)*(std::max_element(y.first, y.second));
            returnd.first = (double)*(std::min_element(y.first, y.second));
        }
        else
        {
            returnd.first = range_.y_minmax.first;
            returnd.second = range_.y_minmax.second;
        }
        if (!image)
            EndBatchDraw();
        setfillstyle(fillstyle_before);
        setlinestyle(linestyle_before);
        settextstyle(LOGFONT_before);
        setbkmode(bkmode_before);
        setbkcolor(colors_before[0]);
        setfillcolor(colors_before[1]);
        setlinecolor(colors_before[2]);
        settextcolor(colors_before[3]);
        setbkmode(bkmode_before);
        SetWorkingImage(image_before);
        delete fillstyle_before;
        delete linestyle_before;
        delete LOGFONT_before;

        if (range_.xdefaulted)
            return std::make_pair(std::make_pair(*std::min_element(x.first, x.second), *std::max_element(x.first, x.second)),
                                  returnd);
        else
            return std::make_pair(range_.x_minmax, returnd);
#pragma endregion
    }
#pragma endregion
#pragma region // xfun绘图
    template <class _x, class _y>
    auto pict_curve_xfun(IMAGE *image, const std::pair<_x, _x> &x, const _y &y,
                         const plot2_messages::graphstyle_s &graph_style = default_graphstyle,
                         const plot2_messages::range_para &range_ = default_range_para,
                         const plot2_messages::image_message &messages = default_image_message,
                         const plot2_messages::act_para &act_paras_ = default_act_para, bool pi = false)
        -> std::pair<std::pair<typename _x::value_type,
                               typename _x::value_type>,
                     std::pair<typename _x::value_type,
                               typename _x::value_type>>
    {
        std::vector<typename _x::value_type> _y_;
        for (_x i = x.first; i != x.second; i++)
            _y_.push_back(y(*i));
        return pict_curve_xy(image, x, std::make_pair(_y_.begin(), _y_.end()), graph_style, range_, messages, act_paras_, pi);
    }
#pragma endregion
#pragma region // 线性函数表
    template <class _x = decltype(x_sta_d<double>) *>
    auto linear_fun_(short i) -> std::pair<_x, _x>
    {
        if (i == (short)0)
            return std::make_pair(x_sta_d<double>, x_sta_d<double>);
        if (i == (short)1)
            return std::make_pair(ln_d<double>, x_sta_d<double>);
        if (i == (short)2)
            return std::make_pair(x_sta_d<double>, ln_d<double>);
        if (i == (short)3)
            return std::make_pair(x_sta_d<double>, ln_d<double>);
        if (i == (short)4)
            return std::make_pair(ln_d<double>, ln_d<double>);
        if (i == (short)5)
            return std::make_pair(x_sta_d<double>, pow_1_d<double>);
        else
            return std::make_pair(x_sta_d<double>, x_sta_d<double>);
    }
#pragma endregion
#pragma region // 线性最小二乘
    template <class _x, class _y, class _funx, class _funy>
    auto least_square(
        const std::pair<_x, _x> &x, const std::pair<_y, _y> &y,
        const _funx &funx, const _funy &funy, short i = -1)
        -> std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                     std::pair<typename _x::value_type, short>>
    {
        typename _x::value_type temp1 = 0;
        typename _x::value_type temp2 = 0;
        typename _x::value_type temp3 = 0;
        typename _x::value_type x_aver;
        typename _x::value_type y_aver;
        auto n = x.second - x.first;
        std::vector<std::vector<typename _x::value_type>>
            temp_vec(2);

        for (int j = 0; j < n; j++)
        {
            temp_vec[0].push_back(funx(*(x.first + j)));
            temp_vec[1].push_back(funy(*(y.first + j)));
        }
        x_aver = std::accumulate(temp_vec[0].begin(), temp_vec[0].end(), 0.0) / n;
        y_aver = std::accumulate(temp_vec[1].begin(), temp_vec[1].end(), 0.0) / n;
        for (int i = 0; i < n; i++)
            temp1 += temp_vec[0][i] * temp_vec[1][i];
        temp1 -= n * x_aver * y_aver;
        auto temp1_ = temp1;
        for (int i = 0; i < n; i++)
            temp2 += temp_vec[0][i] * temp_vec[0][i];
        temp2 -= n * x_aver * x_aver;
        auto temp2_ = temp2;
        typename _x::value_type temp3_ = 0;
        for (int i = 0; i < n; i++)
            temp3_ += temp_vec[1][i] * temp_vec[1][i];
        temp3_ -= n * y_aver * y_aver;
        temp2_ = sqrt(temp2_ * temp3_);
        temp1 /= temp2;
        temp3 = y_aver - temp1 * x_aver;
        temp2 = temp1_ / temp2_;
        return std::make_pair(std::make_pair(temp1, temp3), std::make_pair(temp2, i));
    }
    /// @brief
    /// @param i 0. y = ax + b |
    // 1. y = alnx + b |
    // 2. y = b * e^(ax) |
    // 3. y = b * a^x |
    // 4. y = b * x^a |
    // 5. y = b + a/x |
    template <class _x, class _y, class _funx = double (*)(double), class _funy = double (*)(double)>
    auto least_square(
        const std::pair<_x, _x> &x, const std::pair<_y, _y> &y,
        short i = 0)
        -> std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                     std::pair<typename _x::value_type, short>>
    {
        const _funx &funx = linear_fun_(i).first;
        const _funy &funy = linear_fun_(i).second;
        typename _x::value_type y_aver;
        auto n = x.second - x.first;
        y_aver = std::accumulate(y.first, y.second, 0.0) / n;
        if (y_aver < 0 && i >= 2 && i <= 4)
            i = -i;
        return drl::least_square(x, y, funx, funy, i);
    }
#pragma endregion
#pragma region // 对元素排列
    template <class _x, class _y, class _x_p, class _y_p>
    auto element_xy_sort_copy(
        const std::pair<_x, _x> &x_ele, const std::pair<_y, _y> &y_ele, const _x_p &x_iter, const _y_p &y_iter)
        -> std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                     std::pair<typename _y::value_type, typename _y::value_type>>
    {
        typename _x::value_type x_max = *std::max_element(x_ele.first, x_ele.second);
        typename _x::value_type x_min = *std::min_element(x_ele.first, x_ele.second);
        typename _y::value_type y_max = *std::max_element(y_ele.first, y_ele.second);
        typename _y::value_type y_min = *std::min_element(y_ele.first, y_ele.second);

        std::vector<std::pair<typename _x::value_type, typename _y::value_type>> points;
        for (auto i = x_ele.first; i != x_ele.second; i++)
            points.push_back(std::make_pair(*i, *((y_ele.first) + int(i - x_ele.first))));
        static auto sort_fun = [](const std::pair<typename _x::value_type, typename _x::value_type> &l,
                                  const std::pair<typename _y::value_type, typename _y::value_type> &r) {
            return l.first < r.first;
        };
        std::sort(points.begin(), points.end(), sort_fun);
        for (int i = 0; i < points.size(); i++)
        {
            *(x_iter + i) = points[i].first;
            *(y_iter + i) = points[i].second;
        }

        return std::make_pair(std::make_pair(x_min, x_max), std::make_pair(y_min, y_max));
    }
#pragma endregion
#pragma region // 回归绘制

    template <class _x>
    inline _x a_x_plus_b(const std::pair<_x, _x> &ab, const _x &x)     // y = ax + b
    {                                                                  // *
        return ab.first * x + ab.second;                               // *
    }                                                                  // *
    template <class _x>                                                // *
    inline _x b_plus_a_lnx(const std::pair<_x, _x> &ab, const _x &x)   // y = alnx + b
    {                                                                  // *
        return ab.first * ln_d(x) + ab.second;                         // *
    }                                                                  // *
    template <class _x>                                                // *
    inline _x b_exp_a_x(const std::pair<_x, _x> &ab, const _x &x)      // y = b * e^(ax),传递的是lnb a
    {                                                                  // *
        return exp(ab.second) * exp(ab.first * x);                     // *
    }                                                                  // *
    template <class _x>                                                // *
    inline _x b_pow_a_x(const std::pair<_x, _x> &ab, const _x &x)      // y = b * a^x,传递的是lna lnb
    {                                                                  // *
        return exp(ab.second) * pow(exp(ab.first), x);                 // *
    }                                                                  // *
    template <class _x>                                                // *
    inline _x b_pow_x_a(const std::pair<_x, _x> &ab, const _x &x)      // y = b * x^a,传递的是lnb a
    {                                                                  // *
        return exp(ab.second) * pow(x, ab.first);                      // *
    }                                                                  // *
    template <class _x>                                                // *
    inline _x b_plus_a_div_x(const std::pair<_x, _x> &ab, const _x &x) // y = b + a/x
    {
        return ab.second + ab.first / x;
    }
    inline const std::vector<decltype(drl::a_x_plus_b<double>) *> reg_funs{
        (drl::a_x_plus_b<double>), (drl::b_plus_a_lnx<double>), (drl::b_exp_a_x<double>),
        (drl::b_pow_a_x<double>), (drl::b_pow_x_a<double>), (drl::b_plus_a_div_x<double>)};
    template <class _x>
    _TSTRING reg_mess(const std::pair<std::pair<_x, _x>,
                                      std::pair<_x, short>>
                          &args,
                      decltype(std::ios::floatfield) po = decltype(std::ios::floatfield)(0), int pres = 4)
    {
        _TOSTRINGSTREAM tcout;
        tcout.precision(pres);
        tcout.setf(po, std::ios::floatfield);
        _x p;
        if (args.second.second < 0)
            p = -1;
        else
            p = 1;
        if (args.second.second == 0)
            tcout << _T("y=(") << p * args.first.first << _T(")*x+(")
                  << args.first.second << _T(") R=") << args.second.first;
        if (args.second.second == 1)
            tcout << _T("y=(") << p * args.first.first << _T(")*lnx+(")
                  << args.first.second << _T(") R=") << args.second.first;
        if (args.second.second == 2)
            tcout << _T("y=(") << p * exp(args.first.second) << _T(")*e^((")
                  << args.first.first << _T(")*x) R=") << args.second.first;
        if (args.second.second == 3)
            tcout << _T("y=(") << p * exp(args.first.second) << _T(")*(")
                  << exp(args.first.first) << _T(")^x R=") << args.second.first;
        if (args.second.second == 4)
            tcout << _T("y=(") << p * exp(args.first.second) << _T(")*x^(")
                  << args.first.first << _T(") R=") << args.second.first;
        if (args.second.second == 5)
            tcout << _T("y=(") << p * args.first.second << _T(")+(")
                  << args.first.first << _T(")/x R=") << args.second.first;
        return tcout.str();
    }
    template <class _x, class _y>
    auto line_reg_function(const std::pair<_x, _x> &x, const _y &y_iter,
                           const std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                                           std::pair<typename _x::value_type, short>>
                               &args)
        -> std::pair<typename _x::value_type, typename _x::value_type>
    {
        typename _x::value_type y_max, y_min, temp;
        typename _x::value_type p;
        if (args.second.second < 0 && args.second.second != -1)
            p = -1;
        else
            p = 1;
        for (auto i = x.first; i != x.second; i++)
        {
            if (i == x.first)
            {
                *(y_iter + (i - x.first)) = p * (reg_funs[abs(args.second.second)])(args.first, *i);
                y_max = (*(y_iter + (i - x.first)));
                y_min = (*(y_iter + (i - x.first)));
            }
            else
            {
                temp = *(y_iter + (i - x.first)) = p * (reg_funs[abs(args.second.second)])(args.first, *i);
                if (y_min > temp)
                    y_min = temp;
                if (y_max < temp)
                    y_max = temp;
            }
        }
        return std::make_pair(y_min, y_max);
    }
#pragma endregion
#pragma region // 回归分析
    template <class _x, class _y>
    auto line_reg_analysis(const std::pair<_x, _x> &x, const std::pair<_y, _y> &y)
        -> std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                     std::pair<typename _x::value_type, short>>
    {
        std::vector<std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                              std::pair<typename _x::value_type, short>>>
            Rs;
        Rs.push_back(least_square(x, y, 0)); // ax+b
        Rs.push_back(least_square(x, y, 1)); // b+alnx
        Rs.push_back(least_square(x, y, 2)); // bx+lna
        Rs.push_back(least_square(x, y, 3)); // lnbx+lna
        Rs.push_back(least_square(x, y, 4)); // lna+blnx
        Rs.push_back(least_square(x, y, 5)); // a+b/x
        auto square_fun =
            [](std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                         std::pair<typename _x::value_type, short>>
                   l,
               std::pair<std::pair<typename _x::value_type, typename _x::value_type>,
                         std::pair<typename _x::value_type, short>>
                   r)
            -> bool {
            return pow(l.second.first, 2) < pow(r.second.first, 2);
        };
        auto c = std::max_element(Rs.begin(), Rs.end(), square_fun);
        return *c;
    }
#pragma endregion
} // namespace drl
#ifdef MATRIX_DRL_USE // 对多次回归的drl支持
#include "../include/basic_matr_class.h"

namespace drl // 多次运算部分
{
    const int max_degree = 5;
#pragma region // 多次回归方程
    template <class _x, class _y, class _z = drl::matrix>
    auto degree_reg(const std::pair<_x, _x> &x_mess, const std::pair<_y, _y> &y_mess, const short degree)
        -> std::pair<std::shared_ptr<drl::matrix>, std::pair<typename _x::value_type, short>>
    {
        if (x_mess.second - x_mess.first == y_mess.second - y_mess.first)
        {
            using drl::matrix;
            matrix X(int(x_mess.second - x_mess.first), int(degree + 1), 1.0), y(int(x_mess.second - x_mess.first), 1);
            for (int i = 0; i < X.size(1); i++)
            {
                for (int j = 1; j < X.size(2); j++)
                    X[i][j] = pow(*(x_mess.first + i), j);
                y[i][0] = *(y_mess.first + i);
            }
            std::shared_ptr<drl::matrix> b =
                std::make_shared<drl::matrix>(((X ^ matr_tag::T) * y) /
                                              ((X ^ matr_tag::T) * (X)));
            for (int i = 1; b->size(2) != 1; i++)
            {
                b->rsim(1, 0);
                b->rdel(1);
            }
            double QT = 0.0, QR = 0.0, R;
            double y_aver = std::accumulate(y_mess.first, y_mess.second, 0.0) / (y_mess.second - y_mess.first);
            for (auto i = y_mess.first; i != y_mess.second; i++)
                QT += pow((*i - y_aver), 2);
            QR = ((*b ^ matr_tag::T) * (X ^ matr_tag::T) * y)[0][0] - (y_mess.second - y_mess.first) * y_aver * y_aver;
            R = sqrt(QR / QT);
            if (R > 1.0)
                R = 1.0;
            return std::make_pair(b, std::make_pair(R, degree));
        }
        else
            return std::make_pair(std::make_shared<_z>(matr::Err),
                                  std::make_pair(0.0, (short)-1));
    }
#pragma endregion
#pragma region // 多次回归方程输出
    template <class _x, class _y, class _z = drl::matrix>
    auto degree_reg_fun(const std::pair<_x, _x> &x_mess, const _y &y_mess,
                        const std::pair<std::shared_ptr<drl::matrix>,
                                        std::pair<typename _x::value_type, short>> &args)
        -> std::pair<typename _x::value_type, typename _x::value_type>
    {
        typename _x::value_type y_max, y_min, temp;
        for (int i = 0; i < x_mess.second - x_mess.first; i++)
        {
            *(y_mess + i) = 0;
            for (int j = 0; j <= args.second.second; j++)
            {
                *(y_mess + i) += args.first->operator[](j)[0] * pow(*(x_mess.first + i), j);
            }
            temp = *(y_mess + i);
            if (i == 0)
            {
                y_max = temp;
                y_min = temp;
            }
            else
            {
                if (y_max < temp)
                    y_max = temp;
                if (y_min > temp)
                    y_min = temp;
            }
        }
        return std::make_pair(y_min, y_max);
    }
#pragma endregion
#pragma region // 多次回归方程信息
    template <class _x>
    _TSTRING degree_reg_mess(const std::pair<std::shared_ptr<drl::matrix>,
                                             std::pair<_x, short>> &args,
                             decltype(std::ios::floatfield) po = decltype(std::ios::floatfield)(0), int pres = 4)
    {
        _TOSTRINGSTREAM tcout;
        tcout.precision(pres);
        tcout.setf(po, std::ios::floatfield);
        drl::matrix b = *(args.first);
        b.lrev();
        tcout << _T("y = ");
        for (int i = 0; i <= args.second.second; i++)
        {
            if (i != args.second.second && i != args.second.second - 1)
                tcout << _T("(") << b[i][0] << _T(")x^") << args.second.second - i;
            else if (i == args.second.second - 1)
                tcout << _T("(") << b[i][0] << _T(")x");
            else
                tcout << _T("(") << b[i][0] << _T(")");
            if (i != args.second.second)
                tcout << " + ";
        }
        tcout << " R = " << args.second.first;
        return tcout.str();
    }
#pragma endregion
#pragma region // 多次回归分析
    template <class _x, class _y, class _z = drl::matrix>
    auto degree_analy(const std::pair<_x, _x> &x_mess, const std::pair<_y, _y> &y_mess)
        -> std::pair<std::shared_ptr<drl::matrix>, std::pair<typename _x::value_type, short>>
    {
        std::vector<std::pair<std::shared_ptr<drl::matrix>, std::pair<typename _x::value_type, short>>> mess(max_degree);
        for (int i = 1; i <= max_degree; i++)
        {
            mess[i - 1] = degree_reg(x_mess, y_mess, i);
        }
        auto fun1 = [](std::pair<std::shared_ptr<drl::matrix>, std::pair<typename _x::value_type, short>> &l, std::pair<std::shared_ptr<drl::matrix>, std::pair<typename _x::value_type, short>> &r) -> bool

        {
            return l.second.first < r.second.first;
        };
        auto p = *std::max_element(mess.begin(), mess.end(), fun1);
        return p;
    }
#pragma endregion
} // namespace drl
#endif



inline BYTE message_class(USHORT mess)
{
    if (mess >= 0x200)
        return EX_MOUSE;
    if (mess < 0x100)
        return EX_WINDOW;
    if (mess == WM_CHAR)
        return EX_CHAR;
    if (mess == WM_KEYDOWN || mess == WM_KEYUP)
        return EX_KEY;
    return 0;
}

#pragma endregion
#endif