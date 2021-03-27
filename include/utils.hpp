#pragma once
#include <string>
#include <sstream>
#include <unordered_map>

#define LOG(...)\
Logger(__VA_ARGS__);

//Generally, there are several logger functions(Debug, info ...) and they belongs to a singleton logger class.
//It is not necessary for this project.
template<typename ... Args>
void Logger(Args const & ... args)
{
	std::stringstream ss;
	using List= int[];
	(void)List{0, ( (void)(ss << args << " "), 0 ) ... };

	std::cout<<ss.str()<<std::endl;
}


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
            std::cout << "--filepath <txt path, default is `map.txt`>";
        }
        else if (arg == "--filepath")
        {
            if (i + 1 < argc)
                return std::string(argv[++i]);
        }
    }
    return "../maps/map.txt";
}

inline std::pair<int, int> getPointFromMap(const std::unordered_map<int,int>& map, int width){
        int keyFromMap = map.begin()->first;
        return std::make_pair(keyFromMap % width, keyFromMap / width);
}