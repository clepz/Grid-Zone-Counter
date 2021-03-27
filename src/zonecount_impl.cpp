#include "zonecount_impl.hpp"
#include <fstream>

#define CHECK_KEY_IS_BORDER(key) \
key <=0 || key / width == 0 || key % width == 0 || key % width == width-1 || key % (height*(width-1))<width ? true:false;

namespace tarikumutlu
{
    //---MapImpl---

    MapImpl::MapImpl() : m_map(nullptr){};
    MapImpl::MapImpl(int width, int height) : m_width(width), m_height(height)
    {
        CreateMap();
    };
    MapImpl::~MapImpl()
    {
        if (m_map != nullptr)
        {
            for (int i = 0; i < m_width; i++)
                delete m_map[i];
            delete m_map;
        }
    }

    void MapImpl::CreateMap()
    {
        m_map = new int *[m_actualWidth] { 0 };
        for (int i = 0; i < m_actualWidth; i++)
            m_map[i] = new int[m_actualHeight]{0};

        // add border for map edges.
        for (int i = 0; i < m_actualWidth; i++)
        {
            SetBorder(i, 0);
            SetBorder(m_actualWidth - i - 1, m_actualHeight - 1);
        }
        for( int i = 0 ; i < m_actualHeight ; i++) {
            SetBorder(0, i);
            SetBorder(m_actualWidth - 1 , m_actualHeight - i - 1);
        }
    }
    // Creates a map of given size.
    void MapImpl::SetSize(const int width, const int height)
    {
        // add the map edges as border for better understanding of the algorithm
        m_height = height;
        m_width = width;
        m_actualWidth = width + 2;
        m_actualHeight = height +2;
        CreateMap();
    };
    // Returns size of map to solve.
    void MapImpl::GetSize(int &width, int &height)
    {
        width = m_width;
        height = m_height;
    };
    // Sets border at given point.
    void MapImpl::SetBorder(const int x, const int y)
    {
        m_map[x][y] = -1;
    };

    // Clears border at given point.
    void MapImpl::ClearBorder(const int x, const int y)
    {
        m_map[x][y] = 0;
    };
    // Checks if there is a border at given point.
    bool MapImpl::IsBorder(const int x, const int y)
    {
        if (x < 0 || x >= m_actualWidth || y < 0 || y >= m_actualHeight)
            return true;
        return m_map[x][y] == -1 ? true : false;
    };
    int const *const *MapImpl::GetMap() const
    {
        return m_map;
    }
    bool MapImpl::LoadMapFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            LOG("File is not exist")
            return false;
        }

        //first line gives width and height
        std::string line;
        std::getline(file, line);

        int width = StringToInt(line.substr(0, line.find(',')));
        int height = StringToInt(line.substr(line.find(',') + 1, line.length() - 1));
        SetSize(width,height);
        CreateMap();

        //second line is a value that corresponding x,y is border or not.
        std::getline(file, line);
        file.close();

        std::istringstream ss(line);
        std::string tmp;
        for (int x = 1; x < m_actualHeight-1; x++)
        {
            for (int y = 1; y < m_actualWidth-1; y++)
            {
                std::getline(ss, tmp, ',');
                m_map[y][x] = StringToInt(tmp);
            }
        }
        //Map reading is completed.
        return true;
    }

    // Show map contents as a map.
    void MapImpl::Show()
    {
        for (int y = 1; y < m_actualHeight-1; y++)
        {
            for (int x = 1; x < m_actualWidth-1; x++)
            {
                m_map[x][y] ? std::cout << "\u25A0" : std::cout << "\u25A1";
                std::cout << " ";
            }
            std::cout << "\n";
        }
    };

    // -------------------
    //---ZoneCounterImpl---

    ZoneCounterImpl::ZoneCounterImpl() : m_map(nullptr), m_zoneCount(0) {}

    ZoneCounterImpl::~ZoneCounterImpl() { m_map = nullptr; }

    // Feeds map instance into solution class, and initialize.
    void ZoneCounterImpl::Init(MapInterface *map)
    {
        m_zoneCount = 0;
        this->m_map = map;
    }

    // Counts zones in provided map, and return result.
    int ZoneCounterImpl::Solve()
    {
        int width;
        int height;
        m_map->GetSize(width, height); // Need to get actual size.
        //TODO: border edges add process and storing need to be in this class.
        LOG("width: ", width);
        LOG("height : ", height)
        width += 2; // because actual size is +2.
        height += 2;
        std::unordered_map<int, int> zonePointMap;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (!m_map->IsBorder(x, y))
                {
                    //store points with index.
                    zonePointMap[y * (width) + x] = 0;
                }
            }
        }

        // even if map has only one point, there is a zone. 
        while (zonePointMap.size() != 0)
        {
            //unorder_map BigO is 1.
            auto key = getPointFromMap(zonePointMap, width);
            int x = key.first;
            int y = key.second;
            LOG("search start point: ", x, "-", y);
            //every return of this function is 
            int res = LookNeighbor(x, y, width, height, zonePointMap);
            if(res) m_zoneCount++;
        }

        return m_zoneCount;
    }

    bool ZoneCounterImpl::LookNeighbor(int x, int y, int width, int height, std::unordered_map<int, int> &zonePointMap)
    {
        int key = y * width + x;
        if (zonePointMap.find(key) == zonePointMap.end())
            return false;
        else if (zonePointMap[key] == 0)
        {
            // delete current zone point from the map.
            zonePointMap.erase(key);
            
            // find neighbor zone point's key 
            int n4x = x - 1; // < 0 ? 0 : x - 1;
            int n27x = x;
            int n5x = x + 1; // > 9 ? 9 : x + 1;
            int n2y = y - 1; // < 0 ? 0 : y - 1;
            int n45y = y;
            int n7y = y + 1; // > 6 ? 6 : y + 1;

            int n4 = n45y * width + n4x;  // orta sol
            int n2 = n2y * width + n27x;  // orta ust
            int n7 = n7y * width + n27x;  // orta alt
            int n5 = n45y * width + n5x;  // orta sag
            
            // search all zone points that are neighbor. then return.
            if (zonePointMap.find(n4) != zonePointMap.end())
            {
                LookNeighbor(n4x, n45y, width, height, zonePointMap);
            }
            if (zonePointMap.find(n2) != zonePointMap.end())
            {
                LookNeighbor(n27x, n2y, width, height, zonePointMap);
            }
            if (zonePointMap.find(n7) != zonePointMap.end())
            {
                LookNeighbor(n27x, n7y, width, height, zonePointMap);
            }
            if (zonePointMap.find(n5) != zonePointMap.end())
            {
                LookNeighbor(n5x, n45y, width, height, zonePointMap);
            }
        }
        return true;
    }

    ZoneCounterInterface *getZoneCounter()
    {
        return new ZoneCounterImpl();
    }

}