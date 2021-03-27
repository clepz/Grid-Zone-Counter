#include <iostream>
#include "zonecount_impl.hpp"

using namespace tarikumutlu;

void createMap(MapInterface &map){
    map.SetSize(5,5);
    map.SetBorder(3,1);
    map.SetBorder(3,2);
    map.SetBorder(3,3);
    map.SetBorder(3,4);
    map.SetBorder(3,5);
}

int main(int argc, char const *argv[])
{
    std::string filepath = parseArgs(argc, argv);
    LOG("filepath: ", filepath);

    //Load a map from file and count zones.
    MapImpl map;
    bool res = map.LoadMapFromFile(filepath);
    if(!res)
        return -1;
    map.Show();

    ZoneCounterInterface* zc = getZoneCounter();
    zc->Init(&map);
    int result = zc->Solve();
    LOG("Zone Count is : ", result)
    //-------

    //Create a map with functions and count zones.
    MapImpl map2;
    createMap(map2);
    map2.Show();
    zc->Init(&map2);
    int result2 = zc->Solve();
    LOG("Zone Count is : ", result2)

    return 0;
}
