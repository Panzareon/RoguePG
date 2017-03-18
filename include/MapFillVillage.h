#ifndef MAPFILLVILLAGE_H
#define MAPFILLVILLAGE_H

#include "MapFill.h"

class MapFillVillage : public MapFill
{
    public:
        enum TileType {Space, Wall, Street, BlockingItem, WalkthroughItem,Stairs ,TILE_TYPE_END};
        enum TileIndex{TileDoor, TileWallDecoration, TileRandomItem, TileStairsDown, TileSwordShop, TileShieldShop, TileInn, TileSpellShop, TileStaffShop, TILE_INDEX_END};
        MapFillVillage();
        virtual ~MapFillVillage();

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1);
    protected:
    private:
        void FillBaseLayer(int LayerId);
        void InitItemChances();
};

#endif // MAPFILLVILLAGE_H
