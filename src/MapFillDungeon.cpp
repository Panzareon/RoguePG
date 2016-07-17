#include "MapFillDungeon.h"

MapFillDungeon::MapFillDungeon(Map* map) : MapFill(map)
{
    //ctor
    m_chanceForTile.resize(1);
    InitItemChances();
}

MapFillDungeon::~MapFillDungeon()
{
    //dtor
}
void MapFillDungeon::InitItemChances()
{
    m_chanceForTile[0].push_back(FillItem(512,5));
    m_chanceForTile[0].push_back(FillItem(544,5,FillItem::Walkable));
    m_chanceForTile[0].push_back(FillItem(576,5));
    m_chanceForTile[0].push_back(FillItem(640,5,FillItem::Blocking,FillItem::AndOneAbove));
}


void MapFillDungeon::FillLayer(int LayerId, int LayerAboveHeroId)
{
    if(LayerId == 0)
    {
        FillBaseLayer(LayerId);
    }
    else
    {
        FillWithItems(LayerId, LayerAboveHeroId, 0);
    }
}
void MapFillDungeon::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Map::Space,LayerId,1,WithAdjacent);
    FillLayerByTiles(Map::Wall,LayerId,0,Simple);
}

