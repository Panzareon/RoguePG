#include "MapGeneration/MapEventDungeonEntrance.h"
#include "MapGeneration/DungeonConfiguration.h"
#include "Controller/GameController.h"

MapEventDungeonEntrance::MapEventDungeonEntrance()
{
    //ctor
}
MapEventDungeonEntrance::MapEventDungeonEntrance(int x, int y) : MapEventTile(true, x,y)
{
    //ctor
}

MapEventDungeonEntrance::~MapEventDungeonEntrance()
{
    //dtor
}

void MapEventDungeonEntrance::Activate()
{
    GameController* controller = GameController::getInstance();
    int dungeonId = controller->GetLastDungeonBeated();
    DungeonConfiguration * config;
    if(dungeonId == 0)
    {
        config = new DungeonConfiguration(2, (unsigned int)time(NULL), dungeonId + 1);
    }
    else
    {
        config = new DungeonConfiguration(3, (unsigned int)time(NULL), dungeonId + 1);
    }
    config->PlayMusic();
    controller->SetDungeonConfiguration(config);
    controller->GotoNextLevel();
}
