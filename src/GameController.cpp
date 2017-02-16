#include "GameController.h"
#include "SceneManagerBattle.h"
#include "SceneManagerGameOver.h"
#include <iostream>

GameController* GameController::m_instance = 0;
GameController::GameController() : m_randomGenerator(time(NULL))
{
    //ctor
    m_party = nullptr;
    m_renderTarget = 0;
    m_keysPressed.resize(Configuration::GetInstance()->GetNumberKeys());
    m_gameOver = false;
    m_levelId = 0;
    m_dungeonConfiguration = nullptr;
    m_quit = false;

    //TODO: load actual values
    m_windowWidth = 640;
    m_windowHeight = 480;
}

GameController::~GameController()
{
    //dtor
    delete m_party;
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
        //TODO: finish the dungeon
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
        //TODO: exit Dungeon
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

bool GameController::IsKeyPressed(Configuration::Keys key)
{
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
    if(m_gameOver)
    {
        ToMainMenu();
        //display Game Over screen
        SceneManagerGameOver* gameOver = new SceneManagerGameOver(GetRenderTarget(), GetWindowWidth(), GetWindowHeight());
        LoadSceneManager(gameOver);
    }
}

void GameController::ToMainMenu()
{
    //remove all SceneManager but the Main Menu
    while(m_sceneManager.size() > 1)
    {
        CloseActiveSceneManger();
    }
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
