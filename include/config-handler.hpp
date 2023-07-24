#ifndef PTE_CONFIG_HANDLER_HPP
#define PTE_CONFIG_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class Config
{
private:
    map<string, string> config_list;
    ifstream file;

public:
    Config();
    void load(string config_file_path);
    string get(string identifier);
};

#endif