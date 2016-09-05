#include "EffectFactory.h"

EffectFactory::EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::function<std::vector<float>*(float, BattleEnums::Target)>* valueToStrength)
{
    m_effectFunction = func;
    m_valueToStrength = valueToStrength;
}



EffectFactory::~EffectFactory()
{
    //dtor
    delete m_valueToStrength;
    delete m_effectFunction;
}

Effect* EffectFactory::GetEffectWithValue(float value, BattleEnums::Target target)
{
    return new Effect(m_effectFunction, (*m_valueToStrength)(value, target));
}
