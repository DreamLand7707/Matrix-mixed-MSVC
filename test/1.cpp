#include "../include/drl_graph/coord.h"
#include "basic_matr_class.h"
#include <cmath>

int main(void)
{
    using drl::matrix;
    double pi = 3.1415926;
    matrix A(0.0, 4 * pi, 1000);
    matrix B(1, 1000);
    for (int i = 0; i < 1000; i++)
    {
        B[0][i] = sin(2 * A[0][i]) + cos(3 * A[0][i]) + sin(4 * A[0][i]) + cos(5 * A[0][i]);
    }
    drl::plot2_messages::graphstyle_s gra = drl::default_graphstyle;
    drl::plot2_messages::range_para ran = drl::default_range_para;
    drl::plot2_messages::image_message ima(_T("x-coord"), _T("y-coord"), _T("FUNCTION: y=sin(2x)+cos(3x)+sin(4x)+cos(5x)"));
    drl::plot2_messages::act_para act = drl::default_act_para;
    IMAGE p(1920, 1080);
    ran.x_ratio = 1;
    act.point_ = true;
    gra.point_density = 25;
    gra.point_line_width *= 2;
    gra.pointsize *= 2;
    gra.pointstyle = drl::plot2_messages::graphstyle_s::pointstyle_::Nazi;
    drl::pict_curve_xy(&p, std::make_pair(A.begin(), A.end()), std::make_pair(B.begin(), B.end()),
                       gra, ran, ima, act);
    saveimage(_T("./source/2.png"), &p);
    return 0;
}