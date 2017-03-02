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

        //Initialize all Textures
        int AnimationSteps = 1;
        switch(file)
        {
        case DungeonTileMap:
            filename = "TileMap.png";
            break;


        case HeroSpriteSheet:
            filename = "skeleton-large.png";
            break;
        case EnemySpriteSheet:
            filename = "skeleton-large.png";
            break;


        case BatBattleSprite:
            filename = "bat.png";
            break;
        case DeadWizardBattleSprite:
            filename = "deadWizard.png";
            break;
        case StoneGolemBattleSprite:
            filename = "stone-golem.png";
            break;
        case DefaultBattleSprite:
            filename = "rogue.png";
            break;

        case TargetCursor:
            filename = "target.png";
            break;

        case FireballAnimation:
            filename = "fireball.png";
            break;


        case DungeonBattleBackground:
            filename = "battle-background.png";
            break;


        case GameOverScreen:
            filename = "game-over.png";
            break;
        case InGameMenu:
            filename = "menu.png";
            break;
        case InGameMenuSelected:
            filename = "menu-selected.png";
            break;
        case EquipmentMenu:
            filename = "equipment-menu.png";
            break;
        case EquipmentSelected:
            filename = "equipment-selected.png";
            break;
        }
        Texture* newTexture = new Texture(AnimationSteps);
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
