#include "SceneManagerDungeon.h"

#include "DrawableNode.h"
#include "AnimatedNode.h"
#include "TileMap.h"
#include "MapFillDungeon.h"
#include "TextureList.h"

#include <iostream>


SceneManagerDungeon::SceneManagerDungeon(sf::RenderTarget * target, int windowWidth, int windowHeight, int tileWidth, int tileHeight): SceneManagerMoveable(target, windowWidth, windowHeight, tileWidth, tileHeight), m_generator(&m_map)
{
    //ctor
    //Define Tile Maps
    m_map.init(5);
    m_tileMap = new TileMap();
    m_tileMapItems = new TileMap();
    m_tileMapAboveHero = new TileMap();
    m_tileMapAboveWall = new TileMap();
    m_tileMapWallDecoration = new TileMap();

    m_tileMap->setTexture(TextureList::getTexture(TextureList::m_dungeonTileMap));
    m_tileMapItems->setTexture(TextureList::getTexture(TextureList::m_dungeonTileMap));
    m_tileMapAboveHero->setTexture(TextureList::getTexture(TextureList::m_dungeonTileMap));
    m_tileMapAboveWall->setTexture(TextureList::getTexture(TextureList::m_dungeonTileMap));
    m_tileMapWallDecoration->setTexture(TextureList::getTexture(TextureList::m_dungeonTileMap));

    //Build Scene Graph
    m_mainNode = new Node();
    m_belowHero = new Node();
    m_mainNode->addChild(m_belowHero);

    m_eventLayer = new Node();
    m_mainNode->addChild(m_eventLayer);

    m_aboveHero = new Node();
    m_mainNode->addChild(m_aboveHero);

    m_belowHero->addChild(new DrawableNode(m_tileMap));
    m_belowHero->addChild(new DrawableNode(m_tileMapItems));

    m_aboveHero->addChild(new DrawableNode(m_tileMapAboveHero));
    m_aboveHero->addChild(new DrawableNode(m_tileMapAboveWall));
    m_aboveHero->addChild(new DrawableNode(m_tileMapWallDecoration));


    //Add Hero
    sf::Sprite hero;
    hero.setTexture(*TextureList::getTexture(TextureList::m_heroSpriteSheet));
    hero.setTextureRect(sf::IntRect(15,13,32,36));
    m_hero = new AnimatedNode(hero);
    m_hero->setBoundingBox(sf::FloatRect(8.0f,22.0f,16.0f,16.0f));
    m_eventLayer->addChild(m_hero);

    //Generate Map

    m_generator.CellularAutomata(0.45f);

    m_generator.PlaceStartingPosition();
    sf::Transform heroTransform;
    //Place Hero at Startposition
    heroTransform.translate(m_map.m_startX * TileMap::GetTileWith(), m_map.m_startY * TileMap::GetTileWith() - 14);
    m_hero->setTransform(heroTransform);
    //m_generator.NumberRooms();

    MapFillDungeon mapFill(&m_map);
    //Fill Base Layer with walkable Tile
    mapFill.FillLayer(MapFill::Ground, 0);
    //Fill Wall
    mapFill.FillLayer(MapFill::Wall, 0,3);
    //Fill Wall Topping
    mapFill.FillLayer(MapFill::WallTopping, 3);
    //Add random Items
    mapFill.FillLayer(MapFill::AdditionalItems, 1,2,4);

    m_map.writeToTileMap(*m_tileMap,0);
    m_map.writeToTileMap(*m_tileMapItems,1);
    m_map.writeToTileMap(*m_tileMapAboveHero,2);
    sf::Color halfTransparent(255,255,255,220);
    m_map.writeToTileMap(*m_tileMapAboveWall,3, halfTransparent);
    m_map.writeToTileMap(*m_tileMapWallDecoration,4);
}

SceneManagerDungeon::~SceneManagerDungeon()
{
    //dtor
    delete m_tileMap;
    delete m_tileMapAboveHero;
    delete m_tileMapAboveWall;
    delete m_tileMapItems;
    delete m_tileMapWallDecoration;
}
