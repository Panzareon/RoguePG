#include "SceneManager.h"
#include <cmath>

SceneManager::SceneManager(sf::RenderTarget* target, int windowWidth, int windowHeight)
{
    //ctor
    m_target = target;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;


    m_posx = m_windowWidth / 2;
    m_posy = m_windowHeight / 2;
}

SceneManager::~SceneManager()
{
    //dtor
    if(m_mainNode != 0)
        delete m_mainNode;
}
void SceneManager::DrawScene()
{
    m_mainNode->draw(*m_target, sf::Transform::Identity);
}
void SceneManager::NextTick()
{
    m_frameTime = m_clock.getElapsedTime();
    m_clock.restart();

    m_mainNode->Tick(m_frameTime.asSeconds());
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
