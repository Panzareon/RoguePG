#ifndef MAPEVENTCHEST_H
#define MAPEVENTCHEST_H

#include "MapEventTile.h"


class MapEventChest : public MapEventTile
{
    public:
        MapEventChest(int x, int y);
        virtual ~MapEventChest();
        virtual void Activate();

    protected:

    private:
};

#endif // MAPEVENTCHEST_H
