#ifndef EFFECTFACTORYBASE_H
#define EFFECTFACTORYBASE_H


#include "EffectBase.h"
#include <vector>
#include <set>
#include "StrengthCalculation.h"

class EffectFactoryBase
{
    public:
        EffectFactoryBase(int id, float chance = 1.0f);
        virtual ~EffectFactoryBase();

        //Returns new Instance of Effect with a strength defined by the value given, needs to be deleted
        virtual EffectBase* GetEffectWithValue(float value, BattleEnums::Target target) = 0;
        virtual EffectBase* GetEffectWithStrength(std::vector<float>* strength, BattleEnums::Target target) = 0;

        void AddAttackType(BattleEnums::AttackType type);
        void AddEffectType(BattleEnums::EffectType type);
        void SetNeedTarget(bool need);

        bool DoesContainAttackType(BattleEnums::AttackType type);
        bool DoesContainEffectType(BattleEnums::EffectType type);

        int GetId();
        float GetChance();

        StrengthCalculation* GetStrengthCalculation();

        //If the effect can be used with TargetNone
        bool DoesNeedTarget();

    protected:
        std::set<BattleEnums::AttackType> m_attackType;
        std::set<BattleEnums::EffectType> m_effectType;
        bool m_needsTarget;
        StrengthCalculation m_strengthCalculation;

        int m_id;
        float m_chance;

    private:
};

#endif // EFFECTFACTORYBASE_H
