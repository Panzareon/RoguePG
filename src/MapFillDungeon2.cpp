#include "MapFillDungeon2.h"

MapFillDungeon2::MapFillDungeon2()
{
    //ctor
}

MapFillDungeon2::~MapFillDungeon2()
{
    //dtor
}

void MapFillDungeon2::InitItemChances()
{
    //Stairs back up
    m_chanceForTile[TileStairsUp].push_back(FillItem(896 , 1, Space, Stairs, FillItem::Walkable));
    //Stairs further down
    m_chanceForTile[TileStairsDown].push_back(FillItem(897 , 1, Space, Stairs, FillItem::Walkable));
    //Defining all Items for Layer 0
    //Small Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(513,50, Space, BlockingItem));
    //Small Stones
    m_chanceForTile[TileRandomItem].push_back(FillItem(545,40, Space, WalkthroughItem,FillItem::Walkable));
    //Small wide Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(577,50, Space, BlockingItem));
    //Tall Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(641,50, Space, BlockingItem,FillItem::Blocking,FillItem::AndOneAbove));
    //Small Crack
    m_chanceForTile[TileRandomItem].push_back(FillItem(546,30, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Medium Crack
    m_chanceForTile[TileRandomItem].push_back(FillItem(547,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Wide Crack
    m_chanceForTile[TileRandomItem].push_back(FillItem(548,5, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Brown Plant
    m_chanceForTile[TileRandomItem].push_back(FillItem(549,10, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Green Plants
    m_chanceForTile[TileRandomItem].push_back(FillItem(550,5, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    m_chanceForTile[TileRandomItem].push_back(FillItem(551,5, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Cracked Barrel
    m_chanceForTile[TileRandomItem].push_back(FillItem(578,50, Space, BlockingItem,FillItem::Blocking,FillItem::Single, FillItem::AtWall));
    //Cracked Pot
    m_chanceForTile[TileRandomItem].push_back(FillItem(579,50, Space, BlockingItem,FillItem::Blocking,FillItem::Single, FillItem::AtWall));

    //Chest
    m_chanceForTile[TileChest].push_back(FillItem(928,1, Space, BlockingItem,FillItem::Blocking,FillItem::Single, FillItem::AtWall));

}


void MapFillDungeon2::FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId, int LayerWallDecoration)
{
    if(type == MapFill::Ground)
    {
        FillBaseLayer(LayerId);
    }
    else if(type == MapFill::Wall)
    {
        //Fill Wall Tiles
        FillLayerWallByTiles(Wall ,LayerId, LayerAboveHeroId, 268,2);
    }
    else if(type == MapFill::WallTopping)
    {
        //Fill Tiles above Wall
        FillLayerWallAbove(Wall, LayerId, 293,2);
    }
    else
    {
        //Nr of items to Place: Width of Map times Height of Map / 50
        FillWithItems(LayerId, LayerAboveHeroId,LayerWallDecoration , MapFillDungeon::TileRandomItem, m_width * m_height / 20);
    }
}

void MapFillDungeon2::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Space,LayerId,11,WithAdjacent);
    FillLayerByTiles(Wall,LayerId,0,Simple);
}
