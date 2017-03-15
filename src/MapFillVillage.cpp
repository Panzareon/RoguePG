#include "MapFillVillage.h"

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
    else
    {
        //Nr of items to Place: Width of Map times Height of Map / 50
        //FillWithItems(LayerId, LayerAboveHeroId,LayerWallDecoration , MapFill::TileRandomItem, m_width * m_height / 20);
    }
}
void MapFillVillage::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Space,LayerId,6,WithAdjacent);
    FillLayerByTiles(Street,LayerId,1,WithAdjacent);
    FillLayerByTiles(Wall,LayerId,0,Simple);
}
