#include "SceneManagerDungeon.h"

#include "DrawableNode.h"
#include "AnimatedNode.h"
#include "TileMap.h"
#include "MapFillDungeon.h"

#include <iostream>


SceneManagerDungeon::SceneManagerDungeon(sf::RenderTarget * target, int windowWidth, int windowHeight, int tileWidth, int tileHeight): SceneManagerMoveable(target, windowWidth, windowHeight, tileWidth, tileHeight), m_generator(&m_map)
{
    //ctor
    //Define Tile Maps
    m_map.init(5);
    m_tileMap = new TileMap();
    m_tileMapWall = new TileMap();
    m_tileMapItems = new TileMap();
    m_tileMapAboveHero = new TileMap();
    m_tileMapAboveWall = new TileMap();

    sf::String tileMapTexture = "texture/TileMap.png";
    if(!m_tileMap->setTexture(tileMapTexture))
    {
        std::cout << "Could not load Texture: " << tileMapTexture.toAnsiString() << std::endl;
    }
    if(!m_tileMapWall->setTexture("texture/TileMap.png"))
    {
        std::cout << "Could not load Texture: " << tileMapTexture.toAnsiString() << std::endl;
    }
    if(!m_tileMapItems->setTexture("texture/TileMap.png"))
    {
        std::cout << "Could not load Texture: " << tileMapTexture.toAnsiString() << std::endl;
    }
    if(!m_tileMapAboveHero->setTexture("texture/TileMap.png"))
    {
        std::cout << "Could not load Texture: " << tileMapTexture.toAnsiString() << std::endl;
    }
    if(!m_tileMapAboveWall->setTexture("texture/TileMap.png"))
    {
        std::cout << "Could not load Texture: " << tileMapTexture.toAnsiString() << std::endl;
    }

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
    m_belowHero->addChild(new DrawableNode(m_tileMapWall));

    m_aboveHero->addChild(new DrawableNode(m_tileMapAboveHero));
    m_aboveHero->addChild(new DrawableNode(m_tileMapAboveWall));


    //Add Hero
    //Todo: create and save Textures somewhere else
    sf::Texture* heroTexture = new sf::Texture();
    sf::String texturePath = "texture/skeleton-large.png";
    if(!heroTexture->loadFromFile(texturePath))
    {
        std::cout << "Could not load Texture: " << texturePath.toAnsiString() << std::endl;
    }
    sf::Sprite hero;
    hero.setTexture(*heroTexture);
    hero.setTextureRect(sf::IntRect(15,13,32,36));
    m_hero = new AnimatedNode(hero);
    m_hero->setBoundingBox(sf::FloatRect(8.0f,22.0f,16.0f,16.0f));
    m_eventLayer->addChild(m_hero);

    //Generate Map

    m_generator.CellularAutomata(0.45f);

    m_generator.PlaceStartingPosition();
    sf::Transform heroTransform;
    heroTransform.translate(m_map.m_startX * TileMap::GetTileMapWith(), m_map.m_startY * TileMap::GetTileMapWith());
    m_hero->setTransform(heroTransform);
    //m_generator.NumberRooms();

    MapFillDungeon mapFill(&m_map);
    mapFill.FillLayer(0);
    mapFill.FillLayer(1);
    mapFill.FillLayer(4);
    mapFill.FillLayer(2,3);

    m_map.writeToTileMap(*m_tileMap,0);
    m_map.writeToTileMap(*m_tileMapWall,1);
    m_map.writeToTileMap(*m_tileMapItems,2);
    m_map.writeToTileMap(*m_tileMapAboveHero,3);
    sf::Color halfTransparent(255,255,255,220);
    m_map.writeToTileMap(*m_tileMapAboveWall,4, halfTransparent);
}

SceneManagerDungeon::~SceneManagerDungeon()
{
    //dtor
}
