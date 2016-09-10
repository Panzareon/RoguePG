#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include <vector>
#include <set>
#include <functional>

#include "Effect.h"

class EffectFactory
{
    public:
        EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::function<std::vector<float>*(float, BattleEnums::Target)>* valueToStrength);
        virtual ~EffectFactory();

        //Returns new Instance of Effect with a strength defined by the value given, needs to be deleted
        Effect* GetEffectWithValue(float value, BattleEnums::Target target);

        void AddAttackType(BattleEnums::AttackType type);
        void AddEffectType(BattleEnums::EffectType type);
        void SetNeedTarget(bool need);

        bool DoesContainAttackType(BattleEnums::AttackType type);
        bool DoesContainEffectType(BattleEnums::EffectType type);
        //If the effect can be used with TargetNone
        bool DoesNeedTarget();
    protected:
    private:
        //Function Pointer to Function that implements the Effect
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* m_effectFunction;

        //Function that calculates Strength for the Effect given a value how strong it should be
        std::function<std::vector<float>*(float, BattleEnums::Target)>* m_valueToStrength;

        std::set<BattleEnums::AttackType> m_attackType;
        std::set<BattleEnums::EffectType> m_effectType;
        bool m_needsTarget;
};

#endif // EFFECTFACTORY_H
