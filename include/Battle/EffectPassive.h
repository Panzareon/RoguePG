#ifndef EFFECTPASSIVE_H
#define EFFECTPASSIVE_H

#include <functional>
#include "EffectBase.h"

class EffectPassive : public EffectBase
{
    public:
        EffectPassive(EffectFactoryBase* factory, std::function<void(PassiveEffect* addTo)>* func, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target);
        virtual ~EffectPassive();

        virtual void AddToPassiveEffect(PassiveEffect* target);

    protected:
        std::function<void(PassiveEffect* addTo)>* m_addFunction;
    private:
};

#endif // EFFECTPASSIVE_H
