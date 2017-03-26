#include "EffectFactoryPassive.h"
#include "EffectPassive.h"

EffectFactoryPassive::EffectFactoryPassive(std::function<void(std::vector<float>* strength, PassiveEffect* addTo)>* func, int id) : EffectFactoryBase(id)
{
    //ctor
    m_effectFunction = func;
}

EffectFactoryPassive::~EffectFactoryPassive()
{
    //dtor
}

EffectBase* EffectFactoryPassive::GetEffectWithValue(float value, BattleEnums::Target target)
{
    std::vector<float>* strength = m_strengthCalculation.GetStrengthVector(value, target);
    return GetEffectWithStrength(strength, target);
}

EffectBase* EffectFactoryPassive::GetEffectWithStrength(std::vector<float>* strength, BattleEnums::Target target)
{
    return new EffectPassive(this, m_effectFunction, strength, m_strengthCalculation.GetValue(strength, target), target);
}
