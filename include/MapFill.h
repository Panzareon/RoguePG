#ifndef MAPFILL_H
#define MAPFILL_H

#include "Map.h"
#include "MapGeneratorUtil.h"
#include <vector>
#include "FillItem.h"

//Set TileMap Id in Map
class MapFill
{
    public:

        MapFill(Map* map);
        virtual ~MapFill();

        virtual void FillLayer(int LayerId, int LayerAboveHeroId = -1) = 0;


    protected:
        enum FillType {Simple, WithAdjacent};
        Map* m_map;

        std::vector<std::vector<FillItem> > m_chanceForTile;

        int m_width;
        int m_height;

        int m_maxTries;
        MapGeneratorUtil m_MGUtil;

        bool CanBlockBeFilled(int x, int y);

        void FillLayerByTiles(Map::TileType checkTile, int LayerId, int TileId, FillType fillType);
        //index of m_chanceForTile
        void FillWithItems(int LayerId, int LayerAboveHeroId, int index);
    private:
};

#endif // MAPFILL_H
