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
        case TextureFiles::DungeonTileMap:
            filename = "TileMap.png";
            break;
        case TextureFiles::DebugTileMap:
            filename = "TileMap-Test.png";
            break;



        case TextureFiles::HeroSpriteSheet:
            filename = "hero.png";
            AnimationSteps = 3;
            break;
        case TextureFiles::EnemySpriteSheet:
            filename = "enemy.png";
            AnimationSteps = 3;
            break;
        case TextureFiles::BossSpriteSheet:
            filename = "boss.png";
            AnimationSteps = 3;
            break;


        case TextureFiles::BatBattleSprite:
            filename = "bat.png";
            break;
        case TextureFiles::DeadWizardBattleSprite:
            filename = "deadWizard.png";
            break;
        case TextureFiles::StoneGolemBattleSprite:
            filename = "stone-golem.png";
            break;
        case TextureFiles::WindEyeBattleSprite:
            filename = "wind-eye.png";
            break;
        case TextureFiles::WaterSlimeBattleSprite:
            filename = "water-slime.png";
            break;
        case TextureFiles::IceGolemBattleSprite:
            filename = "ice-golem.png";
            break;
        case TextureFiles::IceSpiritBattleSprite:
            filename = "ice-spirit.png";
            break;


        case TextureFiles::MageBattleSprite:
            filename = "mage.png";
            break;
        case TextureFiles::BarbarianBattleSprite:
            filename = "barbarian.png";
            break;
        case TextureFiles::PaladinBattleSprite:
            filename = "paladin.png";
            break;
        case TextureFiles::ThiefBattleSprite:
            filename = "thief.png";
            break;
        case TextureFiles::ClericBattleSprite:
            filename = "cleric.png";
            break;
        case TextureFiles::WizardBattleSprite:
            filename = "wizard.png";
            break;
        case TextureFiles::VampireBattleSprite:
            filename = "vampire.png";
            break;
        case TextureFiles::DefaultBattleSprite:
            filename = "rogue.png";
            break;

        case TextureFiles::LockedCharacter:
            filename = "lock.png";
            break;

        case TextureFiles::TargetCursor:
            filename = "target.png";
            break;
        case TextureFiles::TimeArrow:
            filename = "time_arrow.png";
            break;

        case TextureFiles::FireballAnimation:
            filename = "fireball.png";
            break;
        case TextureFiles::WaterAnimation:
            filename = "water.png";
            break;
        case TextureFiles::EarthAnimation:
            filename = "stone.png";
            break;
        case TextureFiles::AirAnimation:
            filename = "wind.png";
            break;
        case TextureFiles::SwordAnimation:
            filename = "sword.png";
            break;


        case TextureFiles::DungeonBattleBackground:
            filename = "battle-background.png";
            break;


        case TextureFiles::GameOverScreen:
            filename = "game-over.png";
            break;
        case TextureFiles::InGameMenu:
            filename = "menu.png";
            break;
        case TextureFiles::InGameMenuSelected:
            filename = "menu-selected.png";
            break;
        case TextureFiles::EquipmentMenu:
            filename = "equipment-menu.png";
            break;
        case TextureFiles::EquipmentSelected:
            filename = "equipment-selected.png";
            break;
        case TextureFiles::StatusMenu:
            filename = "status-menu.png";
            break;
        case TextureFiles::DescriptionBox:
            filename = "description-box.png";
            break;

        case TextureFiles::MinimapHero:
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
