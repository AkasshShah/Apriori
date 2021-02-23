#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>

#include "Transactions.hpp"

namespace crow
{
    // should use ordered map implementation

    // class AprioriRule
    // {
    // private:
    //     std::set<std::string> antecedents;
    //     std::set<std::string> consequents;
    //     int support;
    //     int confidence;
    // public:
    //     AprioriRule(const std::set<std::string>&, const std::set<std::string>&, int, int);
    //     ~AprioriRule();
    //     friend std::ostream& operator<<(std::ostream& os, const AprioriRule& obj);
    // };
    
    // AprioriRule::AprioriRule(const std::set<std::string>& antecedents, const std::set<std::string>& consequents, int support, int confidence)
    //     : antecedents(antecedents),
    //     consequents(consequents),
    //     support(support),
    //     confidence(confidence)
    // {
    // }

    // AprioriRule::~AprioriRule()
    // {
    // }

    // std::ostream& operator<<(std::ostream& os, const AprioriRule& obj)
    // {
    //     // format:
    //     // ( antecedent1, ..., antecedentn, ) -> ( consequent1, ..., consequentn, ) : support, confidence
    //     os << "( ";
    //     for(std::string item : obj.antecedents){
    //         os << "item, ";
    //     }
    //     os << ") -> ( ";
    //     for(std::string item : obj.consequents){
    //         os << "item, ";
    //     }
    //     os << ") : " << obj.support << ", " << obj.confidence;
    //     return(os);
    // }
    
} // namespace crow