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
        const _TSTRING particle_name[3]{
            _T("linear"), _T("dparab"), _T("tparab")};

        const _TSTRING path_after(_T("source/tempfile/tsf"));
        const _TSTRING output_file(_T("source/output"));

        const std::vector<int (*)(const _TSTRING &, const _TSTRING &,
                                  const std::tuple<size_t, _TSTREAMPOS, size_t> &)>
            module_function_map{
                bash_particle,
                bash_tickparticle,
                bash_musicparticle,
                bash_tickmusicparticle};

        const std::map<_TSTRING, int (*)(const _TSTRING &, const _TSTRING &,
                                         const matr::paramatr &, double &)>
            particle_function_map{
                {_T("linear"), linear_anay},
                {_T("dparab"), dparab_anay},
                {_T("tparab"), tparab_anay}};

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
            res += bash1::module_function_map[std::get<0>(i)](source_file_path, target_file_path, i);
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
        /*未完成*/

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
            divide3(_T(R"(\s*\[(.*)\]\s*)")),      // 截取[]内的内容
            module_head(_T(R"(^\$\S+\$$)")),       // 判断是否是模块头，均可
            arg(_T("^") + temp1 + _T("$")),        // 判断是否是参数头，均可
            judge1(_T(R"(^[^,:]+:)"));             // 判断后续跟的是否是继承值，用search
        _TSMATCH match;
        regex_match(temp2, match, divide0);
        temp2 = match[1];
        for (int i = 0; regex_match(temp2, match, divide1); i++)
        {
            temp1 = match[1];
            temp2 = match[2];
            if (i == 0 && regex_match(temp1, module_head))
                if (regex_search(temp2, match, judge1))
                {
                    regex_match(temp2, match, divide2);
                    try
                    {
                        args = bash1::args_temp.at(match[1]);
                    }
                    catch (...)
                    {
                        throw std::invalid_argument("WRONG LABEL\n");
                    }
                }
                else
                    continue;
            else if (regex_match(temp1, match, arg))
            {

                regex_match(temp2, match, divide2);
                temp2 = match[1];
                regex_match(temp2, match, divide3);
                temp2 = match[1];
                _TREGEX tempr(_T(R"(\s+)"));
                _TSREGEX_TOKEN_ITERATOR ber(temp2.begin(), temp2.end(), tempr, -1);
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
                if (temp1 == _T("RGBA"))
                {
                    args[2][1] = stod(*(ber++));
                    args[2][2] = stod(*(ber++));
                    args[2][3] = stod(*(ber++));
                }
                if (temp1 == _T("TSE"))
                {
                    args[0][0] = stod(*(ber++));
                    args[0][1] = stod(*(ber++));
                }
                if (temp1 == _T("DC"))
                {
                    args[0][2] = stod(*(ber++));
                    args[0][3] = stod(*(ber++));
                }
                if (temp1 == _T("AGE"))
                {
                    args[3][0] = stod(*(ber++));
                }
                if (temp1 == _T("NAME"))
                {
                    args.parname((*(ber++)).str().c_str());
                }
            }
            else
                throw std::invalid_argument("WRONG ARG\n");
        }
        return 1;
    }
    double command_sentence(const _TSTRING &command, double &last_time, const _TSTRING &file, const matr::paramatr &args)
    {
        _TREGEX divide0(_T(R"(^\s*(.*?)\s*$)")); // 去前后连续空白字符，均可
        _TSMATCH match;
        _TSTRING tstr;
        double res;
        regex_match(command, match, divide0);
        if (match[1] == _T("{"))
        {
            // 进入并行处理
            return -1;
        }
        else if (match[1] == _T("}"))
        {
            // 跳出并行处理
            return -2;
        }
        else
        {
            // 正常处理
            tstr = match[1];
            _TREGEX judge1(_T(R"((?:\s*(@([0-9]*))\s+)?)") + _TSTRING(_T("(")) + regex_par_name() + _T(")") + _T(R"((?:\s+(@([0-9]*))\s*)?)"));
            _TSMATCH match_t;
            regex_search(tstr, match_t, judge1);
            if (match_t[1].str().size())
            {
                if (match_t[2].str().size())
                {
                    res = stoi(match_t[2].str());
                }
                else
                    res = 0;
            }
            else if (match_t[4].str().size())
            {
                if (match_t[5].str().size())
                {
                    res = last_time + stoi(match_t[5].str());
                }
                else
                    res = last_time;
            }
            else
                res = last_time;

            tstr = match_t.suffix();
            try
            {
                bash1::particle_function_map.at(match_t[3])(file, command, args, last_time);
            }
            catch (...)
            {
                throw std::invalid_argument("WRONG PARTICLE");
            }

            return res;
        }
    }
    int linear_anay(const _TSTRING &file, const _TSTRING &command, const matr::paramatr &args, double &last_time)
    {
        _TREGEX divide0(_T(R"(^\s*(.*?)\s*$)")); // 去前后连续空白字符，均可
        _TSTRING tstr;
        _TSMATCH match;
        regex_match(command, match, divide0);
        tstr = match[1];
        matr::paramatr argst(args);
        drl::matrix points(3, 3);


        O_partmatr outmatr(points, argst);
        last_time = (argst[0][1] - argst[0][0]) / (argst[0][2] * argst[0][3]);
    }
    int dparab_anay(const _TSTRING &file, const _TSTRING &command, const matr::paramatr &args, double &last_time)
    {
        _TREGEX divide0(_T(R"(^\s*(.*?)\s*$)")); // 去前后连续空白字符，均可
        _TSTRING tstr;
        _TSMATCH match;
        regex_match(command, match, divide0);
        tstr = match[1];
        matr::paramatr argst(args);
        drl::matrix points(3, 3);


        O_partmatr outmatr(points, argst);
        last_time = (argst[0][1] - argst[0][0]) / (argst[0][2] * argst[0][3]);
    }
    int tparab_anay(const _TSTRING &file, const _TSTRING &command, const matr::paramatr &args, double &last_time)
    {
        _TREGEX divide0(_T(R"(^\s*(.*?)\s*$)")); // 去前后连续空白字符，均可
        _TSTRING tstr;
        _TSMATCH match;
        regex_match(command, match, divide0);
        tstr = match[1];
        matr::paramatr argst(args);
        drl::matrix points(3, 3);


        O_partmatr outmatr(points, argst);
        last_time = (argst[0][1] - argst[0][0]) / (argst[0][2] * argst[0][3]);
    }

} // namespace drl