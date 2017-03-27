#ifndef MAPEVENTTILE_H
#define MAPEVENTTILE_H

#include "MapEvent.h"

#include <cereal/types/base_class.hpp>

class MapEventTile : public MapEvent
{
    public:
        MapEventTile();
        MapEventTile(bool needButton, int x, int y, bool walkableTile = true);
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime);
        virtual ~MapEventTile();

        sf::FloatRect GetPosition();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            float x = m_rect.left;
            float y = m_rect.top;
            float width = m_rect.width;
            float height = m_rect.height;
            archive(cereal::base_class<MapEvent>( this ), x, y, width, height, m_walkableTile);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            float x;
            float y;
            float width;
            float height;
            archive(cereal::base_class<MapEvent>( this ), x, y, width, height, m_walkableTile);
            m_rect.left = x;
            m_rect.top = y;
            m_rect.width = width;
            m_rect.height = height;
        }

    protected:
        sf::FloatRect m_rect;
        //does the Player need to stand on the Tile or only look at it
        bool m_walkableTile;

    private:
};

#endif // MAPEVENTTILE_H
