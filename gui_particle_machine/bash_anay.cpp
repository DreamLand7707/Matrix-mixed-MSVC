#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"
#include "drl_particle/drl_gui_type.hpp"

namespace drl
{
    namespace bash1
    {
        const _TSTRING bash_part_arg[]{
            _T("RGBA"), _T("TSE"), _T("DC"),
            _T("AGE"), _T("NAME")};
        const _TSTRING bash_sou_arg[]{
            _T("BPM"), _T("FORM"), _T("BLOCK"),
            _T("PITCH"), _T("TONE")};
        const _TSTRING bash_modmode[]{
            _T("partcle"), _T("tickparticle"),
            _T("musicparticle"), _T("tickmusicparticle")};
        const _TSTRING para_last = _T("***");
        const _TSTRING modlabel = _T("label");
        const _TCHAR assign_char = ':';
        const _TSTRING comm_begin_1(_T("//"));
        const _TSTRING unamed_mod(_T("#0"));

        const _TSTRING path_after(_T("source/tempfile/tsf"));
        const _TSTRING output_file(_T("source/output"));
    } // namespace bash1
    void bash_analyse_begin(const _TSTRING &source_file_path, const _TSTRING &target_file_path)
    {
        using namespace std;
        using namespace filesystem;
        filesystem::path path_source(source_file_path),
            path_target(filesystem::current_path() / (bash1::path_after + _T("1.txt")));
        for (auto i : path(bash1::path_after))
        {
            static decltype(i) full(_T(""));
            full /= i;
            create_directory(full);
        }
        copy_file(path_source, path_target);
    }

} // namespace drl