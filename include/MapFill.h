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
        enum ToFillLayer{Ground, Wall, WallTopping, AdditionalItems};
        enum TileIndex{TileStairsUp, TileStairsDown, TileRandomItem, TileChest, TILE_INDEX_END};
        MapFill();
        virtual ~MapFill();

        void SetMap(Map* map);

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1) = 0;


        //Place item of layer at position x,y
        bool PlaceItemAt(int LayerId, int LayerAboveHeroId, int LayerWallDecoration, TileIndex index, int x, int y, bool checkPlacement = true);
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
        void FillLayerWallByTiles(Map::TileType checkTile, int LayerId, int LayerAboveHeroId, int TileId, int wallHeight);
        void FillLayerWallAbove(Map::TileType checkTile, int LayerId, int TileId, int wallHeight);
        //index of m_chanceForTile
        void FillWithItems(int LayerId, int LayerAboveHeroId, int LayerWallDecoration, TileIndex index, int NrItems);
    private:
};

#endif // MAPFILL_H
