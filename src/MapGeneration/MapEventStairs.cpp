#include "MapGeneration/MapEventStairs.h"
#include "Controller/GameController.h"

MapEventStairs::MapEventStairs()
{
    //ctor
}

MapEventStairs::MapEventStairs(bool next, int x, int y) : MapEventTile(true,x,y)
{
    //ctor
    m_next = next;
}

MapEventStairs::~MapEventStairs()
{
    //dtor
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
