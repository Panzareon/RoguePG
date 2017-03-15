#ifndef MAPEVENTDUNGEONENTRANCE_H
#define MAPEVENTDUNGEONENTRANCE_H

#include "MapEventTile.h"

class MapEventDungeonEntrance : public MapEventTile
{
    public:
        MapEventDungeonEntrance(int x, int y);
        virtual ~MapEventDungeonEntrance();

        void Activate();

    protected:

    private:
};

#endif // MAPEVENTDUNGEONENTRANCE_H
