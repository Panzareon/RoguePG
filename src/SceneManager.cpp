#include "SceneManager.h"
#include "GameController.h"
#include "Configuration.h"
#include "EntityBarsNode.h"
#include <cmath>

SceneManager::SceneManager(sf::RenderTarget* target, int windowWidth, int windowHeight)
{
    //ctor
    m_target = target;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;


    m_posx = m_windowWidth / 2;
    m_posy = m_windowHeight / 2;


    m_animationNode = new Node();
    m_gui = new Node();
    m_mainMenu = new MenuNode(m_windowWidth);
    m_mainMenu->setVisibility(false);
    m_gui->addChild(m_mainMenu);

    m_memberStats = new Node();
    m_gui->addChild(m_memberStats);
    SetMemberStats();
}

SceneManager::~SceneManager()
{
    //dtor
    if(m_mainNode != 0)
        delete m_mainNode;
    delete m_gui;
}
void SceneManager::SetMemberStats()
{
    EntityBarsNode* bars;
    Party* p = GameController::getInstance()->getParty();
    int nr = Configuration::GetInstance()->GetMaxPartySize();
    int posX = 10;
    int posY = m_windowHeight - 40;
    int posXDelta = (m_windowWidth - 10) / nr;
    for(int i = 0; i < nr; i++)
    {
        sf::Transform t;
        t.translate(posX, posY);
        bars = new EntityBarsNode(i, p);
        bars->setTransform(t);
        m_memberStats->addChild(bars);
        posX += posXDelta;
    }
}

void SceneManager::DrawScene()
{
    m_mainNode->draw(*m_target, sf::Transform::Identity);
}

void SceneManager::DrawGui()
{
    m_gui->draw(*m_target, sf::Transform::Identity);
}

void SceneManager::NextTick()
{
    m_frameTime = m_clock.getElapsedTime();
    m_clock.restart();

    m_mainNode->Tick(m_frameTime.asSeconds());
    m_gui->Tick(m_frameTime.asSeconds());
    //Call Ticks on Animation
    auto iter = m_animationList.begin();
    while(iter != m_animationList.end())
    {
        (*iter)->PassTime(m_frameTime.asSeconds());
        if((*iter)->IsFinished())
        {
            delete (*iter);
            iter = m_animationList.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    //Call Ticks for derived Classes
    Tick();

    sf::View view = m_target->getDefaultView();
    view.setCenter(std::floor(m_posx), std::floor(m_posy));
    m_target->setView(view);



    m_target->clear();
    DrawScene();

    m_target->setView(m_target->getDefaultView());
    DrawGui();


}
bool SceneManager::IsFinished()
{
    return false;
}

void SceneManager::AddAnimation(Animation* anim)
{
    m_animationList.push_back(anim);
}

Node* SceneManager::GetAnimationNode()
{
    return m_animationNode;
}

void SceneManager::AddSubMenu(MenuNode* menu)
{
    m_mainMenu->addChild(menu);
}
