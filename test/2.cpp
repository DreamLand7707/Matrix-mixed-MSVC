#include "blockchain/blockchain.hpp"

void init_blocks(std::map<int, block> &block_heap, std::vector<block *> &block_time, const std::string &path)
{
    using namespace std;
    block_heap.clear();
    block_time.clear();
    ifstream fin(path, std::ios::in);
    if (!fin)
    {
        throw std::invalid_argument("Can't open file!");
    }
    stringstream strin;
    std::string tstr, tstr1, tstr2;
    int t1;
    getline(fin, tstr);
    for (getline(fin, tstr); fin; getline(fin, tstr))
    {
        strin.str(tstr);
        strin.clear();
        getline(strin, tstr1, ',');
        t1 = std::stoi(tstr1);
        block_heap[t1].blockID = t1;
        block_heap[t1].prevhash = tstr2;
        getline(strin, tstr1, ',');
        tstr2 = block_heap[t1].hash = tstr1;
        getline(strin, tstr1, ',');
        block_heap[t1].timestamp = std::stol(tstr1);
        block_time.push_back(&block_heap[t1]);
    }
    std::sort(block_time.begin(), block_time.end(),
              [](const block *const &lhs, const block *const &rhs) -> bool
              { return lhs->timestamp < rhs->timestamp; }); // 用timestamp为基，对所有block排序
}

void add_txs(std::map<int, block> &block_heap, std::unordered_map<std::string, adminer> &tx_heap, const std::string &path)
{
    using namespace std;
    ifstream fin(path, std::ios::in);
    if (!fin)
    {
        throw std::invalid_argument("Can't open file!");
    }
    stringstream strin;
    std::string tstr, tstr1, tstr2, tstr3;
    int t1, t2;
    getline(fin, tstr);
    for (getline(fin, tstr); fin; getline(fin, tstr))
    {
        strin.str(tstr);
        strin.clear();
        getline(strin, tstr1, ',');
        t1 = stol(tstr1);
        getline(strin, tstr1, ',');
        t2 = stoi(tstr1);
        block_heap[t2].trans.push_back({t1, t2});
        getline(strin, tstr1, ',');
        block_heap[t2].trans.back().addr_in = tstr1;
        getline(strin, tstr2, ',');
        block_heap[t2].trans.back().amout = stod(tstr2);
        getline(strin, tstr3, ',');
        block_heap[t2].trans.back().addr_out = tstr3;
        block_heap[t2].the_rich[tstr1] -= block_heap[t2].trans.back().amout; // 转入的加，转出的减
        block_heap[t2].the_rich[tstr3] += block_heap[t2].trans.back().amout;
        tx_heap[tstr1].as_in.push_back(&block_heap[t2].trans.back());
        tx_heap[tstr3].as_out.push_back(&block_heap[t2].trans.back());
    }
}

int search_admin_tx(std::string const &admin, std::vector<block *> const &block_time, long time_begin, long time_end,
                    std::vector<tran *> &res_out, std::vector<tran *> &res_in)
{
    size_t n = block_time.size();
    res_out.clear();
    res_in.clear();
    int res = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (block_time[i]->timestamp >= time_begin && block_time[i]->timestamp <= time_end)
        {
            for (auto &i : block_time[i]->trans)
            {
                if (admin == i.addr_in)
                { // 转出的记录
                    res++;
                    res_out.push_back(&i);
                }
                if (admin == i.addr_out)
                { // 转入的记录
                    res++;
                    res_in.push_back(&i);
                }
            }
        }
    }
    std::sort(res_out.begin(), res_out.end(),
              [](tran *&l, tran *&r)
              { return l->amout > r->amout; });
    std::sort(res_in.begin(), res_in.end(),
              [](tran *&l, tran *&r)
              { return l->amout > r->amout; });
    return res;
}

double search_admin_value(std::string const &admin, std::vector<block *> const &block_time, long time)
{
    double res = 0;
    size_t n = block_time.size();
    for (size_t i = 0; i < n; i++)
    {
        if (block_time[i]->timestamp <= time)
        {
            try
            {
                res += block_time[i]->the_rich.at(admin);
            }
            catch (...)
            {
                continue;
            }
        }
        else
            break;
    }
    return res;
}

void rich_list(std::vector<block *> const &block_time, std::vector<std::pair<double, std::string>> &admins,
               long time)
{
    using namespace std;
    admins.clear();
    std::map<std::string, double> trich;
    size_t n = block_time.size();
    for (size_t i = 0; i < n; i++)
    {
        if (block_time[i]->timestamp <= time)
        {
            for (auto &i : block_time[i]->the_rich)
            {
                trich[i.first] += i.second;
            }
        }
    }
    for (auto &i : trich)
    {
        admins.push_back({i.second, i.first});
    }
    std::sort(admins.begin(), admins.end(),
              [](const std::pair<double, std::string> &lhs, const std::pair<double, std::string> &rhs)
              { return lhs.first > rhs.first; });
}

void simple_statistics(double &aver_in, double &aver_out,
                       std::vector<std::pair<int, const std::string *>> &in_admins,
                       std::vector<std::pair<int, const std::string *>> &out_admins,
                       std::unordered_map<std::string, adminer> &tx_heap, size_t k)
{
    aver_in = aver_out = 0;
    in_admins.clear();
    out_admins.clear();
    size_t l = 0;
    for (auto i = tx_heap.begin(); i != tx_heap.end(); i++, l++)
    {
        aver_in += i->second.as_out.size();
        aver_out += i->second.as_in.size();
        in_admins.push_back({i->second.as_out.size(), &(i->first)});
        out_admins.push_back({i->second.as_in.size(), &(i->first)});
        if (l == k)
        {
            l = 0;
            std::sort(in_admins.begin(), in_admins.end(),
                      [](const std::pair<int, const std::string *> &lhs, const std::pair<int, const std::string *> &rhs)
                      { return lhs.first > rhs.first; });
            std::sort(out_admins.begin(), out_admins.end(),
                      [](const std::pair<int, const std::string *> &lhs, const std::pair<int, const std::string *> &rhs)
                      { return lhs.first > rhs.first; });
            in_admins.resize(k);
            out_admins.resize(k);
        }
    }
    aver_in /= tx_heap.size();
    aver_out /= tx_heap.size();
}


bool have_circle(std::unordered_map<std::string, adminer> &tx_heap)
{
    bool res = false;
    for (auto i = tx_heap.begin(); i != tx_heap.end(); i++)
    {
        if (res)
            return true;
        if (i->second.t[1] == false)
        {
            DFSD(i->second, tx_heap, res);
        }
    }
    for (auto &i : tx_heap)
    {
        i.second.t[0] = i.second.t[1] = false;
    }
    return false;
}

void DFSD(adminer &i, std::unordered_map<std::string, adminer> &tx_heap, bool &res)
{
    if (i.t[0])
        res = true;
    if (res)
        return;
    i.t[0] = true;
    i.t[1] = true;
    for (auto t : i.as_in)
    {
        DFSD(tx_heap[t->addr_out], tx_heap, res);
    }
    i.t[0] = false;
}

void make_path(const std::string &begin_node, std::unordered_map<std::string, adminer> &tx_heap,
               std::map<std::string, double> &all_path)
{
    std::deque<std::pair<double, size_t>> qu0;
    std::deque<std::pair<std::string, tran *>> qu1;
    size_t t1 = 0;
    all_path.clear();
    tx_heap.at(begin_node).t[0] = true;
    for (auto &i : tx_heap[begin_node].as_in)
    {
        qu1.push_back({i->addr_out, i});
        tx_heap[i->addr_out].t[0] = true;
        t1++;
    }
    qu0.push_back({0.0, t1});
    std::pair<std::string, tran *> t;
    while (qu1.size())
    {
        t1 = 0;
        t = qu1.front();
        qu1.pop_front();
        qu0.front().second--;
        if (all_path[t.first] > t.second->amout + qu0.front().first)
            all_path[t.first] = t.second->amout + qu0.front().first;
        for (auto &i : tx_heap[t.first].as_in)
        {
            if (tx_heap[i->addr_out].t[0])
                continue;
            t1++;
            qu1.push_back({i->addr_out, i});
            tx_heap[i->addr_out].t[0] = true;
        }
        qu0.push_front({qu0.front().first + t.second->amout, t1});
        if (qu0.front().second == 0)
            qu0.pop_front();
    }
    for (auto &i : tx_heap)
        i.second.t[0] = false;
}