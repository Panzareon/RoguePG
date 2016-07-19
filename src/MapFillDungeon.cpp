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
    //Defining all Items for Layer 0
    //Small Rock
    m_chanceForTile[0].push_back(FillItem(512,50));
    //Small Stones
    m_chanceForTile[0].push_back(FillItem(544,40,FillItem::Walkable));
    //Small wide Rock
    m_chanceForTile[0].push_back(FillItem(576,50));
    //Tall Rock
    m_chanceForTile[0].push_back(FillItem(640,50,FillItem::Blocking,FillItem::AndOneAbove));
    //Small Crack
    m_chanceForTile[0].push_back(FillItem(546,20,FillItem::Wall,FillItem::AtWallDouble));
    //Medium Crack
    m_chanceForTile[0].push_back(FillItem(547,20,FillItem::Wall,FillItem::AtWallDouble));
    //Wide Crack
    m_chanceForTile[0].push_back(FillItem(548,5,FillItem::Wall,FillItem::AtWallDouble));
    //Brown Plant
    m_chanceForTile[0].push_back(FillItem(549,20,FillItem::Wall,FillItem::AtWallDouble));
    //Green Plants
    m_chanceForTile[0].push_back(FillItem(550,20,FillItem::Wall,FillItem::AtWallDouble));
    m_chanceForTile[0].push_back(FillItem(551,20,FillItem::Wall,FillItem::AtWallDouble));
    //Cracked Barrel
    m_chanceForTile[0].push_back(FillItem(578,50,FillItem::Blocking,FillItem::Single, FillItem::AtWall));
    //Cracked Pot
    m_chanceForTile[0].push_back(FillItem(579,50,FillItem::Blocking,FillItem::Single, FillItem::AtWall));
}


void MapFillDungeon::FillLayer(int LayerId, int LayerAboveHeroId)
{
    if(LayerId == 0)
    {
        FillBaseLayer(LayerId);
    }
    else if(LayerId == 1)
    {
        //Fill Wall Tiles
        FillLayerWallByTiles(Map::Space,LayerId, 256,2);
    }
    else if(LayerId == 4)
    {
        //Fill Tiles above Wall
        FillLayerWallAbove(Map::Space, LayerId, 288,2);
    }
    else
    {
        //Nr of items to Place: Width of Map times Height of Map / 50
        FillWithItems(LayerId, LayerAboveHeroId, 0, m_width * m_height / 50);
    }
}
void MapFillDungeon::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Map::Space,LayerId,1,WithAdjacent);
    FillLayerByTiles(Map::Wall,LayerId,0,Simple);
}

