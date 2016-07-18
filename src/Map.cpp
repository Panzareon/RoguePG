#include "Map.h"

Map::Map(int width, int height, int nrLayers)
{
    //ctor
    m_nrLayers = nrLayers;
    m_width = width;
    m_height = height;
    for(int i = 0; i < m_nrLayers; i++)
    {
        m_layers.push_back(new int*[m_width*2]);
        for(int j = 0; j < m_width*2; j++)
        {
            m_layers[i][j] = new int[m_height*2];
            for(int k = 0; k < m_height*2; k++)
                m_layers[i][j][k] = 0;
        }
    }
    m_tiles = new int*[m_width];
    for(int j = 0; j < m_width; j++)
        m_tiles[j] = new int[m_height];
    m_roomNr = new int*[m_width];
    for(int j = 0; j < m_width; j++)
        m_roomNr[j] = new int[m_height];
}

Map::~Map()
{
    //dtor
    for(int i = 0; i < m_nrLayers; i++)
    {
        for(int j = 0; j < m_width*2; j++)
            delete[] m_layers[i][j];
        delete[] m_layers[i];
    }
    for(int j = 0; j < m_width; j++)
        delete[] m_tiles[j];
    delete[] m_tiles;
    for(int j = 0; j < m_width; j++)
        delete[] m_roomNr[j];
    delete[] m_roomNr;
}
int Map::GetWidth()
{
    return m_width;
}

int Map::GetHeight()
{
    return m_height;
}


void Map::writeToTileMap(TileMap& in, int layer)
{
    in.load(m_layers.at(layer), m_width, m_height);
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

