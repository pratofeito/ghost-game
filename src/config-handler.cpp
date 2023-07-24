#include "config-handler.hpp"

Config::Config()
{
}

void Config::load(string config_file_path)
{
    file.open(config_file_path);

    string line, arg1, arg2;
    while (getline(file, line))
    {
        istringstream sstring(line);
        sstring >> arg1 >> arg2;

        config_list[arg1] = arg2;
    }
}

string Config::get(string identifier)
{
    return config_list[identifier];
}