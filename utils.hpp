#pragma once
#include <string>
#include <sstream>

inline int StringToInt(const std::string &s)
{
    return std::stoi(s);
}

inline std::string parseArgs(int argc, char const *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg == "--help")
        {
            std::cout << "--filename <txt path, default is `map.txt`>";
        }
        else if (arg == "--filename")
        {
            if (i + 1 < argc)
                return std::string(argv[++i]);
        }
    }
    return "map.txt";
}