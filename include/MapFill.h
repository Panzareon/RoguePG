#ifndef MAPFILL_H
#define MAPFILL_H

#include "Map.h"
#include "MapGeneratorUtil.h"

//Set TileMap Id in Map
class MapFill
{
    public:

        MapFill(Map* map);
        virtual ~MapFill();

        virtual void FillLayer(int LayerId) = 0;


    protected:
        enum FillType {Simple, WithAdjacent};
        Map* m_map;

        int m_width;
        int m_height;

        MapGeneratorUtil m_MGUtil;

        void FillLayerByTiles(Map::TileType checkTile, int LayerId, int TileId, FillType fillType);
    private:
};

#endif // MAPFILL_H
