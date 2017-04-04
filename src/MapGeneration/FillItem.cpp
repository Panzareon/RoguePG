#include "MapGeneration/FillItem.h"
#include "MapGeneration/TileMap.h"

FillItem::FillItem()
{

}

FillItem::FillItem(int Item, int chance, int neededTile, int newTile, Type type, ItemSize size, PlacingRestriction restr)
{
    //ctor
    m_itemId = Item;
    m_chance = chance;
    m_size = size;
    m_type = type;
    m_restr = restr;
    m_placeAtTile = neededTile;
    m_insertType = newTile;
}

FillItem::~FillItem()
{
    //dtor
}
bool FillItem::CanInsertAt(Map* map, int x, int y, int LayerId, int LayerAboveHero, int LayerWallDecoration)
{
    if(x == map->m_startX && y == map->m_startY)
        return false;
    if(x == map->m_endX && y == map->m_endY)
        return false;
    if(map->GetTileType(x,y) != m_placeAtTile)
        return false;
    switch(m_size)
    {
        case AndOneAbove:
            if(map->GetTileId(x,y-1,LayerAboveHero) != 0)
                return false;
        case Single: case AboveHero:
            if(map->GetTileId(x,y,LayerId) != 0)
                return false;

        break;
        case AtWallSingle:
            if(map->GetTileId(x,y,LayerWallDecoration) != 0)
                return false;
            return true;

        break;
        case AtWallDouble:
            if(map->GetTileType(x,y+1) == m_placeAtTile)
                return false;
            if(map->GetTileId(x,y,LayerWallDecoration) != 0 || map->GetTileId(x,y-1,LayerWallDecoration) != 0)
                return false;
            return true;
        case BelowWallDouble:
            if(map->GetTileType(x,y-1) == m_placeAtTile)
                return false;
            if(map->GetTileId(x,y,LayerWallDecoration) != 0 || map->GetTileId(x,y+1,LayerWallDecoration) != 0)
                return false;
            return true;
    }
    int nrWalls = 0;
    for(int i = x - 1; i <= x + 1; i++)
    {
        for(int j = y - 1; j <= y +1; j++)
        {
            if(map->DoesCollide(i,j))
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

void FillItem::Insert(Map* map, int x, int y, int layerId, int layerAboveHero, int LayerWallDecoration)
{
    switch(m_size)
    {
        case Single:
            map->SetTileId(x,y,m_itemId,layerId);
            map->SetTileToType(x,y, m_insertType);
        break;
        case AboveHero:
            map->SetTileId(x,y,m_itemId,layerAboveHero);
            map->SetTileToType(x,y, m_insertType);
        break;
        case AndOneAbove:
            map->SetTileId(x,y,m_itemId,layerId);
            map->SetTileToType(x,y, m_insertType);
            map->SetTileId(x,y-1, m_itemId - TileMap::GetTileMapWith(), layerAboveHero);
        break;
        case AtWallSingle:
            map->SetTileId(x,y,m_itemId,LayerWallDecoration);
            map->SetTileToType(x,y, m_insertType);
        break;
        case AtWallDouble:
            map->SetTileId(x,y,m_itemId,layerId);
            map->SetTileToType(x,y, m_insertType);
            map->SetTileId(x,y-1, m_itemId - TileMap::GetTileMapWith(), LayerWallDecoration);

        break;
        case BelowWallDouble:
            map->SetTileId(x,y,m_itemId - TileMap::GetTileMapWith(),LayerWallDecoration);
            map->SetTileToType(x,y, m_insertType);
            map->SetTileId(x,y+1, m_itemId, LayerWallDecoration);


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
