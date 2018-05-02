#include "EffectFactoryBase.h"

EffectFactoryBase::EffectFactoryBase(int id, float chance)
{
    //ctor
    m_id = id;
    m_chance = chance;
}

EffectFactoryBase::~EffectFactoryBase()
{
    //dtor
}

void EffectFactoryBase::AddAttackType(BattleEnums::AttackType type)
{
    m_attackType.insert(type);
}

void EffectFactoryBase::AddEffectType(BattleEnums::EffectType type)
{
    m_effectType.insert(type);
}

void EffectFactoryBase::SetNeedTarget(bool need)
{
    m_needsTarget = need;
}


bool EffectFactoryBase::DoesContainAttackType(BattleEnums::AttackType type)
{
    return m_attackType.find(type) != m_attackType.end();
}

bool EffectFactoryBase::DoesContainEffectType(BattleEnums::EffectType type)
{
    return m_effectType.find(type) != m_effectType.end();
}

bool EffectFactoryBase::DoesNeedTarget()
{
    return m_needsTarget;
}

StrengthCalculation* EffectFactoryBase::GetStrengthCalculation()
{
    return &m_strengthCalculation;
}

int EffectFactoryBase::GetId()
{
    return m_id;
}

float EffectFactoryBase::GetChance()
{
    return m_chance;
}

