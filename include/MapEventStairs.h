#ifndef MAPEVENTSTAIRS_H
#define MAPEVENTSTAIRS_H

#include "MapEvent.h"


class MapEventStairs : public MapEvent
{
    public:
        MapEventStairs(bool next, int x, int y);
        virtual ~MapEventStairs();
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection);
        virtual void Activate();

    protected:

    private:
        bool m_next;
        sf::FloatRect m_rect;
};

#endif // MAPEVENTSTAIRS_H
