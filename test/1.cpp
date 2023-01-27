#include "blockchain/blockchain.hpp"
int main(void)
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::map;
    using std::set;
    using std::string;
    using std::unordered_map;
    using std::vector;

    map<string, int> command_set{
        {"init", 0},
        {"balance", 1},
        {"rich man", 2},
        {"graph info", 3},
        {"help", 4},
        {"add file", 5},
        {"quit", 6}};
    map<string, int> balance_set{
        {"record", 10}, {"sum", 11}};
    map<string, int> graph_set{
        {"inout", 30},
        {"circle", 31},
        {"from", 32}};
    std::regex is_number("^\\+?[1-9]\\d*$");
    string command, tstr1, tstr2, tstr3, tstr4, tstr5;
    std::map<int, block> block_heap;
    std::vector<block *> block_time;
    std::vector<std::pair<double, std::string>> admins;
    std::vector<std::pair<int, const std::string *>> in_admins;
    std::vector<std::pair<int, const std::string *>> out_admins;
    std::unordered_map<std::string, adminer> tx_heap;
    std::map<std::string, double> all_path;
    std::vector<tran *> res_out;
    std::vector<tran *> res_in;
    int t1, t2, t3;
    double dt1, dt2, dt3;
    bool inited = false;
    clock_t begin;
    for (;;)
    {
        begin = clock();
        cout << "[COMMAND] " << endl;
        getline(cin, command);
        try
        {
            t1 = command_set.at(command);
        }
        catch (...)
        {
            cout << "Wrong command! Please putin again." << endl;
        }
        if (t1 == 0)
        {
            if (inited)
                cout << "[system:]You've already done that" << endl;
            cout << "[system:]please putin the file of block" << endl;
            getline(cin, tstr1);
            try
            {
                init_blocks(block_heap, block_time, tstr1);
                inited = true;
            }
            catch (std::exception &t)
            {
                cout << t.what() << endl;
            }
            cout << "[system:]please putin the file of txs" << endl;
            getline(cin, tstr1);
            try
            {
                add_txs(block_heap, tx_heap, tstr1);
                inited = true;
            }
            catch (std::exception &t)
            {
                cout << t.what() << endl;
                cout << "Or just the end" << endl;
            }
            cout << "[TIME]:" << double(clock() - begin) / CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (t1 == 1)
        {
            cout << "\t[system:]Please putin \"record\" or \"sum\"" << endl;
            while (1)
            {
                cout << "\t";
                getline(cin, tstr2);
                try
                {
                    t2 = balance_set.at(tstr2);
                }
                catch (std::exception &t)
                {
                    cout << "Wrong command! Please putin again." << endl;
                    continue;
                }
                if (t2 == 10)
                {
                    cout << "\t[system:]:please putin the name of admin and a time period with"
                            " the number of items you want to observe"
                         << endl;
                    while (1)
                    {
                        cout << "\t";
                        getline(cin, tstr2);
                        std::stringstream ssin(tstr2);
                        ssin >> tstr1;
                        ssin >> tstr3;
                        ssin >> tstr4;
                        ssin >> tstr5;
                        if (std::regex_match(tstr3, is_number) &&
                            std::regex_match(tstr4, is_number) &&
                            std::regex_match(tstr5, is_number))
                        {
                            t3 = search_admin_tx(tstr2, block_time, std::stol(tstr3), std::stol(tstr4), res_out, res_in);
                        }
                        else
                        {
                            cout << "\tInvalid input, please putin again" << endl;
                            continue;
                        }
                        {
                            cout << "***************************************" << endl;
                            cout << "The admin named " << tstr1 << endl;
                            cout << "From " << std::stol(tstr3) << " To " << std::stol(tstr4) << endl;
                            cout << "Total number of transactions is: " << t3 << endl;
                            cout << "The transaction of expenditure " << res_out.size() << endl;
                            cout << "Trading of revenues " << res_out.size() << endl;
                            t1 = std::stoi(tstr5);
                            cout << "The top " << t1 << " trades with the largest trading volume:" << endl;
                            t2 = 0;
                            t3 = 0;
                            tran *ttr;
                            for (int i = 0; i < t1; i++)
                            {
                                if (t2 != res_out.size() && res_out[t2]->amout > res_in[t3]->amout)
                                {
                                    ttr = res_out[t2++];
                                }
                                else if (t3 != res_out.size())
                                {
                                    ttr = res_out[t3++];
                                }
                                else
                                    break;
                                cout << "The transaction " << i + 1 << endl;
                                cout << "---------------" << endl;
                                cout << "The transaction blockid " << ttr->blockID << endl;
                                cout << "The transaction id " << ttr->txID << endl;
                                cout << "The transaction amount " << ttr->amout << endl;
                                cout << "The transaction from " << ttr->addr_in << endl;
                                cout << "The transaction to " << ttr->addr_out << endl;
                                cout << "---------------" << endl;
                            }
                            cout << "***************************************" << endl;
                        }
                        break;
                    }
                }
                else if (t2 == 11)
                {
                    cout << "\t[system:]:please putin the name of admin and a time" << endl;
                    while (1)
                    {
                        cout << "\t";
                        getline(cin, tstr2);
                        std::stringstream ssin(tstr2);
                        ssin >> tstr1;
                        ssin >> tstr3;
                        if (!std::regex_match(tstr3, is_number))
                        {
                            cout << "\tInvalid input, please putin again" << endl;
                            continue;
                        }
                        {
                            t3 = std::stol(tstr3);
                            cout << "***************************************" << endl;
                            cout << "The admin named " << tstr1 << endl;
                            cout << "The amount at moment " << t3 << " is "
                                 << search_admin_value(tstr1, block_time, t3) << endl;
                            cout << "***************************************" << endl;
                        }
                        break;
                    }
                }
                break;
            }
            cout << "[TIME]:" << double(clock() - begin) / CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (t1 == 2)
        {
            t2 = 50;
            cout << "Please putin the num of items you want,the default value is 50" << endl;
            while (1)
            {
                getline(cin, tstr1);
                std::stringstream ssin(tstr1);
                ssin >> tstr2;
                ssin >> tstr3;
                if (std::regex_match(tstr2, is_number))
                {
                    t2 = std::stoi(tstr2);
                }
                if (std::regex_match(tstr3, is_number))
                {
                    t3 = std::stoi(tstr3);
                }
                else
                {
                    continue;
                }
                rich_list(block_time, admins, t3);
                cout << "***************************************" << endl;
                for (int i = 0; i < t3 && i < admins.size(); i++)
                {
                    cout << '[' << i + 1 << ']' << admins[i].second << " " << admins[i].first << endl;
                }
                cout << "***************************************" << endl;
                break;
            }
            cout << "[TIME]:" << double(clock() - begin) / CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (t1 == 3)
        {
            cout << "\t[system:]Please putin \"inout\" or \"circle\" or \"from\"" << endl;
            while (1)
            {
                cout << "\t";
                getline(cin, tstr2);
                try
                {
                    t2 = graph_set.at(tstr2);
                }
                catch (std::exception &t)
                {
                    cout << "Wrong command! Please putin again." << endl;
                    continue;
                }
                if (t2 == 30)
                { // 统计交易关系图的平均出度、入度。显示出度 / 入度最高的前k个帐号。
                    cout << "\tPlease enter the number of entries you want to watch" << endl;
                    while (1)
                    {
                        cout << '\t';
                        getline(cin, tstr2);
                        if (regex_match(tstr2, is_number))
                        {
                            t2 = std::stoi(tstr2);
                        }
                        else
                        {
                            cout << "\tInvalid number, Please putin again." << endl;
                            continue;
                        }
                        simple_statistics(dt1, dt2, in_admins, out_admins, tx_heap, t2);
                        cout << "***************************************" << endl;
                        cout << "The average out-degree is " << dt2 << endl;
                        cout << "The average in-degree is " << dt1 << endl;
                        cout << "----------" << endl;
                        cout << "Top " << t2 << " accounts with the highest outbound degree:" << endl;
                        for (auto &i : out_admins)
                        {
                            cout << *(i.second) << endl;
                        }
                        cout << "Top " << t2 << " accounts with the highest inbound degree:" << endl;
                        for (auto &i : in_admins)
                        {
                            cout << *(i.second) << endl;
                        }
                        cout << "----------" << endl;
                        cout << "***************************************" << endl;
                        break;
                    }
                }
                else if (t2 == 31)
                {
                    cout << "***************************************" << endl;
                    cout.setf(std::ios::boolalpha);
                    cout << "\tCirlce: " << have_circle(tx_heap) << endl;
                    cout << "***************************************" << endl;
                }
                else if (t2 == 32)
                {
                    cout << "\tPlease enter the admin of entries you want to watch" << endl;
                    while (1)
                    {
                        cout << '\t';
                        getline(cin, tstr2);
                        try
                        {
                            make_path(tstr2, tx_heap, all_path);
                        }
                        catch (std::exception &t)
                        {
                            cout << t.what() << endl;
                            continue;
                        }
                        cout << "***************************************" << endl;
                        cout << "From " << tstr2 << endl;
                        for (auto &i : all_path)
                        {
                            cout << "To " << i.first << " amount:" << i.second << endl;
                        }
                        cout << "***************************************" << endl;
                        break;
                    }
                }
                break;
            }
            cout << "[TIME]:" << double(clock() - begin) / CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (t1 == 4)
        {
            cout << "[HELP FILE]:" << endl;
            cout << "USE init to init block chain, but you can only do it once" << endl;
            cout << "USE balance to do sth. with account" << endl;
            cout << "\t then USE record to view records" << endl;
            cout << "\t or USE sum to view aggregate amount" << endl;
            cout << "[TIME]:" << double(clock() - begin) / CLOCKS_PER_SEC << " seconds" << endl;
        }
        else if (t1 == 5)
        {
            cout << "[system:]please putin the file of txs" << endl;
            getline(cin, tstr1);
            try
            {
                add_txs(block_heap, tx_heap, tstr1);
                inited = true;
            }
            catch (std::exception &t)
            {
                cout << t.what() << endl;
                cout << "Or just the end" << endl;
            }
            cout << "[TIME]:" << double(clock() - begin) / CLOCKS_PER_SEC << " seconds" << endl;
        }
        else
            break;
    }
    return 0;
}