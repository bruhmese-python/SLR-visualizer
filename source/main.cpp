#include <iostream>
#include <iterator>
// #include <time.h>
#include <regex>
#include "utils.h"
using namespace std;

int main(int argc, char const *argv[])
{
    // time_t start, end;
    // time(&start);

    PRODTS productions = {
        // {'S', "AA"},
        // {'A', "aA|b"}
    };

    int counter;

    string START_SYMBOL;

    if (argc >= 2)
    {
        regex regexp("(.{1})->(.+)");
        for (counter = 1; counter < argc; counter++)
        {
            cmatch cm;
            // cout << " " << argv[counter] << "\n";
            if (regex_search(argv[counter], cm, regexp))
                productions.insert(PRODT(string(cm[1], 0)[0], string(cm[2], 0)));
            if (counter == 1)
                START_SYMBOL = string(cm[1], 0);
        }
    }
    else
        return -1;

    PRODTS augmented{};
    for (const auto &prod : productions)
    {
        if (utils::has_dot(prod.second))
        {
            // cout << "Grammar has delimiter character \'.\'\n";
            return -1;
        }
        auto v = utils::augmentize(prod.second);
        for (auto _v : v)
        {
            auto _V = PRODT(prod.first, _v);
            if (utils::not_in(augmented, _V))
                augmented.insert(_V);
        }
        auto _v = PRODT('\'', string(".") + START_SYMBOL);
        if (utils::not_in(augmented, _v))
            augmented.insert(_v);
    }
    // cout << "Initial Grammar\n";
    // cout << '\'' << "->" << augmented.find('\'')->second << "\n";
    // for (auto i : augmented)
    //     cout << i.first << "->" << i.second << "\n";

    slrtree::node *root;
    STATE_MAP *s_m;
    slrtree tree(augmented, &root, &s_m);
    /* for (const auto &[f, s] : *s_m)
        std::cout << f << "\n"; */

    utils::json JSON(*root, *s_m);
    cout << JSON.JSON;

    // time(&end);
    // double time_taken = double(end - start);
    // std::cout << "\nExecution finished in " << time_taken << " seconds \n";
    return 0;
}
