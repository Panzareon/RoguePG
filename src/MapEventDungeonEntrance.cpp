#include "MapEventDungeonEntrance.h"
#include "DungeonConfiguration.h"
#include "GameController.h"

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
    DungeonConfiguration * config = new DungeonConfiguration(5, time(NULL));
    config->PlayMusic();
    GameController* controller = GameController::getInstance();
    controller->SetDungeonConfiguration(config);
    controller->GotoNextLevel();
}
