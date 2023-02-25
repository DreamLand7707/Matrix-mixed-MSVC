#include "drl_graph/coord.h"
int main(void) {
    using namespace std;
    using namespace drl;
    plot2_messages::graphstyle_s gra = darkmode_graphstyle;
    plot2_messages::range_para ran = default_range_para;
    plot2_messages::image_message mes = default_image_message;
    plot2_messages::act_para act = default_act_para;

    matrix A(0.0, 100.0, 0.001);
    IMAGE ima(1920, 1080);
    auto fun = [](double a)
    { return (sin(a / 6.28) + 1) * a * (sin(50 * a) + 1); };
    ran.x_ratio = 1;
    ran.y_ratio = 1;
    act.axis = false;
    act.title = false;
    drl::pict_curve_xfun(&ima, pair(A.begin(), A.end()), fun, gra, ran, mes, act);
    saveimage(_T("./source/1.png"), &ima);
    return 0;
}