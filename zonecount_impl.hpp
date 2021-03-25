#pragma once

#include "zonecount.hpp"
#include <iostream>
#include <unordered_map>
#include "utils.hpp"

namespace tarikumutlu
{
    class MapImpl : public MapInterface
    {
    private:
        int m_height;
        int m_width;
        int **m_map;

    private:
        void CreateMap();

    public:
        MapImpl();
        MapImpl(int width, int height);
        ~MapImpl();
        // Creates a map of given size.
        void SetSize(const int width, const int height);
        // Returns size of map to solve.
        void GetSize(int &width, int &height);
        // Sets border at given point.
        void SetBorder(const int x, const int y);

        // Clears border at given point.
        void ClearBorder(const int x, const int y);
        // Checks if there is a border at given point.
        bool IsBorder(const int x, const int y);
        // Get read-only map
        int const* const* GetMap() const;
        // Load Map from txt file. 
        // first line is comma seperated width and height
        // second line is comma seperated value for each cell.
        void LoadMapFromFile(const std::string& filename = "map.txt");
        // Show map contents.
        void Show();


    };

    class ZoneCounterImpl : public ZoneCounterInterface
    {
    private:
        MapInterface *m_map;

        void LookNeighbour(int x, int y, int width, int height, std::unordered_map<int,int> &borderMap);

        int m_zoneCount;

    public:
        ZoneCounterImpl();
        ~ZoneCounterImpl();
        // Feeds map instance into solution class, and initialize.
        void Init(MapInterface *map);
        
        // Counts zones in provided map, and return result.
        int Solve();
    };

}