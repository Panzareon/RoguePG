#include "Effect.h"

Effect::Effect(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::vector<float>* strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target)
{
    m_effectFunction = func;
    m_strength = strength;
    m_strengthCalculation = strengthCalculation;
    m_defaultTarget = target;
}

Effect::~Effect()
{
    //dtor
    delete m_strength;
}
void Effect::UseEffectOn(Entity* user, std::vector<Entity* >* targets)
{
    if(m_defaultTarget == BattleEnums::TargetSelf)
    {
        std::vector<Entity* >* target = new std::vector<Entity* >(1, user);
        (*m_effectFunction)(m_strength, user, target);
    }
    else
    {
        (*m_effectFunction)(m_strength, user, targets);
    }
}

float Effect::GetValue()
{
    return m_strengthCalculation->GetValue(m_strength, m_defaultTarget);
}

