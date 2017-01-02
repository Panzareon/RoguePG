#include "SceneManagerMoveable.h"
#include "SceneManagerGameMenu.h"
#include "Configuration.h"
#include "GameController.h"

#include "EnemyFactory.h"

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
    GameController* controller = GameController::getInstance();

    //Movement
    //TODO: calculate movement Speed
    float MoveSpeed = 256.0f;
    Configuration* conf = Configuration::GetInstance();

    float moveX = 0.0f;
    float moveY = 0.0f;

    //check Movement Buttons
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

    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel))
    {
        //Open Menu
        SceneManager* sm = new SceneManagerGameMenu(controller->GetRenderTarget(), controller->GetWindowWidth(), controller->GetWindowHeight());
        controller->LoadSceneManager(sm);
    }

    //TODO: remove Debugkey
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        std::vector<Entity*> enemies;
        //TODO: get Entities of this Map from somewhere else
        Entity* e = EnemyFactory::GetEntity(EnemyFactory::EnemyListBat);
        e->SetTeamId(1);
        enemies.push_back(e);
        e = EnemyFactory::GetEntity(EnemyFactory::EnemyListBat);
        e->SetTeamId(1);
        enemies.push_back(e);

        GameController::getInstance()->StartBattle(&enemies);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        GameController::getInstance()->getParty()->GetActivePartyMembers()->at(0)->LevelUp();
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
