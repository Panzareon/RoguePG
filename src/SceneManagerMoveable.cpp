#include "SceneManagerMoveable.h"
#include "Configuration.h"
#include "GameController.h"

SceneManagerMoveable::SceneManagerMoveable(sf::RenderTarget * target, int windowWidth, int windowHeight, int tileWidth, int tileHeight): SceneManager(target, windowWidth, windowHeight), m_map(tileWidth, tileHeight)
{
    //ctor
    m_minViewPosX = m_windowWidth / 2;
    m_minViewPosY = m_windowHeight / 2;

    m_maxViewPosX = m_map.GetWidth() * TileMap::GetTileWith() - m_windowWidth / 2;
    m_maxViewPosY = m_map.GetHeight() * TileMap::GetTileWith() - m_windowHeight / 2;
}

SceneManagerMoveable::~SceneManagerMoveable()
{
    //dtor
}
void SceneManagerMoveable::Tick()
{
    //Calculations fore every tick

    //Movement
    //TODO: calculate movement Speed
    float MoveSpeed = 256.0f;
    Configuration* conf = Configuration::GetInstance();

    float moveX = 0.0f;
    float moveY = 0.0f;

    if (sf::Keyboard::isKeyPressed(conf->GetKey(Configuration::MoveLeft)))
    {
        moveX -= MoveSpeed * m_frameTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(conf->GetKey(Configuration::MoveRight)))
    {
        moveX += MoveSpeed * m_frameTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(conf->GetKey(Configuration::MoveUp)))
    {
        moveY -= MoveSpeed * m_frameTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(conf->GetKey(Configuration::MoveDown)))
    {
        moveY += MoveSpeed * m_frameTime.asSeconds();
    }

    //TODO: remove Debugkey
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        std::vector<Entity*> enemies;
        //TODO: get Entities of this Map from somewhere else
        enemies.push_back(new Entity(1));
        enemies.push_back(new Entity(1));

        GameController::getInstance()->StartBattle(&enemies);
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
