#ifndef MAPFILLDUNGEON_H
#define MAPFILLDUNGEON_H

#include <MapFill.h>


class MapFillDungeon : public MapFill
{
    public:
        MapFillDungeon(Map* map);
        virtual ~MapFillDungeon();

        virtual void FillLayer(int LayerId, int LayerAboveHeroId = 0);
    protected:
    private:
        void FillBaseLayer(int LayerId);
        void InitItemChances();
};

#endif // MAPFILLDUNGEON_H
