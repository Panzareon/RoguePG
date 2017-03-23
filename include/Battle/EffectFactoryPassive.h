#ifndef EFFECTFACTORYPASSIVE_H
#define EFFECTFACTORYPASSIVE_H

#include "EffectFactoryBase.h"

class EffectFactoryPassive : public EffectFactoryBase
{
    public:
        EffectFactoryPassive(std::function<void(std::vector<float>* strength, PassiveEffect* addTo)>* func, int id);
        virtual ~EffectFactoryPassive();

        //Returns new Instance of Effect with a strength defined by the value given, needs to be deleted
        virtual EffectBase* GetEffectWithValue(float value, BattleEnums::Target target);

    protected:
         std::function<void(std::vector<float>* strength, PassiveEffect* addTo)>* m_effectFunction;

    private:
};

#endif // EFFECTFACTORYPASSIVE_H
