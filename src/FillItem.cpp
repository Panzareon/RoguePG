#include "FillItem.h"
#include "TileMap.h"

FillItem::FillItem(int Item, int chance, Type type, ItemSize size)
{
    //ctor
    m_itemId = Item;
    m_chance = chance;
    m_size = size;
    m_type = type;
}

FillItem::~FillItem()
{
    //dtor
}
bool FillItem::CanInsertAt(Map* map, int x, int y)
{
    //Todo: e.g. for Chests: check if at a Wall
    int nrWalls = 0;
    for(int i = x - 1; i <= x + 1; i++)
    {
        for(int j = y - 1; j <= y +1; j++)
        {
            if(map->GetTileType(i,j) == Map::Wall)
                nrWalls++;
        }
    }
    return nrWalls >= 3 || nrWalls == 0;
}

void FillItem::Insert(Map* map, int x, int y, int layerId, int layerAboveHero)
{
    switch(m_size)
    {
        case Single:
            map->SetTileId(x,y,m_itemId,layerId);
            if(m_type == Blocking)
                map->SetTileToType(x,y, Map::BlockingItem);
        break;
        case AboveHero:
            map->SetTileId(x,y,m_itemId,layerAboveHero);
            if(m_type == Blocking)
                map->SetTileToType(x,y, Map::BlockingItem);
        break;
        case AndOneAbove:
            map->SetTileId(x,y,m_itemId,layerId);
            if(m_type == Blocking)
                map->SetTileToType(x,y, Map::BlockingItem);
            map->SetTileId(x,y-1, m_itemId - TileMap::GetTileMapWith(), layerAboveHero);

    }
}

int FillItem::GetChance()
{
    return m_chance;
}

FillItem::Type FillItem::GetType()
{
    return m_type;
}


