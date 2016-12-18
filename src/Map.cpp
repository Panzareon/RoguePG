#include "Map.h"
#include <cmath>

Map::Map(int width, int height)
{
    m_nrLayers = 0;

    m_startX = -1;
    m_startY = -1;
    m_width = width;
    m_height = height;

    m_tiles = new int*[m_width];
    for(unsigned int j = 0; j < m_width; j++)
        m_tiles[j] = new int[m_height];
    m_roomNr = new int*[m_width];
    for(unsigned int j = 0; j < m_width; j++)
        m_roomNr[j] = new int[m_height];
}

Map::~Map()
{
    //dtor
    for(unsigned int i = 0; i < m_nrLayers; i++)
    {
        for(unsigned int j = 0; j < m_width*2; j++)
            delete[] m_layers[i][j];
        delete[] m_layers[i];
    }
    for(unsigned int j = 0; j < m_width; j++)
        delete[] m_tiles[j];
    delete[] m_tiles;
    for(unsigned int j = 0; j < m_width; j++)
        delete[] m_roomNr[j];
    delete[] m_roomNr;
}
void Map::init(unsigned int nrLayers)
{
    //ctor
    m_nrLayers = nrLayers;
    for(unsigned int i = 0; i < m_nrLayers; i++)
    {
        m_layers.push_back(new int*[m_width*2]);
        for(unsigned int j = 0; j < m_width*2; j++)
        {
            m_layers[i][j] = new int[m_height*2];
            for(unsigned int k = 0; k < m_height*2; k++)
                m_layers[i][j][k] = 0;
        }
    }
}
int Map::GetWidth()
{
    return m_width;
}

int Map::GetHeight()
{
    return m_height;
}


void Map::writeToTileMap(TileMap& in, int layer, sf::Color color)
{
    in.load(m_layers.at(layer), m_width, m_height, color);
}

void Map::SetTileToWall(unsigned int x, unsigned int y)
{
    m_tiles[x][y] = Wall;
}

void Map::SetTileToSpace(unsigned int x, unsigned int y)
{
    m_tiles[x][y] = Space;
}

void Map::SetTileToType(unsigned int x, unsigned int y, TileType type)
{
    m_tiles[x][y] = type;
}

bool Map::IsTileWall(unsigned int x, unsigned int y)
{
    return m_tiles[x][y] == Wall;
}

void Map::SetRoomNr(unsigned int x, unsigned int y, int roomNr)
{
    m_roomNr[x][y] = roomNr;
    if(m_maxRoomNr < roomNr)
        m_maxRoomNr = roomNr;
    if(m_rooms.find(roomNr) == m_rooms.end())
        m_rooms.insert(std::pair<int,MapRoom>(roomNr, MapRoom(roomNr)));
    m_rooms.at(roomNr).AddPosition(x,y);
}

int Map::GetRoomNr(unsigned int x, unsigned int y)
{
    return m_roomNr[x][y];
}
void Map::SetTileId(unsigned int x, unsigned int y, int TileId, int layerId)
{
    SetTileId(x,y,TileId,TileId,TileId,TileId,layerId);
}

void Map::SetTileId(unsigned int x, unsigned int y, int TileIdTL, int TileIdTR, int TileIdBL, int TileIdBR, int layerId)
{
    if(x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
        m_layers[layerId][x*2][y*2] = TileIdTL;
        m_layers[layerId][x*2+1][y*2] = TileIdTR;
        m_layers[layerId][x*2][y*2+1] = TileIdBL;
        m_layers[layerId][x*2+1][y*2+1] = TileIdBR;
    }
}

int Map::GetTileId(unsigned int x, unsigned int y, int layerId)
{
    if(x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
        return m_layers[layerId][x*2][y*2];
    }
    return 0;
}


Map::TileType Map::GetTileType(unsigned int x, unsigned int y)
{
    if(x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
        return (TileType)m_tiles[x][y];
    }
    else
    {
        return Wall;
    }
}
bool Map::DoesCollide(unsigned int x, unsigned int y)
{
    TileType type = GetTileType(x,y);
    if(type == Wall || type == InteractableWall || type == BlockingItem)
        return true;
    return false;
}

bool Map::DoesCollide(sf::Rect<float> rect)
{
    for(int x = std::floor(rect.left / TileMap::GetTileWith()); x <= std::floor((rect.left + rect.width) / TileMap::GetTileWith()); x++)
    {
        for(int y = std::floor(rect.top / TileMap::GetTileWith()); y <= std::floor((rect.top + rect.height) / TileMap::GetTileWith()); y++)
        {
            if(DoesCollide(x,y))
                return true;
        }
    }
    return false;
}

