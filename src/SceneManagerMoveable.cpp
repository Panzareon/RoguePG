#include "SceneManagerMoveable.h"
#include "SceneManagerGameMenu.h"
#include "Configuration.h"
#include "GameController.h"
#include "DrawableNode.h"

#include "EnemyFactory.h"
#include <iostream>

SceneManagerMoveable::SceneManagerMoveable(int tileWidth, int tileHeight): m_map(tileWidth, tileHeight)
{
    //ctor
    m_heroDirection = Enums::North;
    m_minViewPosX = m_windowWidth / 2;
    m_minViewPosY = m_windowHeight / 2;
    m_minimapViewRange = 5;
    m_heroMoved = TileMap::GetTileWidth();

    m_maxViewPosX = m_map.GetWidth() * TileMap::GetTileWidth() - m_windowWidth / 2;
    m_maxViewPosY = m_map.GetHeight() * TileMap::GetTileWidth() - m_windowHeight / 2;


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

    //Init minimap
    m_minimap.create(tileWidth, tileHeight, sf::Color::Transparent);
    sf::IntRect minimapSize;
    minimapSize.left = 0;
    minimapSize.top = 0;
    minimapSize.width = tileWidth;
    minimapSize.height = tileHeight;
    m_minimapTexture.loadFromImage(m_minimap,minimapSize);
    DrawableNode* minimap = new DrawableNode(new sf::Sprite(m_minimapTexture));
    m_minimapScale = 2.0f;
    m_minimapNode = new Node();
    minimap->setTransform(minimap->getTransform().scale(m_minimapScale,m_minimapScale));
    m_gui->addChild(m_minimapNode);
    m_minimapNode->addChild(minimap);
    sf::Sprite minimapHero;
    tex = TextureList::getTexture(TextureList::MinimapHero);
    minimapHero.setTexture(*tex);
    minimapHero.setTextureRect(sf::IntRect(0,0,2,2));
    m_minimapPlayer = new AnimatedNode(&minimapHero, tex->GetNumberAnimationSteps());
    m_minimapPlayer->SetAnimationSpeed(2.0f);
    m_minimapNode->addChild(m_minimapPlayer);
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
            m_heroMoved += std::abs(moveX) + std::abs(moveY);
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
                m_heroMoved += std::abs(moveX);
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
                    m_heroMoved += std::abs(moveY);
                }
            }
        }
    }
    if(m_heroMoved >= TileMap::GetTileWidth())
    {
        UpdateMinimap();
        m_heroMoved = 0.0f;
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

void SceneManagerMoveable::UpdateMinimap()
{
    int heroX,heroY;
    sf::FloatRect heroBB = m_hero->getGlobalBoundingBox();
    heroX = (heroBB.left + heroBB.width/2.0f) / TileMap::GetTileWidth();
    heroY = (heroBB.top + heroBB.height/2.0f) / TileMap::GetTileWidth();
    for(int x = heroX - m_minimapViewRange; x <= heroX + m_minimapViewRange; x++)
    {
        for(int y = heroY - m_minimapViewRange; y <= heroY + m_minimapViewRange; y++)
        {
            if(x >= 0 && y >= 0 && x < m_map.GetWidth() && y < m_map.GetHeight())
            {
                m_minimap.setPixel(x,y,m_minimapColor[m_map.GetTileType(x,y)]);
            }
        }
    }
    m_minimapTexture.loadFromImage(m_minimap);
    m_minimapPlayer->setPosition(heroX * m_minimapScale, heroY * m_minimapScale);
}
