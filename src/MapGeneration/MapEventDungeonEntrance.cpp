#include "MapGeneration/MapEventDungeonEntrance.h"
#include "MapGeneration/DungeonConfiguration.h"
#include "Controller/GameController.h"

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
        config = new DungeonConfiguration(2, time(NULL), dungeonId + 1);
    }
    else
    {
        config = new DungeonConfiguration(5, time(NULL), dungeonId + 1);
    }
    config->PlayMusic();
    controller->SetDungeonConfiguration(config);
    controller->GotoNextLevel();
}
