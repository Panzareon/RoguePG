#include "GameController.h"
#include "SceneManagerBattle.h"
#include <iostream>

GameController* GameController::m_instance = 0;
GameController::GameController() : m_randomGenerator(time(NULL))
{
    //ctor
    m_party = 0;
    m_renderTarget = 0;
    m_keysPressed.resize(Configuration::GetInstance()->GetNumberKeys());

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


    GetActiveSceneManager()->NextTick();
    if(GetActiveSceneManager()->IsFinished())
    {
        CloseActiveSceneManger();
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

void GameController::GameOver()
{
    m_party->UpdateActiveParty();
    bool finished = true;
    for(unsigned int i = 0; i < m_party->GetActivePartyMembers()->size(); i++)
    {
        if(!m_party->GetActivePartyMembers()->at(i)->IsDead())
        {
            finished = false;
        }
    }
    if(finished)
    {
        //TODO: remove all SceneManager and display Game Over screen
    }
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
