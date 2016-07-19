#include "SceneManager.h"
#include <cmath>

SceneManager::SceneManager(sf::RenderTarget* target)
{
    //ctor
    m_target = target;
    m_posx = 320;
    m_posy = 240;
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


    Tick();

    sf::View view = m_target->getDefaultView();
    view.setCenter(std::floor(m_posx), std::floor(m_posy));
    m_target->setView(view);



    m_target->clear();
    DrawScene();

}
