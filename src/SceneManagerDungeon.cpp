#include "SceneManagerDungeon.h"

#include "DrawableNode.h"
#include "TileMap.h"
#include "MapFillDungeon.h"

SceneManagerDungeon::SceneManagerDungeon(): m_map(30,30,5), m_generator(&m_map)
{
    //ctor
    //Define Tile Maps
    m_tileMap = new TileMap();
    m_tileMapWall = new TileMap();
    m_tileMapItems = new TileMap();
    m_tileMapAboveHero = new TileMap();
    m_tileMapAboveWall = new TileMap();
    m_tileMap->setTexture("texture/TileMap.png");
    m_tileMapWall->setTexture("texture/TileMap.png");
    m_tileMapItems->setTexture("texture/TileMap.png");
    m_tileMapAboveHero->setTexture("texture/TileMap.png");
    m_tileMapAboveWall->setTexture("texture/TileMap.png");

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

    //Generate Map

    m_generator.CellularAutomata(0.45f);

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
