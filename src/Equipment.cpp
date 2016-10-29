#include "Equipment.h"
#include "Attack.h"

Equipment::Equipment()
{
    //ctor
}

Equipment::~Equipment()
{
    //dtor
}

bool Equipment::StaysAfterBattle()
{
    return true;
}

bool Equipment::IsStillActive()
{
    return true;
}

float Equipment::GetResistance(float resistanceValue, BattleEnums::AttackType type)
{
    return resistanceValue *= m_typeResistance[type];
}

void Equipment::AttackEntity(Attack* att, Entity* target, Entity* attacker)
{
    att->m_type.insert(m_attackTypes.begin(), m_attackTypes.end());
}

float Equipment::GetAttribute(float attributeValue, BattleEnums::Attribute attribute)
{
    return attributeValue + m_attributeBuffs[attribute];
}

int Equipment::GetActivationPriority()
{
    //Default Prio for Equipment
    return 0;
}
