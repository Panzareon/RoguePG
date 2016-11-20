#include "Equipment.h"
#include "Attack.h"
#include "Entity.h"
#include "Skill.h"

Equipment::Equipment(int itemId) : Item(itemId, Item::ItemTypeEquipment)
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

void Equipment::AddExp(int exp)
{
    AddExp(m_target, exp);
}

void Equipment::AddExp(Entity* target, int exp)
{
    if(!CanLearnSomething(target))
        return;
    m_exp[target] += exp;
    while(m_exp[target] >= m_level[target] * m_level[target] * m_neededExpMultiplier)
    {
        LevelUp(target);
    }
}

int Equipment::GetEquipmentExp()
{
    return GetEquipmentExp(m_target);
}

int Equipment::GetLevel()
{
    return GetLevel(m_target);
}

int Equipment::GetEquipmentExp(Entity* target)
{
    return m_exp[target];
}

int Equipment::GetLevel(Entity* target)
{
    return m_level[target];
}

std::map<int, std::shared_ptr<Skill>>*  Equipment::GetSkillsToLearn()
{
    return &m_skillsToLearn;
}

bool Equipment::CanLearnSomething(Entity* target)
{
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

SkillGenerator* Equipment::GetSkillGenerator()
{
    return &m_skillGenerator;
}

void Equipment::AddSkillsToLearn(int nr)
{
    //Get next level of this Equipment, that has not yet a Skill to learn
    int lvl = 1;
    if(m_skillsToLearn.size() > 0)
        lvl = m_skillsToLearn.rbegin()->first + 1;
    for(int i = 0; i < nr; i++)
    {
        m_skillsToLearn.insert(std::pair<int, std::shared_ptr<Skill>>(lvl, std::shared_ptr<Skill>(m_skillGenerator.GetNewSkill(m_skillStrength))));
        lvl++;
    }
}

void Equipment::SetSkillStrength(float strength)
{
    m_skillStrength = strength;
}




//Not needed Functions from IPassiveEffect
void Equipment::OnTurn()
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

