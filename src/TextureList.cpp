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
std::map<TextureList::TextureFiles, Texture*> TextureList::m_textures;

Texture* TextureList::getTexture(TextureFiles file)
{
    if(m_textures.find(file) == m_textures.end())
    {
        std::string filename;
        std::string texturePath = "texture/";
        Texture* newTexture;

        //Initialize all Textures
        switch(file)
        {
        case DungeonTileMap:
            newTexture = new Texture();
            filename = "TileMap.png";
            break;


        case HeroSpriteSheet:
            newTexture = new Texture(4);
            filename = "skeleton-large.png";
            break;
        case DefaultBattleSprite:
            newTexture = new Texture();
            filename = "rogue.png";
            break;
        case TargetCursor:
            newTexture = new Texture();
            filename = "target.png";
            break;


        case DungeonBattleBackground:
            newTexture = new Texture();
            filename = "battle-background.png";
            break;
        }
        texturePath += filename;
        if(!newTexture->loadFromFile(texturePath))
        {
            std::string msg("Could not load Texture: ");
            msg.append(texturePath);
            throw InvalidArgumentException(msg);
            return 0;
        }
        m_textures.insert(std::make_pair(file, newTexture));
    }
    return m_textures[file];
}
