#ifndef MAPFILLVILLAGE_H
#define MAPFILLVILLAGE_H

#include "MapFill.h"

class MapFillVillage : public MapFill
{
    public:
        enum TileType {Wall, Space, Street};
        MapFillVillage();
        virtual ~MapFillVillage();

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1);
    protected:
    private:
        void FillBaseLayer(int LayerId);
        void InitItemChances();
};

#endif // MAPFILLVILLAGE_H
