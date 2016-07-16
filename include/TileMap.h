#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap();
        virtual ~TileMap();
        bool setTexture(const std::string& tileset);
        void load(int** tiles, unsigned int width, unsigned int height);
    protected:
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

        unsigned int m_tileWidth;
        unsigned int m_tileHeight;
        unsigned int m_halfTileWidth;
        unsigned int m_halfTileHeight;
};

#endif // TILEMAP_H
