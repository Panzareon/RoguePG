#include "MapFillDungeon.h"

MapFillDungeon::MapFillDungeon(Map* map) : MapFill(map)
{
    //ctor
}

MapFillDungeon::~MapFillDungeon()
{
    //dtor
}
void MapFillDungeon::FillLayer(int LayerId)
{
    if(LayerId == 0)
    {
        FillBaseLayer(LayerId);
    }
    else
    {
        FillWithItems(LayerId);
    }
}
void MapFillDungeon::FillBaseLayer(int LayerId)
{
    FillLayerByTiles(Map::Space,LayerId,1,WithAdjacent);
    FillLayerByTiles(Map::Wall,LayerId,0,Simple);
}

void MapFillDungeon::FillWithItems(int LayerId)
{

}
