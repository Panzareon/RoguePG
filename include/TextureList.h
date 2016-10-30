#ifndef TEXTURELIST_H
#define TEXTURELIST_H

#include <map>
#include "Texture.h"

class TextureList
{
    public:
        //List of Texture file names
        enum TextureFiles{
            DungeonTileMap,

            HeroSpriteSheet,

            BatBattleSprite, DefaultBattleSprite,

            TargetCursor,

            FireballAnimation,

            DungeonBattleBackground
        };
        virtual ~TextureList();


        static Texture* getTexture(TextureFiles file);
    protected:
    private:
        static std::map<TextureFiles, Texture*> m_textures;
        TextureList();
};

#endif // TEXTURELIST_H
