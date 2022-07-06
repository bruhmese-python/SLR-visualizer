#ifndef SLRTREE_H
#define SLRTREE_H
#pragma once
#define PRODTS std::multimap<char, std::string>
#define PRODT std::pair<char, std::string>
#define STATE std::map<char, struct node *>
#define STATE_MAP std::map<std::string, std::string>

#include <map>
#include <vector>
#include <string>
#include <set>

class slrtree
{
private:
    static PRODTS m_productions;
    static STATE_MAP m_states;
    static int _n_;

public:
    struct node;

    slrtree();
    ~slrtree();
    slrtree(PRODTS _P, node **_root_addr, STATE_MAP **s_m);
};
int slrtree::_n_ = 0;
struct slrtree ::node
{
    PRODTS subproductions;
    STATE states;
    PRODTS firstadded;

    void iterate();
    void add_prodts(PRODT _p);
    void add_prodts_from_main(char A);
    void add_to_state(char &A, PRODT _P);

    std::string shifted(std::string _p) const;
    char get_next(std::string &_p) const;
    bool shiftable(std::string &_p) const;
    bool find_in(PRODT _p) const;
};
PRODTS slrtree::m_productions = {};
STATE_MAP slrtree::m_states = {};
#endif