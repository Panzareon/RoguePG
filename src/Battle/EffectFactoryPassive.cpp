#include "EffectFactoryPassive.h"
#include "EffectPassive.h"

EffectFactoryPassive::EffectFactoryPassive(std::function<void(PassiveEffect* addTo)>* func, int id) : EffectFactoryBase(id)
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
    return new EffectPassive(this, m_effectFunction, m_strengthCalculation.GetStrengthVector(value, target), &m_strengthCalculation, target);
}
