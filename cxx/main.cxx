#include <iostream> // std::cout std::cin
#include <fstream> // std::ifstream
#include <iomanip> // std::setw
#include <string> // std::string
#include <array> // std::array
#include <set> // std::set

#include "include/nlohmann/json.hpp"
#include "Transactions.hpp"
#include "Apriori.hpp"

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

    // get minimum support and minimum confidence
    double minimum_support = 0.0;
    double minimum_confidence = 0.0;

    // get minimum support & confidence via std in
    // can also get them via cli inputs via argv
    std::cout << "Enter minimum support (out of 100): ";
    std::cin >> minimum_support;
    std::cout << "Enter minimum confidence (out of 100): ";
    std::cin >> minimum_confidence;
    minimum_support /= 100.0;
    minimum_confidence /= 100.0;


    // test print
    // for(std::string item : items)
    // {
    //     std::cout << item << std::endl;
    // }
    // std::cout << items.count("some item") << std::endl;

    std::array<double, 2> supp_and_conf = {minimum_support, minimum_confidence};

    // iterate through each database and generate Transactions and perform Apriori on those transactions
    for(int i = 0; i < NUM_DBS; i++)
    {
        // generate Transactions obj
        crow::Transactions dbt(items, i+1, supp_and_conf);
        
        for(int d = 0; d < dbs_transaction[i].size(); d++)
        {
            std::vector<std::string> transaction;
            for(int k = 0; k < dbs_transaction[i][d].size(); k++)
            {
                transaction.push_back(dbs_transaction[i][d][k]);
            }
            dbt.push_transaction(transaction);
        }
        // std::cout << "DB " << i + 1 << " has " << dbt.count() << " transactions\n";

        // done setting up db
        // now call apriori and output in standard out or file or both

        // crow::Apriori(dbt);

        // output information into file or standard output
        std::cout << dbt << std::endl;
    }

    return(1);
}