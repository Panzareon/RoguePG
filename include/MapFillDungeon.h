#ifndef MAPFILLDUNGEON_H
#define MAPFILLDUNGEON_H

#include <MapFill.h>


class MapFillDungeon : public MapFill
{
    public:
        enum TileType {Wall, Space, InteractableWall, BlockingItem, WalkthroughItem, Stairs, TILE_TYPE_END};
        enum TileIndex{TileStairsUp, TileStairsDown, TileRandomItem, TileChest, TILE_INDEX_END};
        MapFillDungeon();
        virtual ~MapFillDungeon();

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1);
        virtual void InitItemChances();
    protected:
        virtual void FillBaseLayer(int LayerId);
    private:
};

#endif // MAPFILLDUNGEON_H
