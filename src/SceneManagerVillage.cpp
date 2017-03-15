#include "SceneManagerVillage.h"
#include "MapEventShop.h"

SceneManagerVillage::SceneManagerVillage(int tileWidth, int tileHeight, unsigned int seed, MapFill* mapFill) : SceneManagerMoveable (tileWidth, tileHeight), m_generator(&m_map, seed, (MapFillVillage*)mapFill)
{
    //ctor
    m_mapFill = mapFill;
    m_mapFill->SetMap(&m_map);
    m_map.init(5);

    m_map.m_startX = 0;
    m_map.m_startY = rand() % tileHeight;

    m_generator.PlaceHouses(6,3, tileHeight*tileWidth / 100);

    m_generator.PlaceStreets();

    AddShops();

    //Fill Base Layer with walkable Tile
    m_mapFill->FillLayer(MapFill::Ground, 0);
    //Fill Wall
    m_mapFill->FillLayer(MapFill::Wall, 0,3);
    //Fill Wall Topping
    m_mapFill->FillLayer(MapFill::WallTopping, 3);


    sf::Transform heroTransform;
    //Place Hero at Startposition
    heroTransform.translate(m_map.m_startX * TileMap::GetTileWith(), m_map.m_startY * TileMap::GetTileWith() - 14);
    m_hero->setTransform(heroTransform);
    UpdateCamPosition();

    //Add random Items
    m_mapFill->FillLayer(MapFill::AdditionalItems, 1,2,4);


    m_map.writeToTileMap(*m_tileMap,0);
    m_map.writeToTileMap(*m_tileMapItems,1);
    m_map.writeToTileMap(*m_tileMapAboveHero,2);
    m_map.writeToTileMap(*m_tileMapAboveWall,3);
    m_map.writeToTileMap(*m_tileMapWallDecoration,4);
}

SceneManagerVillage::~SceneManagerVillage()
{
    //dtor
}

void SceneManagerVillage::AddShops()
{
    for(int i = 0; i < MapEventShop::SHOP_TYPES_END; i++)
    {
        std::pair<int,int> pos = m_generator.PopDoor();
        m_mapFill->PlaceItemAt(1,2,4,(MapFillVillage::TileIndex)(MapFillVillage::TileSwordShop + i),pos.first, pos.second - 3, false);
    }
}
