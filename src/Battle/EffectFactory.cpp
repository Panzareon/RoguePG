#include "Battle/EffectFactory.h"

#include <iostream>

EffectFactory::EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* func, int id, float chance) : EffectFactoryBase(id, chance)
{
    m_effectFunction = func;
    m_needsTarget = true;
}



EffectFactory::~EffectFactory()
{
    //dtor
    delete m_effectFunction;
}

EffectBase* EffectFactory::GetEffectWithValue(float value, BattleEnums::Target target)
{
    std::vector<float>* strength = m_strengthCalculation.GetStrengthVector(value, target);
    return GetEffectWithStrength(strength, target);
}

EffectBase* EffectFactory::GetEffectWithStrength(std::vector<float>* strength, BattleEnums::Target target)
{
    Effect* ret = new Effect(this, m_effectFunction, strength, m_strengthCalculation.GetValue(strength, target), target);
    ret->SetAnimation(AnimationFactory::GetAnimationTypeFor(&m_attackType, &m_effectType));
    return ret;
}
