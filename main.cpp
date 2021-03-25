#include <iostream>
#include "zonecount_impl.hpp"

using namespace tarikumutlu;

int main(int argc, char const *argv[])
{
    std::string filename = parseArgs(argc, argv);
    std::cout<<"filename: "<<filename <<std::endl;
    MapImpl map;
    map.LoadMapFromFile(filename);
    map.Show();

    ZoneCounterImpl zci;
    zci.Init(&map);
    int result = zci.Solve();
    std::cout << "Zone Count is : " << result << std::endl;

    return 0;
}
