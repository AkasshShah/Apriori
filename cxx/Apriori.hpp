#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>

#include "Transactions.hpp"

namespace crow
{
    // double get_support(Transactions db, std::set<std::string> items)

    void Apriori(Transactions db, double minimum_support, double minimum_confidence)
    {
        
    }
} // namespace crow