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
        enum ToFillLayer{Ground, Wall, WallTopping, AdditionalItems, WallBelow};
        MapFill();
        virtual ~MapFill();

        void SetMap(Map* map);

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1) = 0;


        //Place item of layer at position x,y
        bool PlaceItemAt(int LayerId, int LayerAboveHeroId, int LayerWallDecoration, int index, int x, int y, bool checkPlacement = true);

        template<class Archive>
        void serialize(Archive & archive, std::uint32_t const version)
        {
            archive(m_chanceForTile);
        }
    protected:
        int m_defaultType;
        enum FillType {Simple, WithAdjacent};
        Map* m_map;

        std::vector<std::vector<FillItem> > m_chanceForTile;

        int m_width;
        int m_height;

        int m_maxTries;
        MapGeneratorUtil m_MGUtil;

        bool CanBlockBeFilled(int x, int y);

        void FillLayerByTiles(int checkTile, int LayerId, int TileId, FillType fillType);
        //yDelta changes the y position of the wall to be displayed
        void FillLayerWallByTiles(int checkTile, int LayerId, int LayerAboveHeroId, int TileId, int wallHeight, int yDelta = 1);
        void FillLayerWallAbove(int checkTile, int LayerId, int TileId, int wallHeight);
        void FillLayerWallBelow(int checkTile, int LayerId, int TileId, int wallHeight, int yDelta = 1);
        //index of m_chanceForTile
        void FillWithItems(int LayerId, int LayerAboveHeroId, int LayerWallDecoration, int index, int NrItems);
    private:
};

#endif // MAPFILL_H
