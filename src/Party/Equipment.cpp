#include "Party/Equipment.h"
#include "Battle/Attack.h"
#include "Battle/Entity.h"
#include "Battle/Skill.h"
#include "Controller/Localization.h"

#include <iostream>

Equipment::Equipment(int itemId, EquipmentPosition pos) : Item(itemId, Item::ItemTypeEquipment)
{
    //ctor
    m_target = nullptr;
    m_position = pos;
    m_neededExpMultiplier = 20;
    for(int i = 0; i < (int)BattleEnums::ATTACK_TYPE_END; i++)
    {
        m_typeResistance[(BattleEnums::AttackType)i] = 1.0f;
    }
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
}

void Equipment::UnEquip()
{
    m_target = nullptr;
}

Entity* Equipment::GetEquipTarget()
{
    return m_target;
}

bool Equipment::IsEquipped()
{
    return m_target != nullptr;
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

void Equipment::AddExp(int exp)
{
    AddExp(m_target, exp);
}

void Equipment::AddExp(Entity* target, int exp)
{
    initExpAndLevel(target);
    if(!CanLearnSomething(target))
        return;
    m_exp[target] += exp;
    while(GetEquipmentExpPercent(target) >= 1.0)
    {
        LevelUp(target);
    }
}

Equipment::EquipmentPosition Equipment::GetEquipmentPosition()
{
    return m_position;
}

int Equipment::GetEquipmentExp()
{
    return GetEquipmentExp(m_target);
}

float Equipment::GetEquipmentExpPercent()
{
    return GetEquipmentExp(m_target);
}

float Equipment::GetEquipmentExpPercent(Entity* target)
{
    initExpAndLevel(target);
    return ((float)m_exp[target] - NeededExp(m_level[target] - 1)) / (float)(NeededExp(m_level[target]));
}

int Equipment::NeededExp(int lvl)
{
    return lvl * lvl * m_neededExpMultiplier;
}

int Equipment::GetLevel()
{
    return GetLevel(m_target);
}

int Equipment::GetEquipmentExp(Entity* target)
{
    initExpAndLevel(target);
    return m_exp[target];
}

int Equipment::GetLevel(Entity* target)
{
    initExpAndLevel(target);
    return m_level[target];
}

std::map<int, std::shared_ptr<Skill>>*  Equipment::GetSkillsToLearn()
{
    return &m_skillsToLearn;
}

bool Equipment::CanLearnSomething(Entity* target)
{
    initExpAndLevel(target);
    //Checks if the is a skill target has not learned yet from this Equipment
    //Check if this Equipment actually can learn something
    if(m_skillsToLearn.size() == 0)
        return false;
    //Check if last Skill is already learned
    if(m_skillsToLearn.rbegin()->first <= m_level[target])
        return false;
    return true;
}

void Equipment::LevelUp(Entity* target)
{
    m_level[target]++;
    auto it = m_skillsToLearn.find(m_level[target]);
    if(it != m_skillsToLearn.end())
    {
        target->AddSkill(it->second);
    }
}

void Equipment::initExpAndLevel(Entity* target)
{
    if(m_level.find(target) == m_level.end())
    {
        m_level[target] = 1;
        m_exp[target] = 0;
    }
}

SkillGenerator* Equipment::GetSkillGenerator()
{
    return &m_skillGenerator;
}

void Equipment::AddSkillsToLearn(int nr)
{
    //Get next level of this Equipment, that has not yet a Skill to learn
    int lvl = 2;
    if(m_skillsToLearn.size() > 0)
        lvl = m_skillsToLearn.rbegin()->first + 1;
    for(int i = 0; i < nr; i++)
    {
        m_skillsToLearn.insert(std::pair<int, std::shared_ptr<Skill>>(lvl, std::shared_ptr<Skill>(m_skillGenerator.GetNewSkill(m_skillStrength + lvl))));
        lvl++;
    }
}

void Equipment::SetSkillStrength(float strength)
{
    m_skillStrength = strength;
}

void Equipment::SetAttributeBuff(BattleEnums::Attribute attribute, int buff)
{
    m_attributeBuffs[attribute] = buff;
}

void Equipment::SetTypeResistance(BattleEnums::AttackType type, float multiplier)
{
    m_typeResistance[type] = multiplier;
}

void Equipment::AddAttackType(BattleEnums::AttackType type)
{
    m_attackTypes.insert(type);
}

std::string Equipment::GetName()
{
    return Item::GetName();
}

std::string Equipment::GetLocalizedDescription()
{
    return Localization::GetInstance()->GetLocalization(Item::GetDescription());
}



//Not needed Functions from IPassiveEffect
void Equipment::OnTurn(Entity* target)
{
    //NOOP
}

void Equipment::GetAttacked(Attack*, Entity*, Entity*)
{
    //NOOP
}

float Equipment::GetExp(float exp)
{
    //NOOP: simple Pass Through
    return exp;
}

