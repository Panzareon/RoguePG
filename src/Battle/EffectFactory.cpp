#include "Battle/EffectFactory.h"

#include <iostream>

EffectFactory::EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* func, int id)
{
    m_effectFunction = func;
    m_needsTarget = true;
    m_id = id;
}



EffectFactory::~EffectFactory()
{
    //dtor
    delete m_effectFunction;
}

EffectBase* EffectFactory::GetEffectWithValue(float value, BattleEnums::Target target)
{
    Effect* ret = new Effect(this, m_effectFunction, m_strengthCalculation.GetStrengthVector(value, target), &m_strengthCalculation, target);
    ret->SetAnimation(AnimationFactory::GetAnimationTypeFor(&m_attackType, &m_effectType));
    return ret;
}
