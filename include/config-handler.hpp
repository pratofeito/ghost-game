#ifndef PTE_CONFIG_HANDLER_HPP
#define PTE_CONFIG_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class Config
{
private:
    map<string, string> config_list;
    fstream file;

public:
    Config();
    void load(string config_file_path);
    void set(string config_file_path, string config, string value);
    string get(string identifier);
};

#endif