#include "MapEventTile.h"
#include "TileMap.h"

MapEventTile::MapEventTile(bool needButton, int x, int y, bool walkableTile) : MapEvent(needButton)
{
    //ctor
    m_rect.left = x * TileMap::GetTileWith();
    m_rect.top = y * TileMap::GetTileWith();
    m_rect.width = TileMap::GetTileWith();
    m_rect.height = TileMap::GetTileWith();
    m_walkableTile = walkableTile;
}

MapEventTile::~MapEventTile()
{
    //dtor
}

bool MapEventTile::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime)
{
    if(!m_walkableTile)
    {
        switch(lookingDirection)
        {
        case Enums::East:
            rect.left += TileMap::GetTileWith();
            break;
        case Enums::West:
            rect.left -= TileMap::GetTileWith();
            break;
        case Enums::North:
            rect.top -= TileMap::GetTileWith();
            break;
        case Enums::South:
            rect.top += TileMap::GetTileWith();
            break;
        }
    }
    if(rect.intersects(m_rect))
    {
         return true;
    }
    return false;
}
