#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <regex>
#include <string>
#include <numbers>
#include <vector>
using std::cout;
using std::endl;
long double factorial(long double x);
short do_command(std::string &command);
long double calculate(std::string &message, size_t k = 0, size_t y = 0);
struct value_exp
{
    size_t pos;
    size_t stack_pos_l;
    size_t stack_pos_r;
    bool value_aval;
    bool stack_aval_l;
    bool stack_aval_r;
    long double val;
    short kind;
    value_exp(size_t pos_, size_t stack_pos_l_, size_t stack_pos_r_,
              bool value_aval_, bool stack_aval_l_, bool stack_aval_r_, long double val_, short kind_)
        : pos(pos_), stack_pos_l(stack_pos_l_), stack_pos_r(stack_pos_r_), value_aval(value_aval_),
          stack_aval_l(stack_aval_l_), stack_aval_r(stack_aval_r_), val(val_), kind(kind_) {}
};
namespace
{
    const std::map<std::string, std::string> messages{
        {"quit_message",                "#QUIT"                           },
        {"variable_use_error_message",  "undefined variable!"             },
        {"variable_name_error_message", "illegal variable name!"          },
        {"command_use_error_message",   "wrong usage"                     },
        {"command_name_error",          "there is no command"             },
        {"function/Variable wrong",     "wrong function or wrong variable"}
    };
    const std::map<std::string, short> commands{
        {"#SET",  1},
        {"#DEF",  1},
        {"#DEL",  2},
        {"#VAR",  3},
        {"#HELP", 4},
        {"#H",    4},
        {"#FUNS", 5},
        {"#FIX",  6},
        {"#SCI",  7},
        {"#DFU",  8},
        {"#CLS",  9},
        {"#set",  1},
        {"#def",  1},
        {"#del",  2},
        {"#var",  3},
        {"#help", 4},
        {"#h",    4},
        {"#funs", 5},
        {"#fix",  6},
        {"#sci",  7},
        {"#dfu",  8},
        {"#cls",  9},
        {"-SET",  1},
        {"-DEF",  1},
        {"-DEL",  2},
        {"-VAR",  3},
        {"-HELP", 4},
        {"-H",    4},
        {"-FUNS", 5},
        {"-FIX",  6},
        {"-SCI",  7},
        {"-DFU",  8},
        {"-CLS",  9},
        {"-set",  1},
        {"-def",  1},
        {"-del",  2},
        {"-var",  3},
        {"-help", 4},
        {"-h",    4},
        {"-funs", 5},
        {"-fix",  6},
        {"-sci",  7},
        {"-dfu",  8},
        {"-cls",  9}
    };
    static std::vector<value_exp> stack_of_oper;
    static std::vector<long double> stack_of_value;
}
const char command_head = '#';
const char command_head_2 = '-';
std::map<std::string, long double> &variables()
{
    static std::map<std::string, long double> vars{
        {"ans",    0.0l                               },
        {"PI",     std::numbers::pi_v<long double>    },
        {"E",      std::numbers::e_v<long double>     },
        {"EGAMMA", std::numbers::egamma_v<long double>}
    };
    return vars;
}
const std::map<std::string, long double (*)(long double)> &functions()
{
    static const std::map<std::string, long double (*)(long double)> fun{
        {"sin",  std::sin  },
        {"cos",  std::cos  },
        {"tan",  std::tan  },
        {"abs",  std::abs  },
        {"asin", std::asin },
        {"acos", std::acos },
        {"atan", std::atan },
        {"lg",   std::log10},
        {"ln",   std::log  },
        {"log2", std::log2 },
        {"sinh", std::sinh },
        {"cosh", std::cosh },
        {"tanh", std::tanh }
    };
    return fun;
}
int main(void)
{
    std::string message;
    cout << "CALCULATOR V0.4";
    for (unsigned long long i = 0ull; message != messages.at("quit_message"); i++)
    {
        cout << "\n[COM] ";
        std::getline(std::cin, message);
        if (message[0] != command_head && message[0] != command_head_2)
        {
            try
            {
                cout << "answer: " << (variables()["ans"] = calculate(message)) << endl;
            }
            catch (...)
            {
                cout << messages.at("command_use_error_message") << endl;
            }
        }
        else
        {
            do_command(message);
        }
    }
}
long double factorial(long double x)
{
    for (; x > 1;)
        x *= --x;
    return x;
}
long double make_value(const std::string &message)
{
    static const std::regex t(" *((?:-?[0-9]+.?[0-9]*)|(?:-?[0-9]*.[0-9]+)) *");
    static const std::regex d(" *([A-Za-z_]+[A-Za-z_0-9]*) *");
    std::smatch smd;
    try
    {
        if (std::regex_match(message, smd, t))
            return std::stold(smd.str(1));
        else if (std::regex_match(message, smd, d))
            return variables().at(smd.str(1));
        else
            return 0;
    }
    catch (...)
    {
        cout << messages.at("function/Variable wrong") << endl;
        return 0;
    }
}
long double make_value(const std::string &message, size_t pos)
{
    static const std::regex t(" *([A-Za-z0-9_]+)\\$ *");
    std::smatch smd;
    std::regex_match(message, smd, t);
    try
    {
        if (smd.str(1).empty())
            return stack_of_value[pos];
        else
            return functions().at(smd.str(1))(stack_of_value[pos]);
    }
    catch (...)
    {
        cout << messages.at("function/Variable wrong") << endl;
        return 0;
    }
}
long double double_calcu(long double lhs, long double rhs, short way)
{
    if (way == 1)
        return lhs + rhs;
    if (way == 2)
        return lhs - rhs;
    if (way == 4)
        return lhs * rhs;
    if (way == 5)
        return lhs / rhs;
    if (way == 7)
        return std::pow(lhs, rhs);
    return 0;
}
long double min_calculate(std::string &&message, size_t pos)
{
    static size_t temp2;
    temp2 = 0;
    auto N = [](char a) -> char
    {
		if (a == '+')
			return 1;
		if (a == '-')
			return 2;
		if (a == '*')
			return 4;
		if (a == '/')
			return 5;
		if (a == '^')
			return 7;
		else if (a == '$')
			return -1;
		else return 0; };
    size_t pos_st = pos;
    stack_of_oper.clear();
    bool n = false;
    for (size_t i = 0; i < message.size(); i++)
    {
        if (N(message[i]) == -1)
        {
            n = true;
            if (stack_of_oper.size())
                (*(stack_of_oper.end() - 1)).stack_aval_r = true;
            pos_st++;
        }
        if (N(message[i]) > 0)
        {
            stack_of_oper.emplace_back(i, pos_st - n, pos_st, false, n, false, 0, N(message[i]));
            n = false;
            message[i] = ' ';
        }
    }
    long double temp1;
    if (!stack_of_oper.size())
    {
        for (int i = 0; i < message.size(); i++)
            if (message[i] == '$')
            {
                temp2++;
                temp1 = make_value(message, pos);
            }
        if (!temp2)
            temp1 = make_value(message);
    }
    for (size_t i = 0; i < stack_of_oper.size(); i++)
    {
        auto c = std::max_element(stack_of_oper.begin(), stack_of_oper.end(),
                                  [](value_exp lhs, value_exp rhs)
                                  { return lhs.kind < rhs.kind && ((rhs.kind - lhs.kind) > 1); });
        c->value_aval = true;
        if (c + 1 != stack_of_oper.end())
        {
            if ((c + 1)->value_aval == true)
            {
                c->val = (c + 1)->val;
            }
            else if (c->stack_aval_r == true)
            {
                c->val = make_value(std::string(message, c->pos + 1, (c + 1)->pos - c->pos - 1), c->stack_pos_r);
                temp2++;
            }
            else
            {
                c->val = make_value(std::string(message, c->pos + 1, (c + 1)->pos - c->pos - 1));
            }
        }
        else
        {
            if (c->stack_aval_r == true)
            {
                c->val = make_value(std::string(message, c->pos + 1, message.size() - c->pos - 1), c->stack_pos_r);
                temp2++;
            }
            else
                c->val = make_value(std::string(message, c->pos + 1, message.size() - c->pos - 1));
        }
        if (c != stack_of_oper.begin())
        {
            if ((c - 1)->value_aval == true)
            {
                c->val = double_calcu((c - 1)->val, c->val, c->kind);
            }
            else if (c->stack_aval_l == true)
            {
                c->val = double_calcu(
                    make_value(std::string(message, (c - 1)->pos + 1, c->pos - (c - 1)->pos - 1), c->stack_pos_l),
                    c->val, c->kind);
                temp2++;
            }
            else
            {
                c->val = double_calcu(
                    make_value(std::string(message, (c - 1)->pos + 1, c->pos - (c - 1)->pos - 1)), c->val, c->kind);
            }
        }
        else
        {
            if (c->stack_aval_l == true)
            {
                c->val = double_calcu(
                    make_value(std::string(message, 0, c->pos), c->stack_pos_l),
                    c->val, c->kind);
                temp2++;
            }
            else
                c->val = double_calcu(
                    make_value(std::string(message, 0, c->pos)),
                    c->val, c->kind);
        }
        if (i == stack_of_oper.size() - 1)
            temp1 = c->val;
        c->kind = -50;
    }
    if (temp2 >= 1)
    {
        stack_of_value.erase(stack_of_value.begin() + pos + 1, stack_of_value.begin() + pos + temp2);
        stack_of_value[pos] = temp1;
    }
    return temp1;
}
long double calculate(std::string &message, size_t k, size_t y)
{
    stack_of_value.clear();
    size_t j, stack_pos = y;
    for (size_t i = k; i != message.size(); i++)
    {
        if (message[i] == '$')
            stack_pos++;
        if (message[i] == '(')
        {
            size_t temp = 0;
            for (j = i + 1;; j++)
            {
                if (message[j] == '(')
                {
                    i = j;
                    stack_pos += temp;
                    temp = 0;
                }
                if (message[j] == '$')
                    temp++;
                if (message[j] == ')')
                {
                    auto y = min_calculate(
                        std::string(message.begin() + i + 1, message.begin() + j),
                        stack_pos);
                    if (!temp)
                        stack_of_value.push_back(y);
                    message.replace(i, j - i + 1, "  ");
                    message[i] = '$';
                    break;
                }
            }
            i = k - 1;
            stack_pos = y;
        }
    }
    return min_calculate(std::move(message), 0);
}
/*
1. SETV的形式：#SETV <name> <value>
2. DELV的形式：#DELV <name>
*/
short do_command(std::string &command)
{
    std::regex reg_com_head("^(?:#|-)[A-Za-z]+");
    std::smatch smd;
    if (std::regex_search(command, smd, reg_com_head))
    {
        short c;
        try
        {
            c = commands.at(smd.str());
        }
        catch (...)
        {
            cout << messages.at("command_name_error") << endl;
            return -1;
        }
        if (c == 1)
        {
            static const std::regex reg_SETV("(?:#|-)[A-Za-z]+"
                                             " *([A-Za-z_]+[A-Za-z_0-9]*)"
                                             " *((?:-?[0-9]+.?[0-9]*)|(?:-?[0-9]*.[0-9]+))");
            static const std::regex reg_SETV_2("(?:#|-)[A-Za-z]+"
                                               " *([A-Za-z_]+[A-Za-z_0-9]*)"
                                               " *([A-Za-z_]+[A-Za-z_0-9]*)");
            if (std::regex_match(command, smd, reg_SETV))
            {
                try
                {
                    functions().at(smd.str(1))(1.0);
                    cout << messages.at("variable_name_error_message") << endl;
                    return -1;
                }
                catch (...)
                {
                    variables()[smd.str(1)] = std::stold(smd.str(2));
                    return c;
                }
            }
            else if (std::regex_match(command, smd, reg_SETV_2))
            {
                try
                {
                    functions().at(smd.str(1))(1.0);
                    functions().at(smd.str(2))(1.0);
                    cout << messages.at("variable_name_error_message") << endl;
                    return -1;
                }
                catch (...)
                {
                    try
                    {
                        variables()[smd.str(1)] = variables().at(smd.str(2));
                        return c;
                    }
                    catch (...)
                    {
                        cout << messages.at("variable_name_error_message") << endl;
                        return -1;
                    }
                }
            }
            else
            {
                cout << messages.at("command_use_error_message") << endl;
                return -1;
            }
            return c;
        }
        if (c == 2)
        {
            static const std::regex reg_DELV("(?:#|-)[A-Za-z]+"
                                             " *([A-Za-z_]+[A-Za-z_0-9]*)");
            if (std::regex_match(command, smd, reg_DELV))
            {
                try
                {
                    variables().at(smd.str(1));
                    variables().erase(smd.str(1));
                    return c;
                }
                catch (...)
                {
                    cout << messages.at("variable_use_error_message") << endl;
                }
            }
            else
            {
                cout << messages.at("command_use_error_message") << endl;
                return -1;
            }
        }
        if (c == 3)
        {
            cout << "------------------------" << endl;
            cout << "VARS"
                 << "\t\t"
                 << "VALUE" << endl;
            for (auto i = variables().begin(); i != variables().end(); i++)
            {
                cout << i->first << "\t\t" << i->second << endl;
            }
            return c;
        }
        if (c == 4)
        {
            cout << "#SET / -DEF / #set / -def <name> <value> to set a variable" << endl
                 << "#DEL / ... <name> \t\t\t to delete a variable" << endl
                 << "#VAR / ... \t\t\t\t to inquire all variables" << endl
                 << "#HELP & #H / ... \t\t\t to require help document" << endl
                 << "#FUNS / ... \t\t\t\t to inquire all functions" << endl
                 << "#SCI & #FIX & #DFU / ... <PREC> \t to set precision" << endl
                 << "#CLS / ... \t\t\t\t to clear screen" << endl
                 << "#QUIT / ... \t\t\t\t to quit" << endl;
            return c;
        }
        if (c == 5)
        {
            cout << "------------------------" << endl;
            cout << "function table:" << endl;
            for (auto i = functions().begin(); i != functions().end(); i++)
            {
                cout << i->first << endl;
            }
        }
        if (c == 6 || c == 7 || c == 8)
        {
            static const std::regex reg_fcd("(?:#|-)[A-Za-z]+"
                                            " *([0-9]*)");
            std::smatch smd;
            if (std::regex_match(command, smd, reg_fcd))
            {
                if (c == 6)
                    cout.setf(std::ios::fixed, std::ios::floatfield);
                if (c == 7)
                    cout.setf(std::ios::scientific, std::ios::floatfield);
                if (c == 8)
                    cout.unsetf(std::ios::floatfield);
                if (smd.str(1).empty())
                    cout << "The past precision is " << cout.precision(6) << endl;
                else
                    cout << "The past precision is " << cout.precision(stod(smd.str(1))) << endl;
                return c;
            }
            else
            {
                cout << messages.at("command_use_error_message") << endl;
                return -1;
            }
        }
        if (c == 9)
        {
            system("cls");
            cout << "CALCULATOR V0.4";
        }
        return 0;
    }
    else
    {
        cout << messages.at("command_name_error") << endl;
        return -1;
    }
}