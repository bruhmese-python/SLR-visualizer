#include "slrtree.h"
#include <iostream>
#include <numeric>
#include <algorithm>

auto CMP = [](PRODT n_p, PRODT _p)
{ return (_p.first == n_p.first and _p.second == n_p.second); };
auto stringify = [](PRODT _p)
{ return (std::string(1, _p.first) + "->" + _p.second); };

std::string condense(PRODTS &s_p)
{
    std::string value;
    for (const auto &_p : s_p)
        value += stringify(_p) + "\n";
    return value;
}

void set_NULL(slrtree::node **s) { *s = NULL; }

bool slrtree ::node::find_in(PRODT _p) const
{
    for (const auto &each : this->subproductions)
    {
        if (CMP(each, _p))
            return true;
    }
    return false;
}
void slrtree ::node::iterate()
{
    std::set<char> nexts;

    // Save to firstadded (for future check )
    for (const auto &s_p : this->subproductions)
        this->firstadded.insert(s_p);

    for (auto k = m_productions.size(); k--;)
    {

        // Get Elements after dot
        for (const auto &[A, _p] : this->subproductions)
        {
            std::string RHS(_p);
            if (shiftable(RHS))
                nexts.insert(get_next(RHS));
        }

        // Draw out productions from main (not I0)
        for (const auto &n : nexts)
        {
            this->add_prodts_from_main(n);
        }
    }

    // Create new states
    auto BEGIN = this->subproductions.begin(), END = this->subproductions.end();
    for (PRODTS::iterator p_it(BEGIN); p_it != END; p_it++)
    {
        // std::cout << "--Consider production :" << p_it->first << "->" << p_it->second << "\n";
        if (shiftable(p_it->second))
        {
            char alpha = get_next(p_it->second);
            this->add_to_state(alpha, PRODT(p_it->first, shifted(p_it->second)));
            for (PRODTS::iterator p_jt(p_it); p_jt != END; p_jt++)
            {
                if (shiftable(p_jt->second) and p_jt != p_it)
                {
                    if (alpha == get_next(p_jt->second))
                    {
                        this->add_to_state(alpha, PRODT(p_jt->first, shifted(p_jt->second)));
                    }
                }
            }

            if (this->states[alpha]->subproductions == this->firstadded)
            {
                // std::cout << "Self loop ->" << alpha << "<-\n";
                set_NULL(&(this->states[alpha]));
            }
        }
    }

    for (const auto &[A, _p] : this->subproductions)
    {
        std::string RHS(_p);
        if (shiftable(RHS))
            nexts.insert(get_next(RHS));
    }

    auto t_key = condense(this->subproductions);
    if (m_states.find(t_key) == m_states.end())
        m_states[t_key] = "I" + std::to_string(_n_++);

    if (states.empty())
        return;

    /* std::cout << "\nNexts: ";
    std::for_each(nexts.begin(), nexts.end(), [](const char &c)
                  { std::cout << " " << c; });
    std::cout << '\n';

    std::cout << " Iteration \n-----------\n";
    for (const auto &[f, s] : this->subproductions)
        std::cout << f << "->" << s << std::endl;
    std::cout << " States \n-----------\n";
    for (const auto &[f, s] : this->states)
    {
        std::cout << "-" << f << "-> [";
        if (s != NULL)
        {
            for (const auto &[_f, _s] : s->subproductions)
                std::cout << _f << "->" << _s << " , ";
        }
        std::cout << " ]" << std::endl;
    } */
    for (const auto &[_s, child] : this->states)
    {
        if (child != NULL)
            child->iterate();
    }
}

void slrtree ::node::add_prodts(PRODT _p)
{
    if (not this->find_in(_p))
        this->subproductions.insert(_p);
}
void slrtree ::node::add_prodts_from_main(char A)
{
    for (const auto &_p : m_productions)
    {
        if (_p.first == A)
        {
            this->add_prodts(_p);
            // std::cout << "Adding prodt :" << _p.first << "->" << _p.second << "\n";
        }
    }
}
void slrtree::node::add_to_state(char &A, PRODT _ps)
{
    if (this->states.find(A) != states.end())
    {
        // std::cout << "Added since found while " << A << "\n";
        this->states[A]->add_prodts(_ps);
    }
    else
    {
        struct node *newnode = new node;
        this->states[A] = newnode;
        newnode->add_prodts(_ps);
        // std::cout << "Created since not found while " << A << "\n";
    }
    // std::cout << "Added to state " << A << " : " << _ps.first << "->" << shifted(_ps.second) << "\n";
}
bool slrtree::node::shiftable(std::string &_p) const
{
    auto i = _p.find_first_of(".");
    if (not(i < _p.size() - 1))
    {
        // std::cout << "Unshiftable " << _p << "\n";
        return false;
    }
    // std::cout << "Already in finished state : " << _p << '\n';
    return true;
}
std::string slrtree::node::shifted(std::string _p) const
{

    auto i = _p.find_first_of(".");
    if (i < _p.size() - 1)
    {
        char _t = _p[i + 1];
        _p[i + 1] = _p[i];
        _p[i] = _t;
    }
    return _p;
}
char slrtree::node::get_next(std::string &_p) const
{
    auto i = _p.find_first_of(".");
    // std::cout << "got next :" << _p[i + 1] << '\n';
    return _p[i + 1];
}

slrtree::slrtree(PRODTS _ps, node **_root_addr, STATE_MAP **s_m)
{
    struct node *root = new node;
    *_root_addr = root;
    m_productions = _ps;
    root->subproductions = m_productions;
    // std::cout << "m_productions: " << (m_productions.begin()++)->first << "->" << (m_productions.begin()++)->second << " ...\n";
    // std::cout << "root->subproductions: " << (root->subproductions.begin()++)->first << "->" << (root->subproductions.begin()++)->second << " ...\n";
    root->iterate();
    *s_m = &m_states;
}

slrtree::slrtree() {}
slrtree::~slrtree() {}
