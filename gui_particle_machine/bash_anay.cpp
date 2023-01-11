#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"
#include "drl_particle/drl_gui_type.hpp"

namespace drl
{
    namespace bash1
    {
        const _TSTRING bash_para[]{
            _T("RGBA"), _T("TSE"), _T("DC"),
            _T("AGE"), _T("NAME")};
        const _TSTRING bash_modmode[]{
            _T("partcle"), _T("tickparticle"), _T("musicparticle"), _T("tickmusicparticle")};
        const _TSTRING para_last = _T("***");
        const _TSTRING modlabel = _T("label");
        const _TCHAR assign_char = ':';
        const _TSTRING comm_begin_1(_T("//"));
        const _TSTRING unamed_mod(_T("#mod"));
    } // namespace bash1
    void bash_analyse_begin(const _TSTRING &file_path)
    {
        
    }

} // namespace drl