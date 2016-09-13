#include "TextureList.h"
#include "InvalidArgumentException.h"

TextureList::TextureList()
{
    //ctor
}

TextureList::~TextureList()
{
    //dtor
}
std::map<std::string, sf::Texture*> TextureList::m_textures;
//List of Texture file names
std::string TextureList::m_dungeonTileMap = "TileMap.png";

std::string TextureList::m_heroSpriteSheet = "skeleton-large.png";

std::string TextureList::m_dungeonBattleBackground = "battle-background.png";


sf::Texture* TextureList::getTexture(std::string filename)
{
    if(m_textures.find(filename) == m_textures.end())
    {
        std::string texturePath = "texture/";
        texturePath += filename;
        sf::Texture* newTexture = new sf::Texture();
        if(!newTexture->loadFromFile(texturePath))
        {
            std::string msg("Could not load Texture: ");
            msg.append(texturePath);
            throw InvalidArgumentException(msg);
            return 0;
        }
        m_textures.insert(std::make_pair(filename, newTexture));
    }
    return m_textures[filename];
}
