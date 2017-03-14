#include "MapFillVillage.h"

MapFillVillage::MapFillVillage()
{
    //ctor
    m_chanceForTile.resize(TILE_INDEX_END);
    InitItemChances();
    m_defaultType = Map::Space;
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
    if(type == Ground)
    {
        FillBaseLayer(LayerId);
    }
    else if(type == Wall)
    {
        //Fill Wall Tiles
        FillLayerWallByTiles(Map::Space,LayerId, LayerAboveHeroId, 260,2);
    }
    else if(type == WallTopping)
    {
        //Fill Tiles above Wall
        FillLayerWallByTiles(Map::Space, LayerId, LayerId, 264,2,3);
    }
    else
    {
        //Nr of items to Place: Width of Map times Height of Map / 50
        //FillWithItems(LayerId, LayerAboveHeroId,LayerWallDecoration , MapFill::TileRandomItem, m_width * m_height / 20);
    }
}
void MapFillVillage::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Map::Space,LayerId,6,WithAdjacent);
    FillLayerByTiles(Map::Wall,LayerId,0,Simple);
}
