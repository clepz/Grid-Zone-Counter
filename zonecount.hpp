#pragma once

class MapInterface
{
public:
    virtual ~MapInterface() {}
    // Creates a map of given size.
    virtual void SetSize(const int width, const int height) = 0;
    // Returns size of map to solve.
    virtual void GetSize(int &width, int &height) = 0;
    // Sets border at given point.
    virtual void SetBorder(const int x, const int y) = 0;
    // Clears border at given point.
    virtual void ClearBorder(const int x, const int y) = 0;
    // Checks if there is a border at given point.
    virtual bool IsBorder(const int x, const int y) = 0;
    // Show map contents.
    virtual void Show() = 0;
};

class ZoneCounterInterface
{
public:
    virtual ~ZoneCounterInterface() {}
    // Feeds map instance into solution class, and initialize.
    virtual void Init(MapInterface *map) = 0;
    // Counts zones in provided map, and return result.
    virtual int Solve() = 0;
};
