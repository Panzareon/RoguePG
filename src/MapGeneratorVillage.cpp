#include "MapGeneratorVillage.h"
#include "MapFillVillage.h"

MapGeneratorVillage::MapGeneratorVillage(Map* map, unsigned int seed, MapFillVillage* mapFill)
{
    //ctor
    m_width = map->GetWidth();
    m_height = map->GetHeight();
    m_MGUtil.SetSize(m_width, m_height);
    m_map = map;
    m_map->AddCollidingType(MapFillVillage::Wall);
    m_map->AddCollidingType(MapFillVillage::BlockingItem);
    m_spaceBetweenHouses = 3;
    m_mapFill = mapFill;

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
    int doorX = x + 1 + rand() % (width - 2);
    m_mapFill->PlaceItemAt(1,2,4,MapFillVillage::TileDoor, doorX ,y + height - 1);
    m_doors.push_back(std::pair<int, int>(doorX, y + height));
    int nr = rand()%3 + 1;
    for(int i = 0; i < nr; i++)
    {
        m_mapFill->PlaceItemAt(1,2,4,MapFillVillage::TileWallDecoration, x + 1 + rand() % (width - 2),y + height - 1);
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

void MapGeneratorVillage::PlaceStreets()
{
    StartStreet(m_map->m_startX, m_map->m_startY, Enums::East);

    for(int i = 0; i < m_doors.size(); i++)
    {
        int minLength = m_width*m_height;
        int minDir = 0;
        for(int dir = 0; dir < 4; dir++)
        {
            int length = StartStreet(m_doors[i].first, m_doors[i].second, (Enums::Direction)dir, false);
            if(length < minLength && length != -1)
            {
                minDir = dir;
                minLength = length;
            }
        }
        StartStreet(m_doors[i].first, m_doors[i].second, (Enums::Direction)minDir);
    }
}

int MapGeneratorVillage::StartStreet(int xStart, int yStart, Enums::Direction dir, bool placeStreet)
{
    int nrStreets = 1;
    int x = xStart;
    int y = yStart;
    int xLast = xStart;
    int yLast = yStart;
    int type;
    if(m_map->GetTileType(x,y) == MapFillVillage::Space)
    {
        if(placeStreet)
            m_map->SetTileToType(x,y,MapFillVillage::Street);
    }
    while(x >= 0 && y >= 0 && x < m_width && y < m_height && nrStreets < m_width*m_height)
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

        type = m_map->GetTileType(x,y);
        if(type == MapFillVillage::Street)
        {
            break;
        }

        //Check if space for Street
        if(type == MapFillVillage::Space)
        {
            nrStreets++;
            if(placeStreet)
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

            type = m_map->GetTileType(x,y);
            if(type == MapFillVillage::Street)
            {
                break;
            }

            if(type == MapFillVillage::Space)
            {
                nrStreets++;
                if(placeStreet)
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

                type = m_map->GetTileType(x,y);
                if(type == MapFillVillage::Street)
                {
                    break;
                }
                if(type == MapFillVillage::Space)
                {
                    nrStreets++;
                    if(placeStreet)
                        m_map->SetTileToType(x,y,MapFillVillage::Street);
                }
            }
        }
        xLast = x;
        yLast = y;

    }
    if(x >= 0 && y >= 0 && x < m_width && y < m_height)
        return nrStreets;
    else
        return -1;
}

std::pair<int,int> MapGeneratorVillage::PopDoor()
{
    std::pair<int,int> pos = m_doors.at(m_doors.size() - 1);
    m_doors.resize(m_doors.size() - 1);
    return pos;
}
