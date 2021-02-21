#include <iostream> // std::cout std::cin
#include <fstream> // std::ifstream
#include <iomanip> // std::setw
#include <string> // std::string
#include <array> //std::array

#include "include/nlohmann/json.hpp"
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
    nlohmann::json items;
    std::array<nlohmann::json, NUM_DBS> dbs_transaction;

    // first load json data into nlohmann::json objects
    std::ifstream ifs;
    ifs.open(file_items);
    ifs >> items;
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

    

    return(1);
}