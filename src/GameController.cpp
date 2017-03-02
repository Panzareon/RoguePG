#include "GameController.h"
#include "SceneManagerBattle.h"
#include "SceneManagerGameOver.h"
#include "SceneManagerMessage.h"
#include "Localization.h"

#include <iostream>


namespace ControllerFunctions
{
    void QuitToMainMenu()
    {
        GameController::getInstance()->QuitToMainMenu();
    }
}

GameController* GameController::m_instance = 0;
GameController::GameController() : m_randomGenerator(time(NULL))
{
    //ctor
    m_renderTarget = 0;
    m_keysPressed.resize(Configuration::GetInstance()->GetNumberKeys());
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
    if(m_party != nullptr)
        delete m_party;
    if(m_dungeonConfiguration != nullptr)
        delete m_dungeonConfiguration;
}

void GameController::InitValues()
{
    if(m_party != nullptr)
        delete m_party;
    m_party = nullptr;
    m_levelId = 0;
}

bool GameController::IsWindowFocused()
{
    return m_windowFocused;
}

void GameController::SetWindowFocus(bool focused)
{
    m_windowFocused = focused;
}

void GameController::setParty(Party* party)
{
    if(m_party != nullptr)
    {
        delete m_party;
    }
    m_party = party;
}

Party* GameController::getParty()
{
    return m_party;
}

SceneManager* GameController::GetActiveSceneManager()
{
    return m_sceneManager.back();
}

void GameController::CloseActiveSceneManger()
{
    SceneManager* last = GetActiveSceneManager();
    m_sceneManager.pop_back();
    delete last;
}

void GameController::LoadSceneManager(SceneManager* sm)
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
        ToMainMenu();
        m_quit = false;
    }
}
void GameController::StartBattle(std::vector<Entity*>* enemies)
{
    SceneManagerBattle* newBattle = new SceneManagerBattle(GetRenderTarget(), GetWindowWidth(), GetWindowHeight());

    for(auto it = enemies->begin(); it != enemies->end(); it++)
    {
        newBattle->AddEnemy((*it));
    }
    LoadSceneManager(newBattle);
}

void GameController::GotoNextLevel()
{
    m_levelId++;
    SceneManager* next;
    if(!m_nextLevels.empty())
    {
        //if there is already a created level
        next = m_nextLevels.at(m_nextLevels.size() - 1);
        m_nextLevels.pop_back();
        LoadSceneManager(next);
    }
    else if(m_levelId <= m_dungeonConfiguration->GetNrLevels())
    {
        //if not create a new one
        next = m_dungeonConfiguration->GetLevel(m_levelId);
        LoadSceneManager(next);
    }
    else
    {
        //finish the dungeon
        SceneManagerMessage* message = new SceneManagerMessage(GetRenderTarget(), GetWindowWidth(), GetWindowHeight(), Localization::GetInstance()->GetLocalization("dungeon.finished"));
        message->OnAccept(std::function<void()>(ControllerFunctions::QuitToMainMenu));
        LoadSceneManager(message);
    }
}

void GameController::GotoPreviousLevel()
{
    if(m_levelId > 1)
    {
        m_levelId--;
        //Unload Scene Manager, should be a Dungeon-Level
        SceneManager* next = GetActiveSceneManager();
        m_sceneManager.pop_back();
        m_nextLevels.push_back(next);
    }
    else
    {
        //exit Dungeon
        QuitToMainMenu();
    }
}

void GameController::SetDungeonConfiguration(DungeonConfiguration* config)
{
    if(m_dungeonConfiguration != nullptr)
    {
        delete m_dungeonConfiguration;
    }
    m_dungeonConfiguration = config;
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

bool GameController::IsKeyPressed(Configuration::Keys key)
{
    //Only check Keys if Window is focused
    if(!IsWindowFocused())
    {
        return false;
    }
    if(!m_keysPressed.at(key) && sf::Keyboard::isKeyPressed(Configuration::GetInstance()->GetKey(key)))
    {
        m_keysPressed.at(key) = true;
        return true;
    }
    return false;
}

void GameController::GameOverCheck()
{
    m_party->UpdateActiveParty();
    m_gameOver = true;
    for(unsigned int i = 0; i < m_party->GetActivePartyMembers()->size(); i++)
    {
        if(!m_party->GetActivePartyMembers()->at(i)->IsDead())
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
        ToMainMenu();
        //display Game Over screen
        SceneManagerGameOver* gameOver = new SceneManagerGameOver(GetRenderTarget(), GetWindowWidth(), GetWindowHeight());
        LoadSceneManager(gameOver);
        m_gameOver = false;
    }
}

void GameController::ToMainMenu()
{
    //remove all SceneManager but the Main Menu
    while(m_sceneManager.size() > 1)
    {
        CloseActiveSceneManger();
    }
    InitValues();
}

void GameController::QuitToMainMenu()
{
    m_quit = true;
}


std::default_random_engine* GameController::GetRandomGenerator()
{
    return &m_randomGenerator;
}







GameController* GameController::getInstance()
{
    if(m_instance == 0)
    {
        m_instance = new GameController();
    }
    return m_instance;
}
