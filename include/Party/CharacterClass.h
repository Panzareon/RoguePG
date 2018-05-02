#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H

#include "Battle/SkillGenerator.h"
#include "SceneGraph/TextureList.h"
#include <vector>
#include <map>

class PartyMember;

class CharacterClass
{
    public:
        enum CharacterClassEnum{CharacterClassPaladin, CharacterClassMage, CharacterClassCleric, CharacterClassBarbarian, CharacterClassThief, CharacterClassVampire, CharacterClassWizard, CHARACTER_CLASS_END};
        CharacterClass(CharacterClassEnum chrClass, float skillChance, TextureList::TextureFiles battleSprite);
        virtual ~CharacterClass();
        static CharacterClass* GetCharacterClass(CharacterClassEnum chrClass);
        //Only returns unlocked Characters
        static CharacterClass* GetRandomCharacterClass();

        PartyMember* GetNewPartyMember();
        float GetSkillChance();
        float GetAttributePerLevel(BattleEnums::Attribute attr);

        SkillGenerator* GetSkillGenerator();
        Skill* GetNewSkill(PartyMember* user);

        std::string GetName();
        CharacterClassEnum GetClassType();

        TextureList::TextureFiles GetClassSprite();

    protected:
        static std::vector<CharacterClass*>* m_classes;

        TextureList::TextureFiles m_battleSprite;

        SkillGenerator m_skillGenerator;
        CharacterClassEnum m_classType;
        float m_skillChance;
        std::map<BattleEnums::Attribute, int> m_baseAttributes;
        std::map<BattleEnums::Attribute, float> m_attributesPerLevel;

        void SetBaseAttribute(BattleEnums::Attribute attr, int value);
        void SetAttributePerLevel(BattleEnums::Attribute attr, float value);

    private:
};

#endif // CHARACTERCLASS_H
