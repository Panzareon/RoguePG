#include "SceneManagerMoveable.h"

SceneManagerMoveable::SceneManagerMoveable(sf::RenderTarget * target, int windowWidth, int windowHeight, int tileWidth, int tileHeight): SceneManager(target, windowWidth, windowHeight), m_map(tileWidth, tileHeight)
{
    //ctor
    m_minViewPosX = m_windowWidth / 2;
    m_minViewPosY = m_windowHeight / 2;

    m_maxViewPosX = m_map.GetWidth() * TileMap::GetTileMapWith() - m_windowWidth / 2;
    m_maxViewPosY = m_map.GetHeight() * TileMap::GetTileMapWith() - m_windowHeight / 2;
}

SceneManagerMoveable::~SceneManagerMoveable()
{
    //dtor
}
void SceneManagerMoveable::Tick()
{
    //Calculations fore every tick

    //Movement for now
    float MoveSpeed = 256.0f;
    float moveX = 0.0f;
    float moveY = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        moveX -= MoveSpeed * m_frameTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        moveX += MoveSpeed * m_frameTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        moveY -= MoveSpeed * m_frameTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        moveY += MoveSpeed * m_frameTime.asSeconds();
    }

    if(moveX != 0.0f || moveY != 0.0f)
    {
        sf::FloatRect heroBB = m_hero->getGlobalBoundingBox();
        heroBB.left += moveX;
        heroBB.top += moveY;
        if(!m_map.DoesCollide(heroBB))
        {
            m_hero->moveNode(moveX, moveY);
            m_posx = heroBB.left;
            m_posy = heroBB.top;

            if(m_posx < m_minViewPosX)
                m_posx = m_minViewPosX;
            else if(m_posx > m_maxViewPosX)
                m_posx = m_maxViewPosX;
            if(m_posy < m_minViewPosY)
                m_posy = m_minViewPosY;
            else if(m_posy > m_maxViewPosY)
                m_posy = m_maxViewPosY;
        }
    }
}
