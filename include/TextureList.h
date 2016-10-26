#ifndef TEXTURELIST_H
#define TEXTURELIST_H

#include <map>
#include "Texture.h"

class TextureList
{
    public:
        enum TextureFiles{
            DungeonTileMap,

            HeroSpriteSheet, DefaultBattleSprite,

            TargetCursor,

            DungeonBattleBackground
        };
        virtual ~TextureList();


        //List of Texture file names
        static Texture* getTexture(TextureFiles file);
    protected:
    private:
        static std::map<TextureFiles, Texture*> m_textures;
        TextureList();
};

#endif // TEXTURELIST_H
