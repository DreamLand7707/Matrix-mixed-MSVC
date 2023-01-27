#include "basic.hpp"

#ifndef BLOCKCHAIN
#define BLOCKCHAIN

struct tran;
struct block
{
    int blockID;
    std::string hash;
    std::string prevhash;
    long timestamp;
    std::vector<tran> trans;                // 使用数组法描述二叉树
    std::map<std::string, double> the_rich; // 在进行交易初始化的时候直接生成富豪榜
};

struct tran
{
    long int txID;
    int blockID;
    std::string addr_in; // 出钱一方
    double amout;
    std::string addr_out; // 得钱一方
};

struct adminer
{
    std::vector<tran *> as_in;
    std::vector<tran *> as_out;
    bool t[8]{};
};

void init_blocks(std::map<int, block> &block_heap, std::vector<block *> &block_time, const std::string &path);


void add_txs(std::map<int, block> &block_heap, std::unordered_map<std::string, adminer> &tx_heap, const std::string &path);


int search_admin_tx(std::string const &admin, std::vector<block *> const &block_time, long time_begin, long time_end,
                    std::vector<tran *> &res_out, std::vector<tran *> &res_in);


double search_admin_value(std::string const &admin, std::vector<block *> const &block_time, long time);


void rich_list(std::vector<block *> const &block_time, std::vector<std::pair<double, std::string>> &admins,
               long time);


void simple_statistics(double &aver_in, double &aver_out,
                       std::vector<std::pair<int, const std::string *>> &in_admins,
                       std::vector<std::pair<int, const std::string *>> &out_admins,
                       std::unordered_map<std::string, adminer> &tx_heap, size_t k);


bool have_circle(std::unordered_map<std::string, adminer> &tx_heap);


void DFSD(adminer &i, std::unordered_map<std::string, adminer> &tx_heap, bool &res);

void make_path(const std::string &begin_node, std::unordered_map<std::string, adminer> &tx_heap,
               std::map<std::string, double> &all_path);

#endif