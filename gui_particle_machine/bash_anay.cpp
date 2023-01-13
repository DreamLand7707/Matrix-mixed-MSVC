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

        std::map<_TSTRING, matr::paramatr> args_temp;
        double game_ver = 1165;
    } // namespace bash1
    void bash_analyse_begin(const _TSTRING &source_file_path, const _TSTRING &target_file_path)
    {
        using namespace std;
        using namespace filesystem;
        bash1::args_temp.clear();
        filesystem::path path_source(source_file_path),
            path_target(filesystem::current_path() / (bash1::path_after + _T("1.txt")));
        for (auto i : path(bash1::path_after))
        {
            static decltype(i) full(_T(""));
            full /= i;
            create_directory(full);
        }
        copy_file(path_source, path_target);
        bash_anaylse_main(source_file_path, target_file_path, bash_module_devide(source_file_path));
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
        fin.close();
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
    /*
        & 用于存储标准参数
        ^ t_start(d)          t_end(d)          CPT(i)             delta(d)
        ? 起始参数             结束参数           每tick计算次数      计算间隔
        ^ CPerf(i)            Tolf(i)           time(d)            direct(b)
        ? .每个file的指令数目   .一共有的文件数目    .完全生成的时间     生成方向(true代表t_start -> t_end,false为反)
        ^ Ver(i)              R(d)               G(d)               B(d)
        ? 游戏版本             红                绿                  蓝
        ^life(d)             light(i)          instant(b)         mode(i) ?
        粒子寿命             发光              是否瞬间生成           模式(colorblock:0,文件:1,混合:2)
    */
    int bash_particle(const _TSTRING &source_file_path, const _TSTRING &target_file_path,
                      const std::tuple<size_t, _TSTREAMPOS, size_t> &mess)
    {
        static _TIFSTREAM fin;
        static _TOFSTREAM fout;
        _TSTRING tstr1;
        _TSTRING label;
        matr::paramatr matrarg;
        if (bash1::game_ver == 1165.0)
            matrarg = matr::empty_paramatr_1165;
        else
            matrarg = matr::empty_paramatr;
        drl::matrix pointcor(3, 3);
        fin.clear();
        fout.clear();
        fin.open(source_file_path);
        fin.seekg(std::get<1>(mess));
        _TSTRINGSTREAM &ssin = public_tstream();
        for (size_t i = 0; i < std::get<2>(mess); i++)
        {
            std::getline(fin, tstr1);
            ssin.clear();
            ssin.str(tstr1);
        }

        fin.close();
        fout.close();
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
    int default_arg_set(const _TSTRING &line, matr::paramatr &args)
    {
        _TSTRING temp1, temp2(line);
        for (auto i : bash1::bash_part_arg)
            temp1 += (i + _T("|"));
        for (auto i : bash1::bash_sou_arg)
            temp1 += (i + _T("|"));
        temp1.pop_back();
        _TREGEX divide0(_T(R"(^\s*(.*?)\s*$)")),   // 去前后连续空白字符，均可
            divide1(_T(R"(^(\S+?)\s*:\s*(.+)$)")), // 根据:分前后，均可
            divide2(_T(R"(^(\S+?)\s*,\s*(.+)$)")), // 根据,分前后，均可
            module_head(_T(R"(^\$\S+\$$)")),       // 判断是否是模块头，均可
            arg(_T("^") + temp1 + _T("$")),        // 判断是否是参数头，均可
            judge1(_T(R"(^[^,:]+:)"));             // 判断后续跟的是否是继承值，用search
        _TSMATCH match;
        regex_match(temp2, match, divide0);
        temp2 = match[1];
        for (; regex_match(temp2, match, divide1);)
        {
            temp1 = match[0];
            temp2 = match[1];
            regex_match(temp2, match, divide2);
            temp2 = match[0];
            if (regex_match(temp1, module_head))
            {
            }
            else if (regex_match(temp1, arg))
            {
            }
            else
                return -1;
        }
    }

} // namespace drl