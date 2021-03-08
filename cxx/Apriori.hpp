#pragma once

#include <math.h>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <iostream>
#include <map>

#include "Transactions.hpp"

namespace crow
{
    bool is_bit_set(int num, int bit)
    {
        return((num & (1 << bit)) > 0);
    }

    std::vector<std::set<std::string>> gen_subsets(const std::set<std::string>& st)
    {
        std::vector<std::set<std::string>> rtn;
        for(int i = 0; i < 1 << st.size(); i++) // for(int i = 0; i < 2^st.size(); i++)
        {
            std::set<std::string> s1;
            int bit = 0;
            for(auto it = st.cbegin(); it != st.cend(); it++)
            {
                if(crow::is_bit_set(i, bit))
                {
                    s1.insert(*it);
                }
                bit++;
            }
            rtn.push_back(s1);
        }
        return(rtn);
    }

    std::vector<std::set<std::string>> gen_subsets_of_length(const std::set<std::string>& st, ssize_t sz)
    {
        std::vector<std::set<std::string>> rtn;
        for(int i = 0; i < 1 << st.size(); i++) // for(int i = 0; i < 2^st.size(); i++)
        {
            std::set<std::string> s1;
            int bit = 0;
            for(auto it = st.cbegin(); it != st.cend(); it++)
            {
                if(crow::is_bit_set(i, bit))
                {
                    s1.insert(*it);
                }
                bit++;
            }
            if(s1.size() == sz)
            {
                rtn.push_back(s1);
            }
        }
        return(rtn);
    }

    // double get_support(Transactions db, std::set<std::string> items)

    void Apriori(Transactions& db)
    {
        auto minimum_support = db.get_minimum_support();
        auto minimum_confidence = db.get_minimum_confidence();

        // std::map<std::array<std::set<std::string>, 2>, std::array<double, 2>> rules;
        
        
    }
} // namespace crow