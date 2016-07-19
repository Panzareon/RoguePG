#include "SceneManager.h"

SceneManager::SceneManager()
{
    //ctor
}

SceneManager::~SceneManager()
{
    //dtor
    if(m_mainNode != 0)
        delete m_mainNode;
}
void SceneManager::DrawScene(sf::RenderTarget& target)
{
    m_mainNode->draw(target, sf::Transform::Identity);
}
