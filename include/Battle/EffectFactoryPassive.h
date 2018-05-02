#ifndef EFFECTFACTORYPASSIVE_H
#define EFFECTFACTORYPASSIVE_H

#include "EffectFactoryBase.h"

#include <functional>

class EffectFactoryPassive : public EffectFactoryBase
{
    public:
        EffectFactoryPassive(std::function<void(std::vector<float>* strength, PassiveEffect* addTo)>* func, int id, float chance = 1.0f);
        virtual ~EffectFactoryPassive();

        //Returns new Instance of Effect with a strength defined by the value given, needs to be deleted
        virtual EffectBase* GetEffectWithValue(float value, BattleEnums::Target target);
        virtual EffectBase* GetEffectWithStrength(std::vector<float>* strength, BattleEnums::Target target);

    protected:
        std::function<void(std::vector<float>* strength, PassiveEffect* addTo)>* m_effectFunction;

    private:
};

#endif // EFFECTFACTORYPASSIVE_H
