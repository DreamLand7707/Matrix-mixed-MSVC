#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"
#include "drl_particle/drl_gui_type.hpp"

namespace drl
{
    static const _TSTRING bash_mode[] = {_T("paticle_generate_12"), _T("paticle_generate_16")};
    void bash_analyse(_TSTRING path_in, _TSTRING path_out)
    {
        using namespace std;
        static _TFSTREAM foutin;
        static _TSTRING tstr1, tstr2, tstr3;
        {
            foutin.clear();
            tstr1.clear();
            tstr2.clear();
            tstr3.clear();
        }
        foutin.open(path_in, _TFSTREAM::in);
        for (getline(foutin, tstr1); (foutin) && (!tstr1.size()); getline(foutin, tstr1))
            ;
        if (!foutin)
            return;
        if (tstr1 == bash_mode[0] || tstr1 == bash_mode[1])
        {
            double rgb[3] = {1, 1, 1};
            double tse[2] = {1, 10};
            double age = 0;
            double dc[2] = {0.1, 10};
            _TSTRING parname;
            if (tstr1 == bash_mode[0])
                parname = _T("endRod");
            else if (tstr1 == bash_mode[1])
                parname = _T("end_rod");
            // after init
            
        }
    }
} // namespace drl