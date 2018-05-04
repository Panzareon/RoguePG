#include "SceneManager/SceneManager.h"
#include "Controller/GameController.h"
#include "Controller/Configuration.h"
#include "SceneGraph/EntityBarsNode.h"
#include <cmath>

SceneManager::SceneManager()
{
    //ctor
    GameController* controller = GameController::getInstance();
    m_target = controller->GetRenderTarget();
    m_windowWidth = controller->GetWindowWidth();
    m_windowHeight = controller->GetWindowHeight();


    m_posx = m_windowWidth / 2;
    m_posy = m_windowHeight / 2;


    m_animationNode = new Node();
    m_gui = new Node();
    m_mainMenu = new MenuNode(m_windowWidth);
    m_mainMenu->setVisibility(false);
    m_gui->addChild(m_mainMenu);

    m_memberStats = new Node();
    m_gui->addChild(m_memberStats);
    m_mainNode = nullptr;
}

SceneManager::~SceneManager()
{
    //dtor
    if(m_mainNode != nullptr)
        delete m_mainNode;
    delete m_gui;
}
void SceneManager::SetMemberStats()
{
    EntityBarsNode* bars;
    Party* p = GameController::getInstance()->getParty();
    int nr = Configuration::GetInstance()->GetMaxPartySize();
    int posX = 10;
    int posY = m_windowHeight - 45;
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
    if(m_mainNode != nullptr)
        m_mainNode->draw(*m_target, sf::Transform::Identity);
}

void SceneManager::DrawGui()
{
    if(m_gui != nullptr)
        m_gui->draw(*m_target, sf::Transform::Identity);
}

void SceneManager::NextTick()
{
    float time = GameController::getInstance()->GetTickTimeSeconds();
    if(m_mainNode != nullptr)
        m_mainNode->Tick(time);
    if(m_gui != nullptr)
        m_gui->Tick(time);
    //Call Ticks on Animation
    bool finished = false;
    auto iter = m_animationList.begin();
    while(iter != m_animationList.end() && !finished)
    {
        (*iter)->PassTime(time);

        finished = (*iter)->StopsOther();

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
}

void SceneManager::Draw()
{

    sf::View view = m_target->getDefaultView();
    view.setCenter(std::floor(m_posx), std::floor(m_posy));
    m_target->setView(view);

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
    if(anim != nullptr)
    {
         m_animationList.push_back(anim);
    }
    else
    {
        std::cout << "Tried playing invalid Animation" << std::endl;
    }
}

Node* SceneManager::GetAnimationNode()
{
    return m_animationNode;
}

void SceneManager::AddSubMenu(MenuNode* menu)
{
    m_mainMenu->addChild(menu);
}

bool SceneManager::IsTransparent()
{
    return false;
}

bool SceneManager::PausesSceneManagerBelow()
{
    return true;
}

SceneManager::SceneManagerType SceneManager::GetType()
{
    return TypeDefault;
}

