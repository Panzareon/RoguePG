#include "MapEventStairs.h"
#include "GameController.h"
#include "TileMap.h"

MapEventStairs::MapEventStairs(bool next, int x, int y) : MapEvent(true)
{
    //ctor
    m_next = next;
    m_rect.left = x * TileMap::GetTileWith();
    m_rect.top = y * TileMap::GetTileWith();
    m_rect.width = TileMap::GetTileWith();
    m_rect.height = TileMap::GetTileWith();
}

MapEventStairs::~MapEventStairs()
{
    //dtor
}

bool MapEventStairs::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection)
{
    if(rect.intersects(m_rect))
    {
         return true;
    }
    return false;
}

void MapEventStairs::Activate()
{
    GameController* controller = GameController::getInstance();
    if(m_next)
    {
        //go to next Level
        controller->GotoNextLevel();
    }
    else
    {
        //go to previous level
        controller->GotoPreviousLevel();
    }
}
