#include "basic_par.h"
#include "drl_particle/drl_gui_module.hpp"
#include "drl_particle/drl_gui_signal.hpp"



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
        extern const std::vector<int (*)(const _TSTRING &, const _TSTRING &,
                                         const std::tuple<size_t, _TSTREAMPOS, size_t> &)>
            function_map;
        extern std::map<_TSTRING, matr::paramatr> args_temp;
    } // namespace bash1
    void bash_analyse_begin(const _TSTRING &, const _TSTRING & = bash1::output_file);
    const std::vector<std::tuple<size_t, _TSTREAMPOS, size_t>> &bash_module_devide(const _TSTRING &source_file_path);
    int bash_anaylse_main(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                          const std::vector<std::tuple<size_t, _TSTREAMPOS, size_t>> &main_mess);

    int bash_particle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                      const std::tuple<size_t, _TSTREAMPOS, size_t> &mess);

    int bash_tickparticle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                          const std::tuple<size_t, _TSTREAMPOS, size_t> &mess);

    int bash_musicparticle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                           const std::tuple<size_t, _TSTREAMPOS, size_t> &mess);

    int bash_tickmusicparticle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                               const std::tuple<size_t, _TSTREAMPOS, size_t> &mess);

    int default_arg_set(const _TSTRING &line, matr::paramatr &args);

} // namespace drl

#endif