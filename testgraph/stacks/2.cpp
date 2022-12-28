#include <drl_graph/coord.h>
int main(void)
{
    drl::plot2_messages::graphstyle_s gra = drl::darkmode_graphstyle;
    drl::plot2_messages::act_para act = drl::default_act_para;
    drl::plot2_messages::image_message ima;
    drl::plot2_messages::range_para ran = drl::default_range_para;

    using namespace drl;
    using namespace std;
    IMAGE p(1920, 1080);
    ran.xdefaulted = false;
    ran.ydefaulted = false;
    ran.x_ratio = 1;
    ran.y_ratio = 1;
    ran.x_minmax = pair<double, double>(-1, 1);
    ran.y_minmax = pair<double, double>(-1.0, 1.0);
    auto fun1 = [](double x) -> double
    { return 1; };
    auto fun2 = [](double x) -> double
    { return x; };
    auto fun3 = [](double x) -> double
    { return (3 * x * x - 1) / 2.0; };
    auto fun4 = [](double x) -> double
    { return (pow(x, 3) * 5 - 3 * x) / 2.0; };
    auto fun5 = [](double x) -> double
    { return (pow(x, 4) * 35 - pow(x, 2) * 30 + 3) / 8.0; };
    auto fun6 = [](double x) -> double
    { return (pow(x, 5) * 63 - pow(x, 3) * 70 + 15 * x) / 8.0; };
    auto fun7 = [](double x) -> double
    { return (pow(x, 6) * 231 - pow(x, 4) * 315 + pow(x, 2) * 105 - 5) / 16; };
    matrix X(-1.0, 1.0, 1000);
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun1,
                         gra, ran, ima, act);
    gra.linecolor = LIGHTRED;
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun2,
                         gra, ran, ima, act, true);

    gra.linecolor = LIGHTGREEN;
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun3,
                         gra, ran, ima, act, true);
    gra.linecolor = LIGHTMAGENTA;
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun4,
                         gra, ran, ima, act, true);

    gra.linecolor = YELLOW;
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun5,
                         gra, ran, ima, act, true);
    gra.linecolor = WHITE;
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun6,
                         gra, ran, ima, act, true);
    gra.linecolor = LIGHTCYAN;
    drl::pict_curve_xfun(&p,
                         make_pair(X.begin(), X.end()),
                         fun7,
                         gra, ran, ima, act, true);
    saveimage(_T("./source/1.png"), &p);

    return 0;
}