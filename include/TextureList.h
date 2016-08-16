#ifndef TEXTURELIST_H
#define TEXTURELIST_H

#include <map>
#include "SFML/Graphics/Texture.hpp"

class TextureList
{
    public:
        virtual ~TextureList();


        //List of Texture file names
        static std::string m_dungeonTileMap;

        static std::string m_heroSpriteSheet;

        static std::string m_dungeonBattleBackground;

        static sf::Texture* getTexture(std::string filename);
    protected:
    private:
        static std::map<std::string, sf::Texture*> m_textures;
        TextureList();
};

#endif // TEXTURELIST_H
