#include "SceneGraph/TextureList.h"
#include "Exception/InvalidArgumentException.h"

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
        case DebugTileMap:
            filename = "TileMap-Test.png";
            break;



        case HeroSpriteSheet:
            filename = "hero.png";
            AnimationSteps = 3;
            break;
        case EnemySpriteSheet:
            filename = "enemy.png";
            AnimationSteps = 3;
            break;
        case BossSpriteSheet:
            filename = "boss.png";
            AnimationSteps = 3;
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
        case WindEyeBattleSprite:
            filename = "wind-eye.png";
            break;
        case WaterSlimeBattleSprite:
            filename = "water-slime.png";
            break;
        case IceGolemBattleSprite:
            filename = "ice-golem.png";
            break;
        case IceSpiritBattleSprite:
            filename = "ice-spirit.png";
            break;


        case MageBattleSprite:
            filename = "mage.png";
            break;
        case BarbarianBattleSprite:
            filename = "barbarian.png";
            break;
        case PaladinBattleSprite:
            filename = "paladin.png";
            break;
        case ThiefBattleSprite:
            filename = "thief.png";
            break;
        case ClericBattleSprite:
            filename = "cleric.png";
            break;
        case WizardBattleSprite:
            filename = "wizard.png";
            break;
        case VampireBattleSprite:
            filename = "vampire.png";
            break;
        case DefaultBattleSprite:
            filename = "rogue.png";
            break;

        case TargetCursor:
            filename = "target.png";
            break;
        case TimeArrow:
            filename = "time_arrow.png";
            break;

        case FireballAnimation:
            filename = "fireball.png";
            break;
        case WaterAnimation:
            filename = "water.png";
            break;
        case EarthAnimation:
            filename = "stone.png";
            break;
        case AirAnimation:
            filename = "wind.png";
            break;
        case SwordAnimation:
            filename = "sword.png";
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
        case StatusMenu:
            filename = "status-menu.png";
            break;
        case DescriptionBox:
            filename = "description-box.png";
            break;

        case MinimapHero:
            filename = "hero-minimap.png";
            AnimationSteps = 2;
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
