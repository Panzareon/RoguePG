#include "MapGeneration/Map.h"
#include <cmath>

Map::Map()
{
    m_nrLayers = 0;

    m_startX = -1;
    m_startY = -1;
}
Map::Map(int width, int height)
{
    m_nrLayers = 0;

    m_startX = -1;
    m_startY = -1;
    InitSize(width, height);
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

void Map::InitSize(int width, int height)
{
    m_width = width;
    m_height = height;

    m_tiles = new int*[m_width];
    for(unsigned int j = 0; j < m_width; j++)
    {
        m_tiles[j] = new int[m_height];
        for(unsigned int k = 0; k < m_height; k++)
            m_tiles[j][k] = 0;
    }

    m_roomNr = new int*[m_width];
    for(unsigned int j = 0; j < m_width; j++)
    {
        m_roomNr[j] = new int[m_height];
        for(unsigned int k = 0; k < m_height; k++)
            m_roomNr[j][k] = 0;
    }
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
int Map::GetWidth() const
{
    return m_width;
}

int Map::GetHeight() const
{
    return m_height;
}


void Map::writeToTileMap(TileMap& in, int layer, sf::Color color)
{
    in.load(m_layers.at(layer), m_width, m_height, color);
}

void Map::SetTileToType(unsigned int x, unsigned int y, int type)
{
    if(x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
        m_tiles[x][y] = type;
    }
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

void Map::RoomsAreAdjacent(int roomNr1, int roomNr2)
{
    MapRoom* room1 = &m_rooms.at(roomNr1);
    MapRoom* room2 = &m_rooms.at(roomNr2);
    room1->IsAdjacentTo(room2);
    room2->IsAdjacentTo(room1);
}

std::map<int, MapRoom>* Map::GetAllRooms()
{
    return &m_rooms;
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


int Map::GetTileType(unsigned int x, unsigned int y)
{
    if(x >= 0 && y >= 0 && x < m_width && y < m_height)
    {
        return m_tiles[x][y];
    }
    else
    {
        return 0;
    }
}

void Map::AddCollidingType(int type)
{
    m_collidingTiles.push_back(type);
}

bool Map::DoesCollide(unsigned int x, unsigned int y)
{
    if(x < 0 || y < 0 || x >= m_width || y >= m_height)
        return true;
    int type = GetTileType(x,y);
    for(int i = 0; i < m_collidingTiles.size(); i++)
    {
        if(type == m_collidingTiles[i])
            return true;
    }
    return false;
}

bool Map::DoesCollide(sf::Rect<float> rect)
{
    for(int x = (int)std::floor(rect.left / TileMap::GetTileWidth()); x <= std::floor((rect.left + rect.width) / TileMap::GetTileWidth()); x++)
    {
        for(int y = (int)std::floor(rect.top / TileMap::GetTileWidth()); y <= std::floor((rect.top + rect.height) / TileMap::GetTileWidth()); y++)
        {
            if(DoesCollide(x,y))
                return true;
        }
    }
    return false;
}

bool Map::DoesCollide(unsigned int fromX, unsigned int fromY, unsigned int toX, unsigned int toY)
{
    if(abs((int)fromX - (int)toX) > abs((int)fromY - (int)toY))
    {
        if(fromX > toX)
        {
            int x = toX;
            int y = toY;
            toX = fromX;
            toY = fromY;
            fromX = x;
            fromY = y;
        }

        int yStep = 1;
        if(fromY > toY)
            yStep = -1;

        int dX = abs((int)toX - (int)fromX);
        int dY = abs((int)toY - (int)fromY);
        int fehler = dX / 2;
        int y = fromY;
        for(unsigned int x = fromX; x <= toX; x++)
        {
            if(DoesCollide(x,y))
                return true;
            fehler -= dY;
            if(fehler < 0)
            {
                fehler += dX;
                y += yStep;
                if(DoesCollide(x,y))
                    return true;
            }
        }
    }
    else
    {
        if(fromY > toY)
        {
            int x = toX;
            int y = toY;
            toX = fromX;
            toY = fromY;
            fromX = x;
            fromY = y;
        }

        int xStep = 1;
        if(fromX > toX)
            xStep = -1;

        int dX = abs((int)toX - (int)fromX);
        int dY = abs((int)toY - (int)fromY);
        int fehler = dY / 2;
        int x = fromX;
        for(unsigned int y = fromY; y <= toY; y++)
        {
            if(DoesCollide(x,y))
                return true;
            fehler -= dX;
            if(fehler < 0)
            {
                fehler += dY;
                x += xStep;
                if(DoesCollide(x,y))
                    return true;
            }
        }
    }
    return false;
}
