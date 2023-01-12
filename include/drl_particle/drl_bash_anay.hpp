#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"
#include "drl_particle/drl_gui_type.hpp"


#ifndef DRL_BASH_ANAY
#define DRL_BASH_ANAY 1

namespace drl
{
    namespace bash1
    {
        extern const _TSTRING bash_part_arg[];
        extern const _TSTRING bash_sou_arg[];
        extern const _TSTRING bash_modmode[];
        extern const _TSTRING para_last;
        extern const _TSTRING modlabel;
        extern const _TCHAR assign_char;
        extern const _TSTRING comm_begin_1;
        extern const _TSTRING unamed_mod;
        extern const _TSTRING path_after;
        extern const _TSTRING output_file;
    } // namespace bash1
    void bash_analyse_begin(const _TSTRING &, const _TSTRING & = bash1::output_file);
} // namespace drl

#endif