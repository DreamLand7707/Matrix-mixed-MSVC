#include "drl_particle/drl_bash_anay.hpp"

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

        const std::vector<int (*)(const _TSTRING &, const _TSTRING &,
                                  const std::tuple<size_t, _TSTREAMPOS, size_t> &)>
            function_map{
                bash_particle,
                bash_tickparticle,
                bash_musicparticle,
                bash_tickmusicparticle};
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
    const std::vector<std::tuple<size_t, _TSTREAMPOS, size_t>> &bash_module_devide(const _TSTRING &source_file_path)
    {
        using std::getline;
        static std::vector<std::tuple<size_t, _TSTREAMPOS, size_t>> res;
        static _TIFSTREAM fin;
        static _TSTRING strt1;
        static _TREGEX use(_T("^\\$(?:tick)?(?:music)?particle\\$"));
        static _TSMATCH match;
        int p = 0, t = 0;
        _TSTREAMPOS last_pos;
        auto find_mode = [&](const _TSTRING &tar) -> int
        {
            for (int i = 0; i < 4; i++)
                if (tar == bash1::bash_modmode[i])
                    return i;
            return -1;
        };
        strt1.clear();
        res.clear();
        fin.clear();
        fin.open(source_file_path, std::ios::in);
        last_pos = fin.tellg();

        for (getline(fin, strt1); fin; getline(fin, strt1))
        {
            if (std::regex_match(strt1, match, use))
            {
                t = find_mode(match[0]);
                if (t == -1)
                    throw std::invalid_argument(std::string("Line ") + std::to_string(p) + std::string(":WRONG MODULE MODE!"));
                if (res.size())
                {
                    std::get<2>(res.back()) = p;
                    p = 0;
                }
                res.push_back({t, last_pos, 0});
            }
            last_pos = fin.tellg();
            p++;
        }
        std::get<2>(res.back()) = p;
        return res;
    }
    int bash_anaylse_main(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                          const std::vector<std::tuple<size_t, _TSTREAMPOS, size_t>> &main_mess)
    {
        int res = 0;
        for (auto i : main_mess)
        {
            res += bash1::function_map[std::get<0>(i)](source_file_path, target_file_path, i);
        }
        return res;
    }
    int bash_particle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                      const std::tuple<size_t, _TSTREAMPOS, size_t> &mess)
    {
        ;
    }
    int bash_tickparticle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                          const std::tuple<size_t, _TSTREAMPOS, size_t> &mess)
    {
        ;
    }
    int bash_musicparticle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                           const std::tuple<size_t, _TSTREAMPOS, size_t> &mess)
    {
        ;
    }
    int bash_tickmusicparticle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                               const std::tuple<size_t, _TSTREAMPOS, size_t> &mess)
    {
        ;
    }

} // namespace drl