#include "../include/basic_matr_class.h"
#include "../include/drl_graph/coord.h"
#include <cmath>
#include <conio.h>
#include <limits>
#include <random>
#include <vector>
int main(void)
{
    using plotstyle = drl::plot2_messages::graphstyle_s;
    using std::make_pair;
    using std::vector;
    drl::plot2_messages::graphstyle_s gra = drl::default_graphstyle;
    drl::plot2_messages::range_para ran;
    drl::plot2_messages::image_message mes;
    drl::plot2_messages::act_para act;
    using namespace drl;
    IMAGE p(1920, 1080);
    matrix X(0.0, 21.0, 1.0);
    vector<double> y1{
        0.346, 0.483, 0.390, 0.387, 0.141,
        -0.103, -0.399, -0.640, -0.777, -0.728,
        -0.455, -0.045, -0.022, 0.261, 0.352,
        0.570, 0.434, 0.454, 0.214, -0.099,
        -0.335, -0.630};
    vector<double> y2{-7.527, -7.528, -7.528, -7.528, -7.528, -7.527, -7.174, 3.506, 2.634, 2.205, 2.360, 3.037, 3.659, -7.303, -7.528, -7.528, -7.527, -7.528, -7.528, -7.527, -7.189, 3.478};
    ran.y_minmax = std::pair(-10.0, 10.0);
    ran.ydefaulted = false;
    act.point_ = true;
    gra.linecolor = RED;
    gra.pointcolor = CYAN;
    pict_curve_xy(&p, make_pair(X.begin(), X.end()), make_pair(y1.begin(), y1.end()),
                  gra, ran, mes, act);
    gra.linecolor = BLUE;
    gra.linecolor = YELLOW;
    ran.ydefaulted = false;
    pict_curve_xy(&p, make_pair(X.begin(), X.end()), make_pair(y2.begin(), y2.end()),
                  gra, ran, mes, act, true);

    saveimage(_T("./source/9.png"), &p);
    return 0;
}