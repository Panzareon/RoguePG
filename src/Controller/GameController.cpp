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

CEREAL_REGISTER_TYPE(Equipment);

#include "Battle/PassiveSkill.h"
CEREAL_REGISTER_TYPE(PassiveSkill);


#include <iostream>
#include <fstream>


namespace ControllerFunctions
{
    void QuitToVillage()
    {
        GameController::getInstance()->QuitTo(SceneManager::TypeVillage);
    }
}

GameController* GameController::m_instance = 0;
GameController::GameController() : m_randomGenerator(time(NULL))
{
    //ctor
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
        SceneManagerMessage* message = new SceneManagerMessage(Localization::GetInstance()->GetLocalization("dungeon.finished"));
        message->OnAccept(std::function<void()>(ControllerFunctions::QuitToVillage));
        LoadSceneManager(message);
        m_lastDungeon = m_dungeonConfiguration->GetDungeonId();
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
        QuitTo(SceneManager::TypeVillage);
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
    for(unsigned int i = 0; i < m_party.GetActivePartyMembers()->size(); i++)
    {
        if(!m_party.GetActivePartyMembers()->at(i)->IsDead())
        {
            m_gameOver = false;
        }
    }
}

void GameController::GameOver()
{
    //Only show Game over if not in Main Menu
    if(m_gameOver && m_sceneManager.size() > 1)
    {
        m_quitTo = SceneManager::TypeMainMenu;
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
    std::ofstream f(Configuration::GetInstance()->GetSaveFilePath());

    #ifdef DEBUG_FLAG
    cereal::XMLOutputArchive oarchive(f);
    #else
    cereal::PortableBinaryOutputArchive oarchive(f);
    #endif
    oarchive(m_party, m_sceneManager);
}

void GameController::LoadFromFile()
{
    std::ifstream f(Configuration::GetInstance()->GetSaveFilePath());

    #ifdef DEBUG_FLAG
    cereal::XMLInputArchive iarchive(f);
    #else
    cereal::PortableBinaryInputArchive iarchive(f);
    #endif

    iarchive(m_party, m_sceneManager);
    InitValues();
}






GameController* GameController::getInstance()
{
    if(m_instance == 0)
    {
        m_instance = new GameController();
    }
    return m_instance;
}
