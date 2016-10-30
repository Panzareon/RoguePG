#include "EffectFactory.h"

EffectFactory::EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, int id)
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

Effect* EffectFactory::GetEffectWithValue(float value, BattleEnums::Target target)
{
    return new Effect(m_effectFunction, m_strengthCalculation.GetStrengthVector(value, target), &m_strengthCalculation, target);
}
void EffectFactory::AddAttackType(BattleEnums::AttackType type)
{
    m_attackType.insert(type);
}

void EffectFactory::AddEffectType(BattleEnums::EffectType type)
{
    m_effectType.insert(type);
}

void EffectFactory::SetNeedTarget(bool need)
{
    m_needsTarget = need;
}


bool EffectFactory::DoesContainAttackType(BattleEnums::AttackType type)
{
    return m_attackType.find(type) != m_attackType.end();
}

bool EffectFactory::DoesContainEffectType(BattleEnums::EffectType type)
{
    return m_effectType.find(type) != m_effectType.end();
}

bool EffectFactory::DoesNeedTarget()
{
    return m_needsTarget;
}

StrengthCalculation* EffectFactory::GetStrengthCalculation()
{
    return &m_strengthCalculation;
}

int EffectFactory::GetId()
{
    return m_id;
}

