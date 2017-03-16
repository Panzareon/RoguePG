#ifndef MAPFILLDUNGEON2_H
#define MAPFILLDUNGEON2_H

#include "MapFillDungeon.h"

class MapFillDungeon2 : public MapFillDungeon
{
    public:
        MapFillDungeon2();
        virtual ~MapFillDungeon2();

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1);
        virtual void InitItemChances();
    protected:
        virtual void FillBaseLayer(int LayerId);

    private:
};

#endif // MAPFILLDUNGEON2_H
