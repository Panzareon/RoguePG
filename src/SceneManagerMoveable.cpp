#include "SceneManagerMoveable.h"
#include "SceneManagerGameMenu.h"
#include "Configuration.h"
#include "GameController.h"
#include "DrawableNode.h"

#include "EnemyFactory.h"

SceneManagerMoveable::SceneManagerMoveable(int tileWidth, int tileHeight): m_map(tileWidth, tileHeight)
{
    //ctor
    m_heroDirection = Enums::North;
    m_minViewPosX = m_windowWidth / 2;
    m_minViewPosY = m_windowHeight / 2;

    m_maxViewPosX = m_map.GetWidth() * TileMap::GetTileWith() - m_windowWidth / 2;
    m_maxViewPosY = m_map.GetHeight() * TileMap::GetTileWith() - m_windowHeight / 2;


    m_tileMap = new TileMap();
    m_tileMapItems = new TileMap();
    m_tileMapAboveHero = new TileMap();
    m_tileMapAboveWall = new TileMap();
    m_tileMapWallDecoration = new TileMap();



    m_tileMap->setTexture(TextureList::getTexture(TextureList::DungeonTileMap));
    m_tileMapItems->setTexture(TextureList::getTexture(TextureList::DungeonTileMap));
    m_tileMapAboveHero->setTexture(TextureList::getTexture(TextureList::DungeonTileMap));
    m_tileMapAboveWall->setTexture(TextureList::getTexture(TextureList::DungeonTileMap));
    m_tileMapWallDecoration->setTexture(TextureList::getTexture(TextureList::DungeonTileMap));


    //Build Scene Graph
    m_mainNode = new Node();
    m_belowHero = new Node();
    m_mainNode->addChild(m_belowHero);

    m_eventLayer = new Node();
    m_mainNode->addChild(m_eventLayer);
    m_mainNode->addChild(m_animationNode);

    m_aboveHero = new Node();
    m_mainNode->addChild(m_aboveHero);

    m_belowHero->addChild(new DrawableNode(m_tileMap));

    #ifdef DEBUG_FLAG

    m_tileMapRoomNumber = new TileMap();
    m_tileMapRoomNumber->setTexture(TextureList::getTexture(TextureList::DebugTileMap));
    m_roomNumberNode = new DrawableNode(m_tileMapRoomNumber);
    m_roomNumberNode->setVisibility(false);
    m_belowHero->addChild(m_roomNumberNode);

    #endif // DEBUG_FLAG

    m_belowHero->addChild(new DrawableNode(m_tileMapItems));

    m_aboveHero->addChild(new DrawableNode(m_tileMapAboveHero));
    m_aboveHero->addChild(new DrawableNode(m_tileMapAboveWall));
    m_aboveHero->addChild(new DrawableNode(m_tileMapWallDecoration));


    //Add Hero
    sf::Sprite hero;
    Texture* tex = TextureList::getTexture(TextureList::HeroSpriteSheet);
    hero.setTexture(*tex);
    hero.setTextureRect(sf::IntRect(0,0,32,36));
    m_hero = new AnimatedNode(&hero, tex->GetNumberAnimationSteps());
    m_hero->setBoundingBox(sf::FloatRect(8.0f,20.0f,16.0f,16.0f));
    m_eventLayer->addChild(m_hero);
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
        m_hero->SetDirection(m_heroDirection);
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

