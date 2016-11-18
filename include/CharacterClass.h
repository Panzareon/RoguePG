#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H

#include "PartyMember.h"
#include <vector>
#include <map>

class CharacterClass
{
    public:
        enum CharacterClassEnum{CharacterClassFireMage, CHARACTER_CLASS_END};
        CharacterClass(CharacterClassEnum chrClass, float skillChance);
        virtual ~CharacterClass();
        static CharacterClass* GetCharacterClass(CharacterClassEnum chrClass);
        static CharacterClass* GetRandomCharacterClass();

        PartyMember* GetNewPartyMember();
        Skill* GetNewSkill(PartyMember* user);
        float GetSkillChance();
        float GetAttributePerLevel(BattleEnums::Attribute attr);

        void AddSkillTarget(BattleEnums::Target target, float chance);
        void AddSkillAttackType(BattleEnums::AttackType attackType, float chance);
        void AddSkillEffectType(BattleEnums::EffectType effectType, float chance, bool positive);
    protected:
        static std::vector<CharacterClass*>* m_classes;

        CharacterClassEnum m_classType;
        float m_skillChance;
        std::map<float, BattleEnums::Target> m_skillTarget;
        std::map<float, BattleEnums::AttackType> m_skillAttackType;
        std::map<float, BattleEnums::EffectType> m_skillPositiveEffectType;
        std::map<float, BattleEnums::EffectType> m_skillNegativeEffectType;
        std::map<BattleEnums::Attribute, int> m_baseAttributes;
        std::map<BattleEnums::Attribute, float> m_attributesPerLevel;

        void SetBaseAttribute(BattleEnums::Attribute attr, int value);
        void SetAttributePerLevel(BattleEnums::Attribute attr, float value);

        BattleEnums::Target GetRandomTarget();
        BattleEnums::AttackType GetRandomAttackType();
        BattleEnums::EffectType GetRandomEffectType(bool positive);
    private:
};

#endif // CHARACTERCLASS_H
