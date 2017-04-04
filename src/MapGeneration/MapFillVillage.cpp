#include "MapGeneration/MapFillVillage.h"

MapFillVillage::MapFillVillage()
{
    //ctor
    m_chanceForTile.resize(TILE_INDEX_END);
    InitItemChances();
    m_defaultType = Space;
}

MapFillVillage::~MapFillVillage()
{
    //dtor
}

void MapFillVillage::InitItemChances()
{
    //Door
    m_chanceForTile[TileDoor].push_back(FillItem(560,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Stairs further down
    m_chanceForTile[TileStairsDown].push_back(FillItem(897 , 1, Space, Stairs, FillItem::Walkable));
    //Tree
    m_chanceForTile[TileRandomItem].push_back(FillItem(561,20, Space, BlockingItem,FillItem::Blocking,FillItem::AndOneAbove));
    //Closed small window
    m_chanceForTile[TileWallDecoration].push_back(FillItem(562,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Open small window
    m_chanceForTile[TileWallDecoration].push_back(FillItem(563,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Closed big window
    m_chanceForTile[TileWallDecoration].push_back(FillItem(564,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //Open big window
    m_chanceForTile[TileWallDecoration].push_back(FillItem(565,20, Wall, Wall,FillItem::Wall,FillItem::AtWallDouble));
    //small flowers
    m_chanceForTile[TileRandomItem].push_back(FillItem(592,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(593,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(594,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(595,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(596,20, Space, BlockingItem));
    m_chanceForTile[TileRandomItem].push_back(FillItem(597,20, Space, BlockingItem));
    m_chanceForTile[TileRandomItem].push_back(FillItem(624,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(625,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(626,20, Space, WalkthroughItem, FillItem::Walkable));
    m_chanceForTile[TileRandomItem].push_back(FillItem(627,20, Space, BlockingItem));
    m_chanceForTile[TileRandomItem].push_back(FillItem(628,20, Space, BlockingItem));
    //Shop Signs
    m_chanceForTile[TileSwordShop].push_back(FillItem(656,20, Wall, Wall,FillItem::Wall,FillItem::AtWallSingle));
    m_chanceForTile[TileShieldShop].push_back(FillItem(657,20, Wall, Wall,FillItem::Wall,FillItem::AtWallSingle));
    m_chanceForTile[TileInn].push_back(FillItem(658,20, Wall, Wall,FillItem::Wall,FillItem::AtWallSingle));
    m_chanceForTile[TileSpellShop].push_back(FillItem(659,20, Wall, Wall,FillItem::Wall,FillItem::AtWallSingle));
    m_chanceForTile[TileStaffShop].push_back(FillItem(660,20, Wall, Wall,FillItem::Wall,FillItem::AtWallSingle));

}

void MapFillVillage::FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId, int LayerWallDecoration)
{
    if(type == MapFill::Ground)
    {
        FillBaseLayer(LayerId);
    }
    else if(type == MapFill::Wall)
    {
        //Fill Wall Tiles
        FillLayerWallByTiles(Wall,LayerId, LayerAboveHeroId, 260,3);
    }
    else if(type == MapFill::WallTopping)
    {
        //Fill Tiles above Wall
        FillLayerWallByTiles(Wall, LayerId, LayerId, 264,2,4);
    }
    else if(type == MapFill::AdditionalItems)
    {
        //Nr of items to Place: Width of Map times Height of Map / 50
        FillWithItems(LayerId, LayerAboveHeroId,LayerWallDecoration , TileRandomItem, m_width * m_height / 20);
    }
    else if(type == MapFill::WallBelow)
    {
        FillLayerWallBelow(Wall, LayerId,268 ,2);
    }
}
void MapFillVillage::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Space,LayerId,6,WithAdjacent);
    FillLayerByTiles(Street,LayerId,1,WithAdjacent);
    FillLayerByTiles(Wall,LayerId,0,Simple);
}
