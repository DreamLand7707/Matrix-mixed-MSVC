#include "../include/drl_graph/coord.h"
#include <vector>
double ln(double x)
{
    return log(x) / log(exp(1));
}
typedef drl::plot2_messages::graphstyle_s lpstyle;
int main(void)
{
    std::vector<double> x{242.0, 290.0, 340.0, 363.0, 430.0,
                          450.0, 500.0, 390.0, 450.0, 500.0,
                          475.0, 500.0, 500.0, 340.0, 600.0,
                          600.0, 700.0, 700.0, 610.0, 650.0,
                          575.0, 685.0, 620.0, 680.0, 700.0};
    std::vector<double> y{23.2, 24.0, 23.9, 26.3, 26.5,
                          26.8, 26.8, 27.6, 27.6, 28.5,
                          28.4, 28.7, 29.1, 29.5, 29.4,
                          29.4, 30.4, 30.4, 30.9, 31.0,
                          31.3, 31.4, 31.5, 31.8, 31.9};
    drl::plot2_messages::graphstyle_s gra = drl::darkmode_graphstyle;
    drl::plot2_messages::act_para act;
    drl::plot2_messages::image_message ima;
    drl::plot2_messages::range_para ran;
    gra.pointstyle = lpstyle::pointstyle_::TRIA;
    gra.point_line_width = 2;
    gra.pointsize = 8;
    gra.linewidth /= 2;
    // gra.pointsize = gra.pointsize;
    // act.draw_line_ = false;
    IMAGE p(2560, 1600);
    // ran.x_ratio = 2;
    std::vector<double> x_d(x.size()), y_d(y.size());
    drl::pict_curve_xy(&p,
                       make_pair(x.begin(), x.end()),
                       make_pair(y.begin(), y.end()),
                       gra, ran, ima, act);
    saveimage(_T("./source/3_1.png"), &p);
    drl::element_xy_sort_copy(std::make_pair(x.begin(), x.end()),
                              std::make_pair(y.begin(), y.end()),
                              x_d.begin(), y_d.begin());
    gra.pointcolor = LIGHTRED;
    gra.linecolor = LIGHTMAGENTA;
    // act.point_ = false;
    drl::pict_curve_xy(&p,
                       make_pair(x_d.begin(), x_d.end()),
                       make_pair(y_d.begin(), y_d.end()),
                       gra, ran, ima, act, false);

    saveimage(_T("./source/3_2.png"), &p);
    return 0;
    auto line_para = drl::least_square(
        make_pair(x_d.begin(), x_d.end()), make_pair(y_d.begin(), y_d.end()),
        [](double e)
        { return ln(e); },
        [](double e)
        { return ln(e); });
    auto fun1 = [](double x, auto line_para) -> double
    {
        return pow(x, line_para.first.first) * exp(line_para.first.second);
    };
    auto fun2 = std::bind(fun1, std::placeholders::_1, line_para);

    {
        drl::matrix x_(242.0, 700.0, 1.0);
        act.draw_line_ = true;
        act.point_ = false;
        gra.linecolor = LIGHTRED;
        drl::pict_curve_xfun(&p,
                             make_pair(x_.begin(), x_.end()),
                             fun2,
                             gra, ran, ima, act, true);
        TCHAR R[60];
        _stprintf(R, _T("y = %.4f * x^%.4f -> R = %.4f"), exp(line_para.first.second), line_para.first.first, line_para.second);
        SetWorkingImage(&p);
        settextstyle(70, 0, _T("小考拉体"));
        settextcolor(LIGHTRED);
        outtextxy(0, 0, R);
        saveimage(_T("./source/3.png"), &p);
        return 0;
    }
}