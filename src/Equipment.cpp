#include "Equipment.h"
#include "Attack.h"
#include "Entity.h"

Equipment::Equipment(int itemId) : Item(itemId)
{
    //ctor
    m_target = nullptr;
}

Equipment::~Equipment()
{
    //dtor
}

void Equipment::OnEffectStart()
{
    //TODO: Add additional Effects of this Equipment to the target
}

void Equipment::EquipTo(Entity* target)
{
    m_target = target;
    target->AddPassiveEffect(this);
}

void Equipment::UnEquip()
{
    m_target = nullptr;
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

bool Equipment::IsEquipment()
{
    return true;
}

