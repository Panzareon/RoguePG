#include "SceneManager/SceneManagerVillage.h"
#include "MapGeneration/MapEventShop.h"
#include "MapGeneration/MapEventDungeonEntrance.h"


SceneManagerVillage::SceneManagerVillage()
{

}


SceneManagerVillage::SceneManagerVillage(int tileWidth, int tileHeight, unsigned int seed, MapFill* mapFill) : SceneManagerMoveable (tileWidth, tileHeight)
{
    //ctor
    m_mapFill = std::unique_ptr<MapFill>(mapFill);
    Generate();
    m_seed = seed;
}

SceneManagerVillage::~SceneManagerVillage()
{
    //dtor
}

void SceneManagerVillage::Generate()
{
    m_generator.Init(&m_map, m_seed, (MapFillVillage*)m_mapFill.get());
    m_map.init(5);
    m_mapFill->SetMap(&m_map);

    m_minimapColor.resize(MapFillVillage::TILE_TYPE_END);
    m_minimapColor[MapFillVillage::Wall] = sf::Color::White;
    m_minimapColor[MapFillVillage::Space] = sf::Color::Black;
    m_minimapColor[MapFillVillage::Street] = sf::Color::Yellow;
    m_minimapColor[MapFillVillage::BlockingItem] = sf::Color::Black;
    m_minimapColor[MapFillVillage::WalkthroughItem] = sf::Color::Black;
    m_minimapColor[MapFillVillage::Stairs] = sf::Color::Red;

    int tileWidth = m_map.GetWidth();
    int tileHeight = m_map.GetHeight();
    m_map.m_startX = 0;
    m_map.m_startY = rand() % tileHeight;

    m_map.m_endX = rand()% tileWidth;
    m_map.m_endY = tileHeight - 1;

    m_mapFill->PlaceItemAt(1,2,4,MapFillVillage::TileStairsDown,m_map.m_endX, m_map.m_endY, false);
    m_events.push_back(new MapEventDungeonEntrance( m_map.m_endX, m_map.m_endY));

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
    if(m_newHeroPos)
    {
        heroTransform.translate(m_heroX, m_heroY);
    }
    else
    {
        heroTransform.translate(m_map.m_startX * TileMap::GetTileWidth(), m_map.m_startY * TileMap::GetTileWidth() - 14);
    }
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

void SceneManagerVillage::AddShops()
{
    for(int i = 0; i < MapEventShop::SHOP_TYPES_END && m_generator.GetNrOfDoors() >= 1; i++)
    {
        std::pair<int,int> pos = m_generator.PopDoor();
        m_mapFill->PlaceItemAt(1,2,4,(MapFillVillage::TileIndex)(MapFillVillage::TileSwordShop + i),pos.first, pos.second - 3, false);
        m_events.push_back(new MapEventShop(pos.first, pos.second - 1, (MapEventShop::ShopTypes)i));
    }
}

SceneManager::SceneManagerType SceneManagerVillage::GetType()
{
    return TypeVillage;
}
