#ifndef MAPEVENTTILE_H
#define MAPEVENTTILE_H

#include <MapEvent.h>


class MapEventTile : public MapEvent
{
    public:
        MapEventTile(bool needButton, int x, int y, bool walkableTile = true);
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, sf::Time tickTime);
        virtual ~MapEventTile();

    protected:
        sf::FloatRect m_rect;
        //does the Player need to stand on the Tile or only look at it
        bool m_walkableTile;

    private:
};

#endif // MAPEVENTTILE_H
