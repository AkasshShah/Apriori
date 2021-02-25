#pragma once

#include <array>
#include <vector>
#include <string>
#include <set>
#include <map>

namespace crow
{
    // class Transaction will store all the transactions of a database and all unique items that can/have be/been bought
    class Transactions
    {
    private:
        const std::set<std::string>& items;
        std::vector<std::vector<std::string>> transactions;
        int transactions_id;
        double minimum_support;
        double minimum_confidence;
        // rules will be stored in a map where the keys will be an array of size 2
        // where the first element will be a set of the antecedents
        // and the second element will be a set of the consequents
        // the key will also be an array of size 2
        // where the first elemet will be the int support
        // and the second element will be the int confidence
        std::map<std::array<std::set<std::string>, 2>, std::array<int, 2>> rules;
    public:
        Transactions(const std::set<std::string>&, int, std::array<double, 2>);
        ~Transactions();
        void push_transaction(const std::vector<std::string>&);
        std::size_t size(); // returns the number of transaction in obj
        double get_minimum_support();
        void set_minimum_support(double);
        double get_minimum_confidence();
        void set_minimum_confidence(double);
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

    void Transactions::push_transaction(const std::vector<std::string>& transaction)
    {
        transactions.push_back(transaction);
    }

    std::size_t Transactions::size()
    {
        return(transactions.size());
    }

    double Transactions::get_minimum_support() {return(minimum_support);}
    void Transactions::set_minimum_support(double supp) {minimum_support = supp;}
    double Transactions::get_minimum_confidence() {return(minimum_confidence);}
    void Transactions::set_minimum_confidence(double conf) {minimum_confidence = conf;}

    std::ostream& operator<<(std::ostream& os, const Transactions& db)
    {
        os << "---------------------------------\n";
        os << "Apriori on DB with id" << db.transactions_id << std::endl;
        os << "Items in DB:\n[\n";
        for(std::string item : db.items)
        {
            os << item << std::endl;
        }
        os << "]\n\n";
        os << "The DB has the following transactions:\n";
        for(std::vector<std::string> transaction : db.transactions)
        {
            for(int i = 0; i < transaction.size(); i++)
            {
                os << transaction[i];
                if(i <= transaction.size() - 1)
                {
                    os << "; ";
                }
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
                auto lhs = it->first;
                auto rhs = it->second;
                auto antecedents = lhs[0];
                auto consequents = lhs[1];
                auto support = rhs[0];
                auto confidence = rhs[1];
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
        os << "---------------------------------";
        return(os);
    }
    
} // namespace crow
