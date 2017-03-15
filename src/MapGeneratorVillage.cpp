#include "MapGeneratorVillage.h"
#include "MapFillVillage.h"

MapGeneratorVillage::MapGeneratorVillage(Map* map, unsigned int seed)
{
    //ctor
    m_width = map->GetWidth();
    m_height = map->GetHeight();
    m_MGUtil.SetSize(m_width, m_height);
    m_map = map;
    m_map->AddCollidingType(MapFillVillage::Wall);
    m_spaceBetweenHouses = 3;

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
            m_map->SetTileToType(i,j,MapFillVillage::Space);
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
            m_map->SetTileToType(i,j,MapFillVillage::Wall);
        }
    }
}

bool MapGeneratorVillage::IsRoomFree(int x, int y, int width, int height)
{
    for(int i = x - m_spaceBetweenHouses; i < x + width + m_spaceBetweenHouses; i++)
    {
        for(int j = y - m_spaceBetweenHouses; j < y + height + m_spaceBetweenHouses; j++)
        {
            if(i >= 0 && i < m_width && j >= 0 && j < m_height && m_map->IsTileWall(i,j))
                return false;
            if(i == m_map->m_startX && j == m_map->m_startY)
                return false;
        }
    }
    return true;
}

void MapGeneratorVillage::StartStreet(int xStart, int yStart, Enums::Direction dir)
{
    int x = xStart;
    int y = yStart;
    int xLast,yLast;
    if(m_map->GetTileType(x,y) == MapFillVillage::Space)
    {
        m_map->SetTileToType(x,y,MapFillVillage::Street);
    }
    while(x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
        switch(dir)
        {
        case Enums::East:
            x++;
            break;
        case Enums::West:
            x--;
            break;
        case Enums::North:
            y--;
            break;
        case Enums::South:
            y++;
            break;
        }

        //Check if space for Street
        if(m_map->GetTileType(x,y) == MapFillVillage::Space)
        {
            m_map->SetTileToType(x,y,MapFillVillage::Street);
        }
        else if(x >= 0 && y >= 0 && x < m_width && y < m_height)
        {
            //If not check for Space 90° in one direction
            x = xLast;
            y = yLast;
            switch(dir)
            {
            case Enums::East:
                y++;
                break;
            case Enums::West:
                y--;
                break;
            case Enums::North:
                x--;
                break;
            case Enums::South:
                x++;
                break;
            }

            if(m_map->GetTileType(x,y) == MapFillVillage::Space)
            {
                m_map->SetTileToType(x,y,MapFillVillage::Street);
            }
            else if(x >= 0 && y >= 0 && x < m_width && y < m_height)
            {
                //If there is no space check for Space 90° in the other direction
                x = xLast;
                y = yLast;
                switch(dir)
                {
                case Enums::East:
                    y++;
                    break;
                case Enums::West:
                    y--;
                    break;
                case Enums::North:
                    x--;
                    break;
                case Enums::South:
                    x++;
                    break;
                }

                if(m_map->GetTileType(x,y) == MapFillVillage::Space)
                {
                    m_map->SetTileToType(x,y,MapFillVillage::Street);
                }
            }
        }
        xLast = x;
        yLast = y;

    }
}

