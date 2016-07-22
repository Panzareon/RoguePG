#include "TileMap.h"
#include <iostream>

TileMap::TileMap()
{
    //ctor
    m_tileWidth = 32;
    m_tileHeight = 32;
    m_halfTileWidth = m_tileWidth/2;
    m_halfTileHeight = m_tileHeight/2;
}

TileMap::~TileMap()
{
    //dtor
}
int TileMap::GetTileMapWith()
{
    return 32;
}
int TileMap::GetTileWith()
{
    return 32;
}

void TileMap::load(int** tiles, unsigned int width, unsigned int height, sf::Color color)
{

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 16);

    int id = 0;
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            if(tiles[i*2][j*2] == tiles[i*2 + 1][j*2] && tiles[i*2][j*2] == tiles[i*2][j*2 + 1] && tiles[i*2][j*2] == tiles[i*2 + 1][j*2 + 1])
            {
                // get the current tile number
                int tileNumber = tiles[i*2][j*2];

                //only add Vertice there is something to draw on it
                if(tileNumber != 0)
                {

                    // find its position in the tileset texture
                    int tu = (tileNumber % (m_tileset.getSize().x / m_tileWidth));
                    int tv = (tileNumber / (m_tileset.getSize().x / m_tileWidth));

                    // get a pointer to the current tile's quad
                    sf::Vertex* quad = &m_vertices[id];

                    // define its 4 corners
                    quad[0].position = sf::Vector2f(i * m_tileWidth, j * m_tileHeight);
                    quad[1].position = sf::Vector2f((i + 1) * m_tileWidth, j * m_tileHeight);
                    quad[2].position = sf::Vector2f((i + 1) * m_tileWidth, (j + 1) * m_tileHeight);
                    quad[3].position = sf::Vector2f(i * m_tileWidth, (j + 1) * m_tileHeight);

                    // define its 4 texture coordinates
                    quad[0].texCoords = sf::Vector2f(tu * m_tileWidth, tv * m_tileHeight);
                    quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileWidth, tv * m_tileHeight);
                    quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileWidth, (tv + 1) * m_tileHeight);
                    quad[3].texCoords = sf::Vector2f(tu * m_tileWidth, (tv + 1) * m_tileHeight);

                    // define its color
                    quad[0].color = color;
                    quad[1].color = color;
                    quad[2].color = color;
                    quad[3].color = color;

                    id += 4;
                }
            }
            else
            {
                for(int k = 0; k < 4; k++)
                {
                    // get the current tile number
                    int tileNumber = tiles[i*2 + k/2][j*2 + k%2];

                    //only add Vertice there is something to draw on it
                    if(tileNumber != 0)
                    {

                        // find its position in the tileset texture
                        int tu = (tileNumber % (m_tileset.getSize().x / m_tileWidth)) * 2 + k/2;
                        int tv = (tileNumber / (m_tileset.getSize().x / m_tileWidth)) * 2 + k%2;

                        // get a pointer to the current tile's quad
                        sf::Vertex* quad = &m_vertices[id];

                        // define its 4 corners
                        quad[0].position = sf::Vector2f((i*2 + k/2) * m_halfTileWidth, (j*2 + k%2) * m_halfTileHeight);
                        quad[1].position = sf::Vector2f(((i*2 + k/2) + 1) * m_halfTileWidth, (j*2 + k%2) * m_halfTileHeight);
                        quad[2].position = sf::Vector2f(((i*2 + k/2) + 1) * m_halfTileWidth, ((j*2 + k%2) + 1) * m_halfTileHeight);
                        quad[3].position = sf::Vector2f((i*2 + k/2) * m_halfTileWidth, ((j*2 + k%2) + 1) * m_halfTileHeight);

                        // define its 4 texture coordinates
                        quad[0].texCoords = sf::Vector2f(tu * m_halfTileWidth, tv * m_halfTileHeight);
                        quad[1].texCoords = sf::Vector2f((tu + 1) * m_halfTileWidth, tv * m_halfTileHeight);
                        quad[2].texCoords = sf::Vector2f((tu + 1) * m_halfTileWidth, (tv + 1) * m_halfTileHeight);
                        quad[3].texCoords = sf::Vector2f(tu * m_halfTileWidth, (tv + 1) * m_halfTileHeight);

                        // define its color
                        quad[0].color = color;
                        quad[1].color = color;
                        quad[2].color = color;
                        quad[3].color = color;

                        id += 4;
                    }
                }
            }
        }
    }
    //Remove unused Vertices
    m_vertices.resize(id);
}

bool TileMap::setTexture(const std::string& tileset)
{
    return m_tileset.loadFromFile(tileset);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
