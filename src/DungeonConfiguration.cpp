#include "DungeonConfiguration.h"
#include "SceneManagerDungeon.h"
#include "GameController.h"

DungeonConfiguration::DungeonConfiguration(int nrLevels)
{
    //ctor
    m_nrLevels = nrLevels;
}

DungeonConfiguration::~DungeonConfiguration()
{
    //dtor
}

SceneManager* DungeonConfiguration::GetLevel(int id)
{
    //create next Level
    GameController* controller = GameController::getInstance();

    SceneManagerDungeon* sceneManager = new SceneManagerDungeon(controller->GetRenderTarget(),controller->GetWindowWidth(),controller->GetWindowHeight(), 30,30);
    return sceneManager;
}

int DungeonConfiguration::GetNrLevels()
{
    return m_nrLevels;
}
