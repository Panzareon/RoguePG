#include "MapGeneration/MapEventTile.h"
#include "MapGeneration/TileMap.h"

MapEventTile::MapEventTile()
{

}


MapEventTile::MapEventTile(bool needButton, int x, int y, bool walkableTile) : MapEvent(needButton)
{
    //ctor
    m_rect.left = x * TileMap::GetTileWidth();
    m_rect.top = y * TileMap::GetTileWidth();
    m_rect.width = TileMap::GetTileWidth();
    m_rect.height = TileMap::GetTileWidth();
    m_walkableTile = walkableTile;
}

MapEventTile::~MapEventTile()
{
    //dtor
}

sf::FloatRect MapEventTile::GetPosition()
{
    return m_rect;
}

bool MapEventTile::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime)
{
    if(!m_walkableTile)
    {
        switch(lookingDirection)
        {
        case Enums::Direction::East:
            rect.left += TileMap::GetTileWidth();
            break;
        case Enums::Direction::West:
            rect.left -= TileMap::GetTileWidth();
            break;
        case Enums::Direction::North:
            rect.top -= TileMap::GetTileWidth();
            break;
        case Enums::Direction::South:
            rect.top += TileMap::GetTileWidth();
            break;
        }
    }
    if(rect.intersects(m_rect))
    {
         return true;
    }
    return false;
}
