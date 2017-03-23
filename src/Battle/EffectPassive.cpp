#include "EffectPassive.h"

EffectPassive::EffectPassive(EffectFactoryBase* factory, std::function<void(std::vector<float>* strength, PassiveEffect* addTo)>* func, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target)
                :EffectBase(factory,strength,strengthCalculation,target)
{
    //ctor
    m_addFunction = func;
}

EffectPassive::~EffectPassive()
{
    //dtor
}

void EffectPassive::AddToPassiveEffect(PassiveEffect* target)
{
    (*m_addFunction)(m_strength, target);
}
