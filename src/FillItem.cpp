#include "FillItem.h"
#include "TileMap.h"

FillItem::FillItem(int Item, int chance, Type type, ItemSize size, PlacingRestriction restr)
{
    //ctor
    m_itemId = Item;
    m_chance = chance;
    m_size = size;
    m_type = type;
    m_restr = restr;
}

FillItem::~FillItem()
{
    //dtor
}
bool FillItem::CanInsertAt(Map* map, int x, int y, int LayerId, int LayerAboveHero)
{
    if(x == map->m_startX && y == map->m_startY)
        return false;
    switch(m_size)
    {
        case AndOneAbove:
            if(map->GetTileId(x,y-1,LayerAboveHero) != 0)
                return false;
        case Single: case AboveHero:
            if(map->GetTileType(x,y) != Map::Space)
                return false;
            if(map->GetTileId(x,y,LayerId) != 0)
                return false;

        break;
        case AtWallDouble:
            if(map->GetTileType(x,y) != Map::Wall || map->GetTileType(x,y+1) == Map::Wall)
                return false;
            if(map->GetTileId(x,y,LayerAboveHero) != 0 || map->GetTileId(x,y-1,LayerAboveHero) != 0)
                return false;
            return true;
    }
    int nrWalls = 0;
    for(int i = x - 1; i <= x + 1; i++)
    {
        for(int j = y - 1; j <= y +1; j++)
        {
            if(map->GetTileType(i,j) == Map::Wall)
                nrWalls++;
        }
    }
    switch(m_restr)
    {
        case None:
            return true;
        case Default:
            return nrWalls >= 3 || nrWalls == 0;
        case AtWall:
            return nrWalls >= 3;
    }
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
        case AtWallDouble:
            map->SetTileId(x,y,m_itemId,layerAboveHero);
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


