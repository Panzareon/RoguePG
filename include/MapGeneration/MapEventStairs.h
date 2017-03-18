#ifndef MAPEVENTSTAIRS_H
#define MAPEVENTSTAIRS_H

#include "MapEventTile.h"


class MapEventStairs : public MapEventTile
{
    public:
        MapEventStairs(bool next, int x, int y);
        virtual ~MapEventStairs();
        virtual void Activate();

    protected:

    private:
        bool m_next;
};

#endif // MAPEVENTSTAIRS_H
