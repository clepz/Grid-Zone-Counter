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
        m_map = new int *[m_width] { 0 };
        for (int i = 0; i < m_width; i++)
            m_map[i] = new int[m_height]{0};

        // add border for map edges.
        for (int i = 0; i < m_width; i++)
        {
            SetBorder(i, 0);
            SetBorder(m_width - i - 1, m_height - 1);
        }
        for( int i = 0 ; i < m_height ; i++) {
            SetBorder(0, i);
            SetBorder(m_width - 1 , m_height - i - 1);
        }
    }
    // Creates a map of given size.
    void MapImpl::SetSize(const int width, const int height)
    {
        // add the map edges as border for better understanding of the algorithm
        m_height = height + 2;
        m_width = width + 2;
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
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
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

        m_width = StringToInt(line.substr(0, line.find(',')));
        m_height = StringToInt(line.substr(line.find(',') + 1, line.length() - 1));
        CreateMap();

        //second line is a value that corresponding x,y is border or not.
        std::getline(file, line);
        file.close();

        std::istringstream ss(line);
        std::string tmp;
        for (int x = 0; x < m_height; x++)
        {
            for (int y = 0; y < m_width; y++)
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
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
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
        m_map->GetSize(width, height);
        LOG("width (with edges) : ", width);
        LOG("height (with edges) : ", height)
        std::unordered_map<int, int> borderMap;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (m_map->IsBorder(x, y))
                {
                    borderMap[y * width + x] = 0;
                }
            }
        }

        //LookNeighbour(0, 0, width, height, borderMap);

        while (borderMap.size() != 0)
        {
            // I made a choice not using an ordered list. unorder_map insert and find methods' BigO is 1.
            // I think, insert and finds are being more accesing then findtopleftborder. This situation needs some tests.
            auto key = FindTopLeftBorder(borderMap, width);
            int x = key.first;
            int y = key.second;
            LOG("Finding top left border: ", x, "-", y);
            LookNeighbour(x, y, width, height, borderMap);
        }

        return m_zoneCount;
    }

    void ZoneCounterImpl::LookNeighbour(int x, int y, int width, int height, std::unordered_map<int, int> &borderMap)
    {
        static bool first = true;
        bool zoneLastBorder = true;
        int key = y * width + x;
        if (borderMap.find(key) == borderMap.end())
            return;
        else if (borderMap[key] == 0)
        {
            
            bool isKeyBorder = CHECK_KEY_IS_BORDER(key);
            borderMap.erase(key);
            int n146x = x - 1; // < 0 ? 0 : x - 1;
            int n27x = x;
            int n358x = x + 1; // > 9 ? 9 : x + 1;
            int n123y = y - 1; // < 0 ? 0 : y - 1;
            int n45y = y;
            int n678y = y + 1; // > 6 ? 6 : y + 1;

            int n4 = n45y * width + n146x;  // orta sol
            int n2 = n123y * width + n27x;  // orta ust
            int n1 = n123y * width + n146x; // sol ust
            int n7 = n678y * width + n27x;  // orta alt
            int n5 = n45y * width + n358x;  // orta sag
            int n3 = n123y * width + n358x; // sag ust
            int n8 = n678y * width + n358x; // sag alt
            int n6 = n678y * width + n146x; // sol alt
            
            int nBorderCount = 0;
            bool n1IsBorder = CHECK_KEY_IS_BORDER(n1);
            if(n1IsBorder && !isKeyBorder) nBorderCount++;
            bool n2IsBorder = CHECK_KEY_IS_BORDER(n2);
            if(n2IsBorder && !isKeyBorder) nBorderCount++;
            bool n3IsBorder = CHECK_KEY_IS_BORDER(n3);
            if(n3IsBorder && !isKeyBorder) nBorderCount++;
            bool n4IsBorder = CHECK_KEY_IS_BORDER(n4);
            if(n4IsBorder && !isKeyBorder) nBorderCount++;
            bool n5IsBorder = CHECK_KEY_IS_BORDER(n5);
            if(n5IsBorder && !isKeyBorder) nBorderCount++;
            bool n6IsBorder = CHECK_KEY_IS_BORDER(n6);
            if(n6IsBorder && !isKeyBorder) nBorderCount++;
            bool n7IsBorder = CHECK_KEY_IS_BORDER(n7);
            if(n7IsBorder && !isKeyBorder) nBorderCount++;
            bool n8IsBorder = CHECK_KEY_IS_BORDER(n8);
            if(n8IsBorder && !isKeyBorder) nBorderCount++;

            if(isKeyBorder && !first)
                first = true;
            if(!isKeyBorder)
                first = false;

            if (borderMap.find(n4) != borderMap.end() && borderMap[n4] == 0 && n146x >= 0 && !(!isKeyBorder && n4IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n146x, n45y, width, height, borderMap);
            }
            if (borderMap.find(n2) != borderMap.end() && borderMap[n2] == 0 && n123y >= 0&& !(!isKeyBorder && n2IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n27x, n123y, width, height, borderMap);
            }
            if (borderMap.find(n1) != borderMap.end() && borderMap[n1] == 0 && n146x >= 0 && n123y >= 0&& !(!isKeyBorder && n1IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n146x, n123y, width, height, borderMap);
            }
            if (borderMap.find(n7) != borderMap.end() && borderMap[n7] == 0 && n678y < height&& !(!isKeyBorder && n7IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n27x, n678y, width, height, borderMap);
            }
            if (borderMap.find(n5) != borderMap.end() && borderMap[n5] == 0 && n358x < width&& !(!isKeyBorder && n5IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n358x, n45y, width, height, borderMap);
            }
            if (borderMap.find(n3) != borderMap.end() && borderMap[n3] == 0 && n358x < width && n123y >= 0&& !(!isKeyBorder && n3IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n358x, n123y, width, height, borderMap);
            }
            if (borderMap.find(n8) != borderMap.end() && borderMap[n8] == 0 && n678y < height && n358x < width&& !(!isKeyBorder && n8IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n358x, n678y, width, height, borderMap);
            }
            if (borderMap.find(n6) != borderMap.end() && borderMap[n6] == 0 && n678y < height && n146x >= 0&& !(!isKeyBorder && n6IsBorder))
            {
                zoneLastBorder = false;
                LookNeighbour(n146x, n678y, width, height, borderMap);
            }
            if ((zoneLastBorder || (nBorderCount>=3 && nBorderCount<=5)) && !first)
                {m_zoneCount += 1;}
            
        }
    }

    std::pair<int, int> ZoneCounterImpl::FindTopLeftBorder(std::unordered_map<int, int> &borderMap, int width)
    {
        int smallestKey = borderMap.begin()->first;
        for (auto &i : borderMap)
        {
            if (i.first < smallestKey)
                smallestKey = i.first;
        }
        auto pair = std::make_pair(smallestKey % width, smallestKey / width);
        return pair;
    }

    ZoneCounterInterface *getZoneCounter()
    {
        return new ZoneCounterImpl();
    }

}