#include "SceneManagerMoveable.h"
#include "SceneManagerGameMenu.h"
#include "Configuration.h"
#include "GameController.h"

#include "EnemyFactory.h"

SceneManagerMoveable::SceneManagerMoveable(int tileWidth, int tileHeight): m_map(tileWidth, tileHeight)
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

    bool doChange = true;
    Enums::Direction newDirection;



    //check Movement Buttons
    if (controller->IsKeyPressed(Configuration::MoveLeft, false))
    {
        moveX -= MoveSpeed * controller->GetTickTimeSeconds();
        newDirection = Enums::West;
        doChange = false;
    }
    if (controller->IsKeyPressed(Configuration::MoveRight, false))
    {
        moveX += MoveSpeed * controller->GetTickTimeSeconds();
        if(doChange || m_heroDirection == Enums::East)
        {
            newDirection = Enums::East;
            doChange = false;
        }
    }
    if (controller->IsKeyPressed(Configuration::MoveUp, false))
    {
        moveY -= MoveSpeed * controller->GetTickTimeSeconds();
        if(doChange || m_heroDirection == Enums::North)
        {
            newDirection = Enums::North;
            doChange = false;
        }
    }
    if (controller->IsKeyPressed(Configuration::MoveDown, false))
    {
        moveY += MoveSpeed * controller->GetTickTimeSeconds();
        if(doChange || m_heroDirection == Enums::South)
        {
            newDirection = Enums::South;
            doChange = false;
        }
    }

    if(doChange == false)
    {
        m_heroDirection = newDirection;
    }

    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel))
    {
        //Open Menu
        SceneManager* sm = new SceneManagerGameMenu();
        controller->LoadSceneManager(sm);
    }

    sf::FloatRect heroBB = m_hero->getGlobalBoundingBox();
    //Check Accept Key
    for(int i = 0; i < m_events.size(); i++)
    {
        if(m_events[i]->ActivateAt(heroBB, m_heroDirection, controller->GetTickTimeSeconds()))
        {
            if(m_events[i]->NeedButtonPress() && !controller->IsKeyPressed(Configuration::Accept))
            {
                continue;
            }
            m_events[i]->Activate();
        }
        if(m_events[i]->IsFinished())
        {
            delete m_events[i];
            m_events.erase(m_events.begin() + i);
        }
    }



    if(moveX != 0.0f || moveY != 0.0f)
    {
        sf::FloatRect heroBBtest = heroBB;
        heroBBtest.left += moveX;
        heroBBtest.top += moveY;
        if(!m_map.DoesCollide(heroBBtest))
        {
            m_hero->moveNode(moveX, moveY);
            UpdateCamPosition();
        }
        else
        {
            //Check only horizontal movement
            sf::FloatRect heroBBtest = heroBB;
            heroBBtest.left += moveX;
            if(!m_map.DoesCollide(heroBBtest))
            {
                m_hero->moveNode(moveX, 0.0f);
                UpdateCamPosition();
            }
            else
            {
                //Check only vertical movement
                sf::FloatRect heroBBtest = heroBB;
                heroBBtest.top += moveY;
                if(!m_map.DoesCollide(heroBBtest))
                {
                    m_hero->moveNode(0.0f, moveY);
                    UpdateCamPosition();
                }
            }
        }
    }
}
void SceneManagerMoveable::UpdateCamPosition()
{
    //Places the Cam on the Hero
    sf::FloatRect heroBB = m_hero->getGlobalBoundingBox();
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

