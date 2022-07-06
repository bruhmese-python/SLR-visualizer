#ifndef SLR_UTILS
#define SLR_UTILS
#pragma once
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include "slrtree.cpp"

namespace utils
{
    std::vector<std::string> augmentize(std::string p); // returns augmented grammar from given productions
    bool has_dot(std::string p);                        // returns whether the given std::string has delimiter '.'
    bool not_in(PRODTS P, PRODT _p);                    // checks whether the given production is not related to the given grammar
    class json;                                         // json class

};
class utils::json
{
    slrtree::node *root;
    static int i_name;
    STATE_MAP s_map, t_map;
    const std::string _begin_ = "{chart:{container:\"#OrganiseChart-simple\"},nodeStructure:{";
    const std::string _end_ = "}};";

public:
    std::string JSON{"", 0};
    std::string enclose(const std::string &s) { return "{" + s + "}"; }
    std::string text(const std::string &s) { return "text:{" + s + "}"; }
    std::string name(const std::string &s) { return std::to_string(utils::json::i_name++) + ":\"" + s + "\""; }
    std::string state(const std::string &s) { return "state_name:\"" + s + "\""; }
    std::string children(const std::string &s) { return "children:[" + s + "]"; }
    std::string get_prodt(const PRODT &_p) { return (std::string(1, _p.first) + "->" + _p.second); }

    std::string substructure(slrtree::node &_n); // recursive 'children to json' conversion
    json(slrtree::node &_n, STATE_MAP &s_m);     // constructor
};
int utils::json::i_name = 0;

utils::json::json(slrtree::node &_n, STATE_MAP &s_m)
{
    this->root = &_n;
    this->s_map = s_m;
    std::string s_json, c_json, r_li;

    s_json.append(_begin_);

    for (const auto &p_n : _n.subproductions)
        r_li.append(name(get_prodt(p_n)) + ",");
    s_json.append(text(r_li + state(s_map[condense(_n.subproductions)])) + ",");

    for (const auto &[f, s] : _n.states)
        c_json += substructure(*s) + ",";
    s_json.append(children(c_json));
    s_json.append(_end_);

    this->JSON = s_json;
}

std::string utils::json::substructure(slrtree::node &_n)
{
    std::string s_struct, c_struct, l_struct, state_name;
    bool is_jump_to_state = false;

    auto t_key = condense(_n.subproductions);
    auto t_find = t_map.find(t_key);
    if (t_find != t_map.end())
    {
        l_struct.append(name(t_find->second) + ",");
        is_jump_to_state = true;
        state_name = "";
    }
    else
    {
        state_name = t_map[t_key] = s_map[t_key];
        for (const auto &p_n : _n.subproductions)
            l_struct.append(name(get_prodt(p_n)) + ",");
    }
    s_struct.append(text(l_struct + state(state_name)) + ",");

    if (not _n.states.empty() and not is_jump_to_state)
    {
        for (const auto &[f, s] : _n.states)
        {
            if (*(&s) != NULL)
                c_struct.append(substructure(*s) + ",");
            else
                c_struct.append(enclose(text(name("SELF-LOOP"))) + ",");
        }
        if (not c_struct.empty())
            c_struct = children(c_struct);
    }
    s_struct = enclose(s_struct + c_struct);
    return s_struct;
}

std::vector<std::string> utils::augmentize(std::string p)
{
    std::vector<std::string> aug_l;
    char *ptr;
    ptr = strtok(const_cast<char *>(p.c_str()), "|");
    while (ptr != NULL)
    {
        aug_l.push_back("." + std::string(ptr));
        ptr = strtok(NULL, "|");
    }
    return aug_l;
}
bool utils::has_dot(std::string p) { return p.find('.', 0) != std::string::npos; }
bool utils::not_in(PRODTS P, PRODT _p)
{
    for (const auto &[f, s] : P)
    {
        if (_p.first == f and _p.second == s)
            return false;
    }
    return true;
}
#endif