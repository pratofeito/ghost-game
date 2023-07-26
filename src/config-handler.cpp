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

    file.close();
}

void Config::set(string config_file_path, string config, string value)
{
    std::ifstream input_file(config_file_path);

    std::vector<std::string> lines;
    std::string input;

    string line, arg1, arg2;

    while (getline(input_file, line))
    {
        lines.push_back(line);
    }

    input_file.close();

    std::ofstream output_file(config_file_path);

    for (auto &line : lines)
    {
        istringstream sstring(line);
        sstring >> arg1 >> arg2;

        if (arg1 == config)
        {
            line = config + " " + value;
        }
    }

    for (auto const &line : lines)
    {
        output_file << line << "\n";
    }

    output_file.close();

}

string Config::get(string identifier)
{
    return config_list[identifier];
}