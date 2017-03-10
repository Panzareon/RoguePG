#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H

#include "PartyMember.h"
#include "SkillGenerator.h"
#include "TextureList.h"
#include <vector>
#include <map>

class CharacterClass
{
    public:
        enum CharacterClassEnum{CharacterClassMage, CharacterClassBarbarian, CharacterClassPaladin, CharacterClassThief, CharacterClassCleric, CHARACTER_CLASS_END};
        CharacterClass(CharacterClassEnum chrClass, float skillChance, TextureList::TextureFiles battleSprite);
        virtual ~CharacterClass();
        static CharacterClass* GetCharacterClass(CharacterClassEnum chrClass);
        static CharacterClass* GetRandomCharacterClass();

        PartyMember* GetNewPartyMember();
        float GetSkillChance();
        float GetAttributePerLevel(BattleEnums::Attribute attr);

        SkillGenerator* GetSkillGenerator();
        Skill* GetNewSkill(PartyMember* user);

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
