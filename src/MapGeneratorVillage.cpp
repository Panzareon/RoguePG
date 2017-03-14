#include "MapGeneratorVillage.h"

MapGeneratorVillage::MapGeneratorVillage(Map* map, unsigned int seed)
{
    //ctor
    m_width = map->GetWidth();
    m_height = map->GetHeight();
    m_MGUtil.SetSize(m_width, m_height);
    m_map = map;

    if(seed == 0)
        std::srand(std::time(0));
    else
        std::srand(seed);
}

MapGeneratorVillage::~MapGeneratorVillage()
{
    //dtor
}

void MapGeneratorVillage::PlaceHouses(int houseWidth, int houseHeight, int nrHouses)
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            m_map->SetTileToSpace(i,j);
        }
    }

    for(int i = 0; i < nrHouses; i++)
    {
        int x,y;
        int nrTries = 0;
        do
        {
            x = rand() % (m_width - houseWidth);
            y = rand() % (m_height - houseHeight);
            nrTries++;
        }
        while (!IsRoomFree(x,y,houseWidth, houseHeight) && nrTries < 100);
        if(nrTries >= 100)
            break;
        AddHouse(x,y,houseWidth, houseHeight);
    }
}


void MapGeneratorVillage::AddHouse(int x, int y, int width, int height)
{
    for(int i = x; i < x + width; i++)
    {
        for(int j = y; j < y + height; j++)
        {
            m_map->SetTileToWall(i,j);
        }
    }
}

bool MapGeneratorVillage::IsRoomFree(int x, int y, int width, int height)
{
    for(int i = x - 1; i < x + width + 1; i++)
    {
        for(int j = y - 1; j < y + height + 1; j++)
        {
            if(i >= 0 && i < m_width && j >= 0 && j < m_height && m_map->IsTileWall(i,j))
                return false;
        }
    }
    return true;
}
