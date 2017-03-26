#include "SceneManager/SceneManagerDungeon.h"

#include "SceneGraph/DrawableNode.h"
#include "SceneGraph/AnimatedNode.h"
#include "MapGeneration/TileMap.h"
#include "MapGeneration/MapFillDungeon.h"
#include "SceneGraph/TextureList.h"
#include "MapGeneration/MapEventStairs.h"
#include "MapGeneration/MapEventEnemy.h"
#include "MapGeneration/MapEventHero.h"
#include "MapGeneration/MapEventChest.h"
#include "Controller/GameController.h"
#include "Battle/EnemyFactory.h"
#include "MapGeneration/DungeonConfiguration.h"

#include <iostream>

SceneManagerDungeon::SceneManagerDungeon()
{

}

SceneManagerDungeon::SceneManagerDungeon(int tileWidth, int tileHeight, unsigned int seed, int lvlId, DungeonConfiguration* config, MapFill* mapFill, GenerationType type): SceneManagerMoveable(tileWidth, tileHeight), m_generator(&m_map, seed)
{
    //ctor

    mapFill->SetMap(&m_map);
    m_seed = seed;
    m_dungeonConfig = config;
    m_lvlId = lvlId;
    m_mapFill = std::unique_ptr<MapFill>(mapFill);
    Generate(tileWidth, tileHeight, type);
}

SceneManagerDungeon::~SceneManagerDungeon()
{
    //dtor
}

void SceneManagerDungeon::Generate(int tileWidth, int tileHeight, GenerationType type)
{
    m_minimapColor.resize(MapFillDungeon::TILE_TYPE_END);
    m_minimapColor[MapFillDungeon::Wall] = sf::Color::White;
    m_minimapColor[MapFillDungeon::Space] = sf::Color::Black;
    m_minimapColor[MapFillDungeon::InteractableWall] = sf::Color::White;
    m_minimapColor[MapFillDungeon::BlockingItem] = sf::Color::Black;
    m_minimapColor[MapFillDungeon::WalkthroughItem] = sf::Color::Black;
    m_minimapColor[MapFillDungeon::Stairs] = sf::Color::Red;
    //Define Tile Maps
    SetMemberStats();


    #ifdef DEBUG_FLAG

    m_map.init(6);

    #else

    m_map.init(5);

    #endif // DEBUG_FLAG



    //Generate Map

    switch(type)
    {
    case Cave:
        if(tileHeight > 200 || tileWidth > 200)
            m_generator.FasterCellularAutomata(0.45f);
        else
            m_generator.CellularAutomata(0.45f);
        break;
    case Dungeon:
        m_generator.ConnectedRooms(10,8, tileHeight * tileWidth / 160);
    }

    m_generator.NumberRooms();


    //Fill Base Layer with walkable Tile
    m_mapFill->FillLayer(MapFill::Ground, 0);
    //Fill Wall
    m_mapFill->FillLayer(MapFill::Wall, 0,3);
    //Fill Wall Topping
    m_mapFill->FillLayer(MapFill::WallTopping, 3);


    #ifdef DEBUG_FLAG

    for(int x = 0; x < m_map.GetWidth(); x++)
    {
        for(int y = 0; y < m_map.GetHeight(); y++)
            m_map.SetTileId(x,y,m_map.GetRoomNr(x,y), 5);
    }

    m_map.writeToTileMap(*m_tileMapRoomNumber,5);

    #endif // DEBUG_FLAG

    m_generator.PlaceStartingAndEndPosition();

    sf::Transform heroTransform;
    //Place Hero at Startposition
    heroTransform.translate(m_map.m_startX * TileMap::GetTileWidth(), m_map.m_startY * TileMap::GetTileWidth() - 14);
    m_hero->setTransform(heroTransform);
    UpdateCamPosition();

    //Add random Items
    m_mapFill->FillLayer(MapFill::AdditionalItems, 1,2,4);

    //Place Stairs
    m_mapFill->PlaceItemAt(1,2,4,MapFillDungeon::TileStairsUp,m_map.m_startX, m_map.m_startY, false);
    m_mapFill->PlaceItemAt(1,2,4,MapFillDungeon::TileStairsDown,m_map.m_endX, m_map.m_endY, false);
    m_events.push_back(new MapEventStairs(false, m_map.m_startX, m_map.m_startY));
    m_events.push_back(new MapEventStairs(true, m_map.m_endX, m_map.m_endY));


    //Place Boss at Stairs
    sf::Sprite sprite;
    Texture* tex = TextureList::getTexture(TextureList::BossSpriteSheet);
    sprite.setTexture(*tex);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
    Node* enemy = new AnimatedNode(&sprite, tex->GetNumberAnimationSteps());
    enemy->setBoundingBox(sf::FloatRect(0.0f,0.0f,32.0f,32.0f));
    m_eventLayer->addChild(enemy);

    sf::Transform enemyTransform;
    //Place Enemy at Position
    enemyTransform.translate(m_map.m_endX * TileMap::GetTileWidth(), m_map.m_endY * TileMap::GetTileWidth());
    enemy->setTransform(enemyTransform);

    std::vector<Entity*>* enemies = new std::vector<Entity*>();
    //TODO: get Entities of this Map from somewhere else
    Entity* e = m_dungeonConfig->GetDungeonEnemy(m_lvlId);
    e->SetTeamId(1);
    enemies->push_back(e);
    e = m_dungeonConfig->GetDungeonBoss(m_lvlId);
    e->SetTeamId(1);
    enemies->push_back(e);
    e = m_dungeonConfig->GetDungeonEnemy(m_lvlId);
    e->SetTeamId(1);
    enemies->push_back(e);


    MapEventEnemy* mapEvent = new MapEventEnemy(&m_map, enemy,  0.0f, enemies);
    m_events.push_back(mapEvent);



    //Place Chests
    PlaceChest();

    //Place additional heroes with a chance of 50%
    if(rand() % 2 == 0)
        PlaceHero();

    m_map.writeToTileMap(*m_tileMap,0);
    m_map.writeToTileMap(*m_tileMapItems,1);
    m_map.writeToTileMap(*m_tileMapAboveHero,2);
    sf::Color halfTransparent(255,255,255,Configuration::GetInstance()->GetWallTransparency() * 255);
    m_map.writeToTileMap(*m_tileMapAboveWall,3, halfTransparent);
    m_map.writeToTileMap(*m_tileMapWallDecoration,4);


    int nrEnemies = m_map.GetWidth() * m_map.GetHeight() / 300;
    for(int i = 0; i < nrEnemies; i++)
    {
        SpawnEnemy();
    }
}

void SceneManagerDungeon::Tick()
{
    m_timeToNextSpawn -= GameController::getInstance()->GetTickTimeSeconds();
    if(m_timeToNextSpawn <= 0.0f)
    {
        SpawnEnemy();
    }
    SceneManagerMoveable::Tick();

    #ifdef DEBUG_FLAG

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        m_roomNumberNode->setVisibility(true);
    }
    else
    {
        m_roomNumberNode->setVisibility(false);
    }

    #endif // DEBUG_FLAG
}

void SceneManagerDungeon::SpawnEnemy()
{
    std::cout << "Spawn Enemy" << std::endl;
    sf::FloatRect heroPos = m_hero->getGlobalBoundingBox();
    float x = heroPos.left + heroPos.width/2;
    x /= TileMap::GetTileWidth();
    float y = heroPos.top + heroPos.height/2;
    y /= TileMap::GetTileWidth();
    int playerRoomNumber = m_map.GetRoomNr(x,y);
    std::pair<int, int>* pos;
    int nrTries = 0;
    //Try 10 Times to find a Position not in the same room as the Hero
    do
    {
        pos = m_generator.GetFreePosition();
        nrTries++;
    }
    while(m_map.GetRoomNr(pos->first, pos->second) == playerRoomNumber && nrTries < 10);

    SpawnEnemy(pos->first, pos->second, m_lvlId, 110.0f, 220.0f, 4, 2);

    m_timeToNextSpawn = rand()%10 + 10;
}

void SceneManagerDungeon::SpawnEnemy(int x, int y, int lvl, float movementSpeed, float followSpeed, int followRange, int nr)
{
    sf::Sprite sprite;
    Texture* tex = TextureList::getTexture(TextureList::EnemySpriteSheet);
    sprite.setTexture(*tex);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
    Node* enemy = new AnimatedNode(&sprite, tex->GetNumberAnimationSteps());
    enemy->setBoundingBox(sf::FloatRect(4.0f,16.0f,20.0f,16.0f));
    m_eventLayer->addChild(enemy);

    sf::Transform enemyTransform;
    //Place Enemy at Position
    enemyTransform.translate(x * TileMap::GetTileWidth(), y * TileMap::GetTileWidth() - 14);
    enemy->setTransform(enemyTransform);

    std::vector<Entity*>* enemies = new std::vector<Entity*>();
    //TODO: get Entities of this Map from somewhere else
    Entity* e;
    for(int i = 0; i < nr; i++)
    {
        e = m_dungeonConfig->GetDungeonEnemy(lvl);
        e->SetTeamId(1);
        enemies->push_back(e);
    }


    MapEventEnemy* mapEvent = new MapEventEnemy(&m_map, enemy,  movementSpeed, enemies);
    m_events.push_back(mapEvent);
    mapEvent->FollowPlayer(true, followRange, followSpeed);
}

void SceneManagerDungeon::PlaceChest()
{
    std::pair<int, int>* pos;
    //Add a maximum number of tries to prevent endless loop
    //For the first 100 try to find a dead end to put the chest into
    int nrTries = 0;
    bool placed;
    do
    {
        nrTries++;
        pos = m_generator.GetFreePosition(nrTries < 100);
        int roomNr = m_map.GetRoomNr(pos->first, pos->second);
        if((roomNr == m_map.m_endRoomNr || roomNr == m_map.m_startRoomNr) && nrTries < 200)
        {
            //Do not place chest in start or end Room
            continue;
        }
        placed = m_mapFill->PlaceItemAt(1,2,4,MapFillDungeon::TileChest,pos->first, pos->second);
    }
    while(!placed && nrTries < 200);
    std::cout << "Chest at " << pos->first << " " << pos->second << " nr tries:" << nrTries << " placeable: " << placed << std::endl;
    m_events.push_back(new MapEventChest(pos->first, pos->second));

    //look for adjacent free tile
    if(!m_map.DoesCollide(pos->first + 1, pos->second))
    {
        pos->first +=1;
    }
    else if(!m_map.DoesCollide(pos->first - 1, pos->second))
    {
        pos->first -=1;
    }
    else if(!m_map.DoesCollide(pos->first, pos->second + 1))
    {
        pos->second +=1;
    }
    else if(!m_map.DoesCollide(pos->first, pos->second - 1))
    {
        pos->second -=1;
    }

    SpawnEnemy(pos->first,pos->second,m_lvlId + 2, 0.0f, 256.0f,2,3);
}

void SceneManagerDungeon::PlaceHero()
{
    std::pair<int, int>* pos;
    //Add a maximum number of tries to prevent endless loop
    //For the first 100 try to find a dead end to put the hero into
    int nrTries = 0;
    int roomNr;
    do
    {
        nrTries++;
        pos = m_generator.GetFreePosition(nrTries < 100);
        roomNr = m_map.GetRoomNr(pos->first, pos->second);
    }
    while((roomNr == m_map.m_endRoomNr || roomNr == m_map.m_startRoomNr) && nrTries < 200);
    std::cout << "Hero at " << pos->first << " " << pos->second << " nr tries:" << nrTries << std::endl;

    //Display player sprite
    sf::Sprite* sprite = new sf::Sprite();
    Texture* tex = TextureList::getTexture(TextureList::HeroSpriteSheet);
    sprite->setTexture(*tex);
    sprite->setTextureRect(sf::IntRect(0,0,32,32));
    Node* hero = new DrawableNode(sprite);
    m_eventLayer->addChild(hero);

    sf::Transform heroTransform;
    //Place Enemy at Position
    heroTransform.translate(pos->first * TileMap::GetTileWidth(), pos->second * TileMap::GetTileWidth() - 14);
    hero->setTransform(heroTransform);


    m_events.push_back(new MapEventHero(hero, pos->first, pos->second));
}
