#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"
#include "drl_particle/drl_gui_type.hpp"

namespace drl
{
    static const _TSTRING bash_mode[] = {
        _T("bash: paticle_generate_12"),
        _T("bash: paticle_generate_16")};
    static const _TSTRING arg_name[] = {
        _T("RGBA"), _T("TSE"), _T("DC"), _T("AGE"), _T("LIGHT")};
    void bash_analyse(_TSTRING path_in, _TSTRING path_out, bool app)
    {
        using namespace std;
        static _TIFSTREAM fin;
        static _TOFSTREAM fout;
        static _TSTRING tstr1, tstr2, tstr3;
        static int file_mode = _TOFSTREAM::out;
        {
            fin.clear();
            fout.clear();
            tstr1.clear();
            tstr2.clear();
            tstr3.clear();
        }
        if (app)
            file_mode = (_TOFSTREAM::out | _TOFSTREAM::app);
        else
            file_mode = (_TOFSTREAM::out | _TOFSTREAM::trunc);


        fin.open(path_in, _TIFSTREAM::in);
        for (getline(fin, tstr1); (fin) && (!tstr1.size()); getline(fin, tstr1))
            ;
        if (!fin)
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
            for (getline(fin, tstr1); fin; getline(fin, tstr1))
            {
                if (!tstr1.size())
                    continue;
            }
        }
    }
} // namespace drl