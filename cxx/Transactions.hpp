#pragma once

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
        std::map<std::array<std::set<std::string>, 2>, std::array<int, 2>> rules;
    public:
        Transactions(const std::set<std::string>&);
        ~Transactions();
        void push_transaction(const std::vector<std::string>&);
        std::size_t size(); // returns the number of transaction in obj
    };
    
    Transactions::Transactions(const std::set<std::string>& items)
        : items(items)
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
    
} // namespace crow
