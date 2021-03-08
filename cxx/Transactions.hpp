#pragma once

#include <array>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

// #include "Apriori.hpp" // bool is_subset(const std::set<std::string>& haystack, const std::set<std::string>& needles)

namespace crow
{
    template<typename T>
    bool is_subset(const std::set<T>& haystack, const std::set<T>& needles)
    {
        for(const auto& needle : needles) {if(haystack.find(needle) == haystack.end()) {return(false);}}
        return(true);
    }

    template<typename T>
    std::set<T> make_union(const std::set<T>& a, const std::set<T>& b)
    {
        std::set<T> result = a;
        result.insert(b.begin(), b.end());
        return result;
    }

    // class Transaction will store all the transactions of a database and all unique items that can/have be/been bought
    // eventually need to make it template-styled
    // template<typename T>
    class Transactions
    {
    private:
        const std::set<std::string>& items;
        std::vector<std::set<std::string>> transactions;
        // id of db
        int transactions_id;
        double minimum_support;
        double minimum_confidence;
        // rules will be stored in a map where the keys will be an array of size 2
        // where the first element will be a set of the antecedents
        // and the second element will be a set of the consequents
        // the key will also be an array of size 2
        // where the first elemet will be the double support
        // and the second element will be the double confidence
        std::map<std::array<std::set<std::string>, 2>, std::array<double, 2>> rules;
        std::map<std::set<std::string>, double> known_support_values;
    public:
        Transactions(const std::set<std::string>&, int, std::array<double, 2>);
        ~Transactions();
        void push_transaction(const std::set<std::string>&);
        std::size_t size(); // returns the number of transaction in obj
        double get_minimum_support();
        void set_minimum_support(double);
        double get_support(const std::set<std::string>);
        double get_minimum_confidence();
        void set_minimum_confidence(double);
        double get_coonfidence(const std::set<std::string> antecedents, std::set<std::string> consequents);
        friend std::ostream& operator<<(std::ostream&, const Transactions&);
    };
    
    Transactions::Transactions(const std::set<std::string>& items, int transactions_id, std::array<double, 2> supp_and_conf)
        : items(items),
        transactions_id(transactions_id),
        minimum_support(supp_and_conf[0]),
        minimum_confidence(supp_and_conf[1])
    {
    }
    
    Transactions::~Transactions()
    {
    }

    void Transactions::push_transaction(const std::set<std::string>& transaction)
    {
        this->transactions.push_back(transaction);
    }

    std::size_t Transactions::size()
    {
        return(this->transactions.size());
    }

    double Transactions::get_minimum_support() {return(this->minimum_support);}
    void Transactions::set_minimum_support(double supp) {this->minimum_support = supp;}
    double Transactions::get_support(const std::set<std::string> itemset)
    {
        // check if any item in itemset not in this->items
        for(std::string item : itemset) {if(this->items.find(item) == this->items.end()) {return(0.0);}}
        int count = 0;
        for(const auto& transaction : this->transactions)
        {
            if(crow::is_subset<std::string>(transaction, itemset)) {count++;}
        }
        return((double)count/(double)this->size());
    }
    double Transactions::get_minimum_confidence() {return(minimum_confidence);}
    void Transactions::set_minimum_confidence(double conf) {minimum_confidence = conf;}
    double Transactions::get_coonfidence(const std::set<std::string> antecedents, std::set<std::string> consequents)
    {
        return(this->get_support(crow::make_union<std::string>(antecedents, consequents)) / this->get_support(antecedents));
    }
    std::ostream& operator<<(std::ostream& os, const Transactions& db)
    {
        std::string line_break = "---------------------------------";
        os << line_break << std::endl;
        os << "Apriori on DB with id" << db.transactions_id << std::endl;
        os << "Items in DB:\n[\n";
        for(std::string item : db.items)
        {
            os << item << std::endl;
        }
        os << "]\n\n";
        os << "The DB has the following transactions:\n";
        for(const auto& transaction : db.transactions)
        {
            // for(int i = 0; i < transaction.size(); i++)
            for(const auto& it : transaction)
            {
                os << it << "; ";
                // os << transaction[i];
                // if(i <= transaction.size() - 1)
                // {
                //     os << "; ";
                // }
            }
            os << std::endl;
        }
        if(!db.rules.empty())
        {
            os << "\n\n";
            os << "The DB has the following basket Apriori rules:\n";
            os << "Minimum support: " << db.minimum_support << "; Minimum confidence: " << db.minimum_confidence << std::endl;
            os << "Format for the rules printing: (antecedents) -> (consequents) : support, confidence\n";
            for(auto it = db.rules.begin(); it != db.rules.end(); it++)
            {
                auto antecedents = it->first[0];
                auto consequents = it->first[1];
                auto support = it->second[0];
                auto confidence = it->second[1];

                os << "( ";
                for(std::string ant : antecedents)
                {
                    os << ant << ", ";
                }
                os << ") -> ( ";
                for(std::string con : consequents)
                {
                    os << con << ", ";
                }
                os << ") : " << support << ", " << confidence << std::endl;
            }
        }
        os << line_break;
        return(os);
    }
    
} // namespace crow
