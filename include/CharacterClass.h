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

        void AddSkillTarget(BattleEnums::Target target, float chance);
        void AddSkillAttackType(BattleEnums::AttackType attackType, float chance);
        void AddSkillEffectType(BattleEnums::EffectType effectType, float chance);
    protected:
        static std::vector<CharacterClass*>* m_classes;

        CharacterClassEnum m_classType;
        float m_skillChance;
        std::map<float, BattleEnums::Target> m_skillTarget;
        std::map<float, BattleEnums::AttackType> m_skillAttackType;
        std::map<float, BattleEnums::EffectType> m_skillEffectType;


        BattleEnums::Target GetRandomTarget();
        BattleEnums::AttackType GetRandomAttackType();
        BattleEnums::EffectType GetRandomEffectType();
    private:
};

#endif // CHARACTERCLASS_H
