#ifndef SKILLGENERATOR_H
#define SKILLGENERATOR_H

#include "Enums.h"
#include "Skill.h"
#include <map>

class SkillGenerator
{
    public:
        SkillGenerator();
        virtual ~SkillGenerator();

        void AddSkillTarget(BattleEnums::Target target, float chance);
        void AddSkillAttackType(BattleEnums::AttackType attackType, float chance);
        void AddSkillEffectType(BattleEnums::EffectType effectType, float chance, bool positive);


        Skill* GetNewSkill(float strength);

    protected:
        std::map<float, BattleEnums::Target> m_skillTarget;
        std::map<float, BattleEnums::AttackType> m_skillAttackType;
        std::map<float, BattleEnums::EffectType> m_skillPositiveEffectType;
        std::map<float, BattleEnums::EffectType> m_skillNegativeEffectType;


        BattleEnums::Target GetRandomTarget();
        BattleEnums::AttackType GetRandomAttackType();
        BattleEnums::EffectType GetRandomEffectType(bool positive);

    private:
};

#endif // SKILLGENERATOR_H
