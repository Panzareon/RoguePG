#ifndef MAPFILLDUNGEON_H
#define MAPFILLDUNGEON_H

#include <MapFill.h>


class MapFillDungeon : public MapFill
{
    public:
        MapFillDungeon(Map* map);
        virtual ~MapFillDungeon();

        virtual void FillLayer(int LayerId);
    protected:
    private:
        void FillBaseLayer(int LayerId);
        void FillWithItems(int LayerId);
};

#endif // MAPFILLDUNGEON_H
