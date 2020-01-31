#include "Controller/GameController.h"
#include "SceneManager/SceneManagerBattle.h"
#include "SceneManager/SceneManagerGameOver.h"
#include "SceneManager/SceneManagerMessage.h"
#include "Controller/Localization.h"
#include "Controller/MusicController.h"

#ifdef DEBUG_FLAG
#include <cereal/archives/xml.hpp>
#else
#include <cereal/archives/portable_binary.hpp>
#endif
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
//Register Derived Classes for cereal
#include "SceneManager/SceneManagerGameMenu.h"
CEREAL_REGISTER_TYPE(SceneManagerGameMenu);
#include "SceneManager/SceneManagerMainMenu.h"
CEREAL_REGISTER_TYPE(SceneManagerMainMenu);
#include "SceneManager/SceneManagerVillage.h"
CEREAL_REGISTER_TYPE(SceneManagerVillage);
CEREAL_REGISTER_TYPE(SceneManagerMoveable);
#include "SceneManager/SceneManagerDungeon.h"
CEREAL_REGISTER_TYPE(SceneManagerDungeon);


CEREAL_REGISTER_TYPE(MapFillVillage);
#include "MapGeneration/MapFillDungeon.h"
CEREAL_REGISTER_TYPE(MapFillDungeon);
#include "MapGeneration/MapFillDungeon2.h"
CEREAL_REGISTER_TYPE(MapFillDungeon2);
#include "MapGeneration/MapFillIceDungeon.h"
CEREAL_REGISTER_TYPE(MapFillIceDungeon);

#include "MapGeneration/MapEventTile.h"
CEREAL_REGISTER_TYPE(MapEventTile);
#include "MapGeneration/MapEventDungeonEntrance.h"
CEREAL_REGISTER_TYPE(MapEventDungeonEntrance);
#include "MapGeneration/MapEventShop.h"
CEREAL_REGISTER_TYPE(MapEventShop);
#include "MapGeneration/MapEventHero.h"
CEREAL_REGISTER_TYPE(MapEventHero);
#include "MapGeneration/MapEventChest.h"
CEREAL_REGISTER_TYPE(MapEventChest);
#include "MapGeneration/MapEventStairs.h"
CEREAL_REGISTER_TYPE(MapEventStairs);
#include "MapGeneration/MapEventEnemy.h"
CEREAL_REGISTER_TYPE(MapEventEnemy);

CEREAL_REGISTER_TYPE(Equipment);

#include "Battle/PassiveSkill.h"
CEREAL_REGISTER_TYPE(PassiveSkill);


#include <iostream>
#include <fstream>


namespace ControllerFunctions
{
    void QuitToVillage()
    {
        GameController::getInstance()->QuitTo(SceneManager::SceneManagerType::Village);
    }
}

GameController* GameController::m_instance = 0;
GameController::GameController() : m_randomGenerator((unsigned int)time(NULL))
{
    //ctor
    LoadProgress();
    m_renderTarget = 0;
    m_lastDungeon = 0;
    m_keysPressed.resize(Configuration::GetInstance()->GetNumberKeys());
    m_defaultKeysPressed.resize(Configuration::GetInstance()->GetNumberKeys());
    m_gameOver = false;
    m_dungeonConfiguration = nullptr;
    m_quit = false;
    m_windowFocused = true;

    InitValues();

    //TODO: load actual values
    m_windowWidth = 640;
    m_windowHeight = 480;
}

GameController::~GameController()
{
    //dtor
    if(m_dungeonConfiguration != nullptr)
        delete m_dungeonConfiguration;
}

void GameController::InitValues()
{
    m_lastDungeon = 0;
    m_currentGameWasLoaded = false;
}

bool GameController::IsWindowFocused()
{
    return m_windowFocused;
}

void GameController::SetWindowFocus(bool focused)
{
    m_windowFocused = focused;
    MusicController::GetInstance()->PauseMusic(!focused);
}

void GameController::setParty(Party party)
{
    m_party = party;
}

Party* GameController::getParty()
{
    return &m_party;
}

SceneManager* GameController::GetActiveSceneManager()
{
    return m_sceneManager.back().get();
}

void GameController::CloseActiveSceneManger()
{
    m_sceneManager.pop_back();
}

void GameController::LoadSceneManager(SceneManager* sm)
{
    m_sceneManager.push_back(std::shared_ptr<SceneManager>(sm));
}

void GameController::LoadSceneManager(std::shared_ptr<SceneManager> sm)
{
    m_sceneManager.push_back(sm);
}

void GameController::LoadSceneManagerBefore(SceneManager* newSm, SceneManager* sm)
{
    LoadSceneManagerBefore(std::shared_ptr<SceneManager>(newSm), sm);
}

void GameController::LoadSceneManagerBefore(std::shared_ptr<SceneManager> newSm, SceneManager* sm)
{
    int i = 0;
    if(sm == nullptr)
    {
        i = m_sceneManager.size() - 1;
    }
    else
    {
        for(; i < m_sceneManager.size(); i++)
        {
            if(m_sceneManager[i].get() == sm)
            {
                break;
            }
        }
    }


    m_sceneManager.insert(m_sceneManager.begin() + i, newSm);
}

void GameController::Tick()
{
    m_frameTime = m_clock.getElapsedTime();
    m_clock.restart();

    Configuration* conf = Configuration::GetInstance();
    //Check Keys
    for(unsigned int i = 0; i < m_keysPressed.size(); i++)
    {
        if(m_keysPressed.at(i) && !sf::Keyboard::isKeyPressed(conf->GetKey((Configuration::Keys)i)))
        {
            m_keysPressed.at(i) = false;
        }
    }
    for(unsigned int i = 0; i < m_defaultKeysPressed.size(); i++)
    {
        if(m_defaultKeysPressed.at(i) && !sf::Keyboard::isKeyPressed(conf->GetDefaultKey((Configuration::Keys)i)))
        {
            m_defaultKeysPressed.at(i) = false;
        }
    }

    //Tick all Scene Manager til the first one that does not pause the one below
    for(int i = m_sceneManager.size() - 1; i >= 0; i--)
    {
        m_sceneManager[i]->NextTick();
        if(m_sceneManager[i]->PausesSceneManagerBelow())
            break;
    }
    int start = 0;
    for(int i = m_sceneManager.size() - 1; i >= 0; i--)
    {
        if(!m_sceneManager[i]->IsTransparent())
        {
            start = i;
            break;
        }
    }
    GetRenderTarget()->clear();
    for(int i = start; i < m_sceneManager.size(); i++)
    {
        m_sceneManager[i]->Draw();
    }

    if(GetActiveSceneManager()->IsFinished())
    {
        CloseActiveSceneManger();
        if(m_gameOver)
            GameOver();
    }
    if(m_quit)
    {
        ToQuitScreen();
        m_quit = false;
    }
}
void GameController::StartBattle(std::vector<Entity*>* enemies)
{
    SceneManagerBattle* newBattle = new SceneManagerBattle();

    for(auto it = enemies->begin(); it != enemies->end(); it++)
    {
        newBattle->AddEnemy((*it));
    }
    LoadSceneManager(newBattle);
}

void GameController::GotoNextLevel()
{
    m_levelId++;
    if(!m_nextLevels.empty())
    {
        //if there is already a created level
        std::shared_ptr<SceneManager> next = m_nextLevels.at(m_nextLevels.size() - 1);
        m_nextLevels.pop_back();
        LoadSceneManager(next);
    }
    else if(m_levelId <= m_dungeonConfiguration->GetNrLevels())
    {
        //if not create a new one
        LoadSceneManager(m_dungeonConfiguration->GetLevel(m_levelId));
    }
    else
    {
        //finish the dungeon
        std::string rewards = m_dungeonConfiguration->ClearedDungeon();
        SceneManagerMessage* message = new SceneManagerMessage(Localization::GetInstance()->GetLocalization("dungeon.finished") + rewards);
        message->OnAccept(std::function<void()>(ControllerFunctions::QuitToVillage));
        LoadSceneManager(message);
        m_lastDungeon = m_dungeonConfiguration->GetDungeonId();
        m_progress.ClearedDungeon(m_lastDungeon);
    }
}

void GameController::GotoPreviousLevel()
{
    if(m_levelId > 1)
    {
        m_levelId--;
        //Unload Scene Manager, should be a Dungeon-Level
        m_nextLevels.push_back(m_sceneManager.back());
        m_sceneManager.pop_back();
    }
    else
    {
        //exit Dungeon
        QuitTo(SceneManager::SceneManagerType::Village);
        m_levelId = 0;
    }
}

void GameController::SetDungeonConfiguration(DungeonConfiguration* config)
{
    if(m_dungeonConfiguration != nullptr)
    {
        delete m_dungeonConfiguration;
    }
    m_dungeonConfiguration = config;
    m_levelId = 0;
}

DungeonConfiguration* GameController::GetDungeonConfiguration()
{
    return m_dungeonConfiguration;
}


void GameController::SetRenderTarget(sf::RenderTarget* target)
{
    m_renderTarget = target;
}

sf::RenderTarget* GameController::GetRenderTarget()
{
    return m_renderTarget;
}

int GameController::GetWindowWidth()
{
    return m_windowWidth;
}

int GameController::GetWindowHeight()
{
    return m_windowHeight;
}

float GameController::GetTickTimeSeconds()
{
    return m_frameTime.asSeconds();
}

PersistentProgress* GameController::GetPersistentProgress()
{
    return &m_progress;
}

bool GameController::IsKeyPressed(Configuration::Keys key, bool once)
{
    //Only check Keys if Window is focused
    if(!IsWindowFocused())
    {
        return false;
    }
    if(!once)
    {
        return sf::Keyboard::isKeyPressed(Configuration::GetInstance()->GetKey(key)) || sf::Keyboard::isKeyPressed(Configuration::GetInstance()->GetDefaultKey(key));
    }

    if(!m_keysPressed.at(key) && sf::Keyboard::isKeyPressed(Configuration::GetInstance()->GetKey(key)))
    {
        m_keysPressed.at(key) = true;
        m_defaultKeysPressed.at(key) = true;
        return true;
    }
    if(!m_defaultKeysPressed.at(key) && sf::Keyboard::isKeyPressed(Configuration::GetInstance()->GetDefaultKey(key)))
    {
        m_keysPressed.at(key) = true;
        m_defaultKeysPressed.at(key) = true;
        return true;
    }
    return false;
}

void GameController::GameOverCheck()
{
    m_gameOver = true;
    for(unsigned int i = 0; i < m_party.GetAllPartyMembers()->size(); i++)
    {
        if(!m_party.GetAllPartyMembers()->at(i)->IsDead())
        {
            m_gameOver = false;
        }
    }
    //Remove save file
    if(m_currentGameWasLoaded)
    {
        RemoveSaveFile();
    }
}

void GameController::GameOver()
{
    //Only show Game over if not in Main Menu
    if(m_gameOver && m_sceneManager.size() > 1)
    {
        m_quitTo = SceneManager::SceneManagerType::MainMenu;
        ToQuitScreen();
        //display Game Over screen
        SceneManagerGameOver* gameOver = new SceneManagerGameOver();
        LoadSceneManager(gameOver);
        m_gameOver = false;
    }
}

void GameController::ToQuitScreen()
{
    //remove all SceneManager but the declared type
    while(GetActiveSceneManager()->GetType() != m_quitTo && m_sceneManager.size() > 1)
    {
        CloseActiveSceneManger();
    }
}

void GameController::QuitTo(SceneManager::SceneManagerType type)
{
    m_quit = true;
    m_quitTo = type;
}


std::default_random_engine* GameController::GetRandomGenerator()
{
    return &m_randomGenerator;
}
int GameController::GetLastDungeonBeated()
{
    return m_lastDungeon;
}

void GameController::SaveToFile()
{

    #ifdef DEBUG_FLAG
    std::ofstream f(Configuration::GetInstance()->GetSaveFilePath());
    cereal::XMLOutputArchive oarchive(f);
    #else
    std::ofstream f(Configuration::GetInstance()->GetSaveFilePath(), std::ios::binary);
    cereal::PortableBinaryOutputArchive oarchive(f);
    #endif
    oarchive(m_party, m_sceneManager);
}

bool GameController::LoadFromFile()
{

    #ifdef DEBUG_FLAG
    std::ifstream f(Configuration::GetInstance()->GetSaveFilePath());
    cereal::XMLInputArchive iarchive(f);
    #else
    std::ifstream f(Configuration::GetInstance()->GetSaveFilePath(), std::ios::binary);
    cereal::PortableBinaryInputArchive iarchive(f);
    #endif

    try
    {
        DungeonConfiguration conf;
        m_party = Party();
        iarchive(m_party, m_sceneManager);
        InitValues();
        m_currentGameWasLoaded = true;
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool GameController::LoadAvailable()
{
    std::ifstream f(Configuration::GetInstance()->GetSaveFilePath());
    return f.good();
}

void GameController::RemoveSaveFile()
{
    std::remove(Configuration::GetInstance()->GetSaveFilePath().c_str());
}

void GameController::SaveProgress()
{
    #ifdef DEBUG_FLAG
    std::ofstream f(Configuration::GetInstance()->GetProgressFilePath());
    cereal::XMLOutputArchive oarchive(f);
    #else
    std::ofstream f(Configuration::GetInstance()->GetProgressFilePath(), std::ios::binary);
    cereal::PortableBinaryOutputArchive oarchive(f);
    #endif
    oarchive(m_progress);
}

void GameController::LoadProgress()
{
    #ifdef DEBUG_FLAG
    std::ifstream f(Configuration::GetInstance()->GetProgressFilePath());
    if(!f.good())
        return;
    cereal::XMLInputArchive iarchive(f);
    #else
    std::ifstream f(Configuration::GetInstance()->GetProgressFilePath(), std::ios::binary);
    if(!f.good())
        return;
    cereal::PortableBinaryInputArchive iarchive(f);
    #endif
    iarchive(m_progress);
}




GameController* GameController::getInstance()
{
    if(m_instance == 0)
    {
        m_instance = new GameController();
    }
    return m_instance;
}
