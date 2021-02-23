#pragma once

#include <vector>
#include <string>
#include <set>

namespace crow
{
    // class Transaction will store all the transactions of a database and all unique items that can/have be/been bought
    class Transactions
    {
    private:
        const std::set<std::string>& items;
        std::vector<std::vector<std::string>> transactions;
    public:
        Transactions(const std::set<std::string>&);
        ~Transactions();
        void push_transaction(const std::vector<std::string>&);
        std::size_t count(); // returns the number of transaction in obj
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

    std::size_t Transactions::count()
    {
        return(transactions.size());
    }
    
} // namespace crow
