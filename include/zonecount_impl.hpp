#pragma once

#include "izonecount.hpp"
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
        int m_actualWidth;
        int m_actualHeight;

    private:
        void CreateMap();

    public:
        MapImpl();
        MapImpl(int width, int height);
        ~MapImpl();
        // Creates a map of given size. It
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
        int const *const *GetMap() const;
        /**
        * @brief Load map from a txt file. Txt file format:
        * first line is comma seperated width and height.
        * second line is comma seperated value for each zone points as index.
        * 
        * @param filepath 
        * @return true file is found
        * @return false file is not found
        */
        bool LoadMapFromFile(const std::string &filepath = "../maps/map.txt");
        // Show map contents.
        void Show();
    };

    class ZoneCounterImpl : public ZoneCounterInterface
    {
    private:
        MapInterface *m_map;

        /**
         * @brief It follows a point at (x,y) until zone is completed.
         * x,y point must be not followed before and can be anypoint in anywhere.
         * 
         * @param x A start point x
         * @param y A start point y
         * @param width Map width
         * @param height Map height
         * @param borderMap unordered map which has all zone points, not border points.
         * 
         * @return true: if one zone is found.
         * @return false: if given point is a border point
         */
        bool LookNeighbor(int x, int y, int width, int height, std::unordered_map<int, int> &zonePointMap);

        int m_zoneCount;

    public:
        ZoneCounterImpl();
        ~ZoneCounterImpl();
        // Feeds map instance into solution class, and initialize.
        void Init(MapInterface *map);

        // Counts zones in provided map and return result.
        int Solve();
    };

    /**
     * @brief Get the ZoneCounter object
     * 
     * @return ZoneCounterInterface* 
     */
    ZoneCounterInterface *getZoneCounter();

}