#include "MapFillIceDungeon.h"

MapFillIceDungeon::MapFillIceDungeon()
{
    //ctor
}

MapFillIceDungeon::~MapFillIceDungeon()
{
    //dtor
}

void MapFillIceDungeon::InitItemChances(bool wallAbove)
{
    //Stairs back up
    m_chanceForTile[TileStairsUp].push_back(FillItem(896 , 1, Space, Stairs, FillItem::Walkable));
    //Stairs further down
    m_chanceForTile[TileStairsDown].push_back(FillItem(897 , 1, Space, Stairs, FillItem::Walkable));
    //Defining all Items for Layer 0
    //Small Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(513,30, Space, BlockingItem));
    //Small Stones
    m_chanceForTile[TileRandomItem].push_back(FillItem(545,20, Space, WalkthroughItem,FillItem::Walkable));
    //Small Snowy Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(520,50, Space, BlockingItem));
    //Small Snowy Stones
    m_chanceForTile[TileRandomItem].push_back(FillItem(552,40, Space, WalkthroughItem,FillItem::Walkable));
    //Small wide Snowy Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(584,50, Space, BlockingItem));
    //Tall Snowy Rock
    m_chanceForTile[TileRandomItem].push_back(FillItem(648,50, Space, BlockingItem,FillItem::Blocking,FillItem::AndOneAbove));
    //Snowy Barrel
    m_chanceForTile[TileRandomItem].push_back(FillItem(580,30, Space, BlockingItem,FillItem::Blocking,FillItem::Single, FillItem::AtWall));
    //Snowy Pillar base
    m_chanceForTile[TileRandomItem].push_back(FillItem(610,10, Space, BlockingItem));
    //Snowy hole
    m_chanceForTile[TileRandomItem].push_back(FillItem(581,20, Space, BlockingItem));
    //Crystal
    m_chanceForTile[TileRandomItem].push_back(FillItem(582,30, Space, BlockingItem));
    //Snowy Stones
    m_chanceForTile[TileRandomItem].push_back(FillItem(583,50, Space, BlockingItem));

    //Chest
    m_chanceForTile[TileChest].push_back(FillItem(928,1, Space, BlockingItem,FillItem::Blocking,FillItem::Single, FillItem::AtWall));

    InitBaseItemChances(wallAbove);
}


void MapFillIceDungeon::FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId, int LayerWallDecoration)
{
    if(type == MapFill::Ground)
    {
        FillBaseLayer(LayerId);
    }
    else if(type == MapFill::Wall)
    {
        //Fill Wall Tiles
        FillLayerWallByTiles(Wall ,LayerId, LayerAboveHeroId, 272,2);
    }
    else if(type == MapFill::WallTopping)
    {
        //Fill Tiles above Wall
        FillLayerWallAbove(Wall, LayerId, 293,2);
    }
    else if(type == MapFill::AdditionalItems)
    {
        //Nr of items to Place: Width of Map times Height of Map / 50
        FillWithItems(LayerId, LayerAboveHeroId,LayerWallDecoration , MapFillDungeon::TileRandomItem, m_width * m_height / 20);
    }
    else if(type == MapFill::WallBelow)
    {
        FillLayerWallBelow(Wall, LayerId,272 ,3);
    }
}

void MapFillIceDungeon::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Space,LayerId,16,WithAdjacent);
    FillLayerByTiles(Wall,LayerId,0,Simple);
}

void MapFillIceDungeon::InitBaseItemChances(bool wallAbove)
{
    if(wallAbove)
    {
        //Small Crack
        m_chanceForTile[TileRandomItem].push_back(FillItem(546,30, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
        //Medium Crack
        m_chanceForTile[TileRandomItem].push_back(FillItem(547,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    }
    else
    {
        //Small Crack
        m_chanceForTile[TileRandomItem].push_back(FillItem(546,30, Wall, Wall,FillItem::Wall,FillItem::BelowWallDouble));
        //Medium Crack
        m_chanceForTile[TileRandomItem].push_back(FillItem(547,20, Wall, Wall,FillItem::Wall,FillItem::BelowWallDouble));
    }
}
