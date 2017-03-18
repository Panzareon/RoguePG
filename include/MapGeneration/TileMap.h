#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        //Get number of Tiles in the Tile map per row
        static int GetTileMapWith();
        //Get number of Pixels in width and height of a Tile in the Tile map
        static int GetTileWidth();
        TileMap();
        virtual ~TileMap();
        void setTexture(sf::Texture* texture);
        void load(int** tiles, unsigned int width, unsigned int height, sf::Color color = sf::Color::White);
    protected:
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::VertexArray m_vertices;
        sf::Texture* m_tileset;

        unsigned int m_tileWidth;
        unsigned int m_tileHeight;
        unsigned int m_halfTileWidth;
        unsigned int m_halfTileHeight;

};

#endif // TILEMAP_H
