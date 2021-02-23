#include <iostream> // std::cout std::cin
#include <fstream> // std::ifstream
#include <iomanip> // std::setw
#include <string> // std::string
#include <array> // std::array
#include <set> // std::set

#include "include/nlohmann/json.hpp"
#include "Apriori.hpp"
#include "Transactions.hpp"

int main(int argc, char* argv[])
{
    const int NUM_DBS = 5;
    // locations of the json info
    std::string file_items = "../items.json";
    std::string file_db[NUM_DBS] = {
        "../db1_transactions.json",
        "../db2_transactions.json",
        "../db3_transactions.json",
        "../db4_transactions.json",
        "../db5_transactions.json"
    };

    // make nlohmann::json objects
    nlohmann::json itemsjson;
    std::array<nlohmann::json, NUM_DBS> dbs_transaction;

    // first load json data into nlohmann::json objects
    std::ifstream ifs;
    ifs.open(file_items);
    ifs >> itemsjson;
    if(ifs.is_open()) ifs.close();
    
    for(int i = 0; i < NUM_DBS; i++)
    {
        std::ifstream ifss(file_db[i]);
        std::stringstream buffer;
        buffer << ifss.rdbuf();
        dbs_transaction[i] = nlohmann::json::parse(buffer.str());
        if(ifss.is_open()) ifss.close();
    }

    // std::cout << std::setw(4) << dbs_transaction[0] << std::endl; // test

    // make set of all the items
    std::set<std::string> items;
    for(std::string item : itemsjson)
    {
        items.insert(item);
    }

    // test print
    // for(std::string item : items)
    // {
    //     std::cout << item << std::endl;
    // }
    // std::cout << items.count("some item") << std::endl;

    // iterate through each database and generate Transactions and perform Apriori on those transactions
    for(int i = 0; i < NUM_DBS; i++)
    {
        // generate Transactions obj
        crow::Transactions dbt(items);
        

        for(int j = 0; j < dbs_transaction[i].size(); j++)
        {
            std::vector<std::string> transaction;
            for(int k = 0; k < dbs_transaction[i][j].size(); k++)
            {
                transaction.push_back(dbs_transaction[i][j][k]);
            }
            dbt.push_transaction(transaction);
        }
        // std::cout << "DB " << i + 1 << " has " << dbt.count() << " transactions\n";

        
    }

    return(1);
}