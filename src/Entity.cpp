#include "Entity.h"
#include "AIRandom.h"
#include "SceneManagerBattle.h"
#include <math.h>
#include <map>

Entity::Entity(int teamId)
{
    //ctor
    m_controllTypeAtm = Entity::ControllAI;
    m_teamId = teamId;

    //TODO: add actual values
    m_AI = new AIRandom(this);
    for(int i = 0; i < BattleEnums::ATTRIBUTE_END; i++)
    {
        m_attributes.insert(std::pair<BattleEnums::Attribute, int>((BattleEnums::Attribute)i, 10));
    }
    m_attributes[BattleEnums::AttributeMaxHp] = 100;
    m_hp = GetAttribute(BattleEnums::AttributeMaxHp);



    m_toNextAttack = 1.0f;
}

Entity::~Entity()
{
    //dtor
    if(m_AI != 0)
        delete m_AI;
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
        delete iter->second;
}
void Entity::AttackEntity(Entity* target)
{
    //TODO: play Attack animation
    //TODO: Get Weapon Dmg
    int attack = 10;
    bool isPhysical = IsAttackPhysical();
    if(isPhysical)
    {
        attack *= GetAttribute(BattleEnums::AttributeStrength);
    }
    else
    {
        attack *= GetAttribute(BattleEnums::AttributeInt);
    }
    Attack att(attack, GetAttackType(), isPhysical);
    AttackEntity(target, &att);
}

void Entity::AttackEntity(Entity* target, Attack* attack)
{
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        iter->second->AttackEntity(attack, target, this);
    }
    target->GetHit(attack, this);
}

void Entity::GetHit(Attack* attack, Entity* attacker)
{
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        iter->second->GetAttacked(attack, this, attacker);
    }
    //TODO: maybe other dmg calculation?
    int defense;
    if(attack->m_physical)
    {
        defense = GetAttribute(BattleEnums::AttributeDefense);
    }
    else
    {
        defense = GetAttribute(BattleEnums::AttributeMagicDefense);
    }
    int dmg = attack->m_dmg / std::sqrt(defense);
    //TODO: add resistance or weakness to Attack type
    m_hp -= dmg;
    //TODO: play get hit animation
    if(m_hp <= 0)
    {
        m_hp = 0;
        //TODO: handle death + death animation
    }
}

BattleEnums::AttackType Entity::GetAttackType()
{
    //TODO: get Attack Type of weapon / currently active buffs
    return BattleEnums::AttackTypePhysical;
}

bool Entity::IsAttackPhysical()
{
    //TODO: Get Type of weapon / Buffs
    return true;
}

bool Entity::IsDead()
{
    return m_hp <= 0;
}

void Entity::AddSkill(Skill* skill)
{
    m_skills.push_back(*skill);
}

int Entity::GetAttribute(BattleEnums::Attribute attr)
{
    float atmValue = (float)m_attributes[attr];
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        atmValue = iter->second->GetAttribute(atmValue, attr);
    }
    return (int)atmValue;
}


void Entity::PassTime(float Time)
{
    m_toNextAttack -= Time * GetAttribute(BattleEnums::AttributeSpeed);
}

void Entity::FinishedTurn()
{
    m_toNextAttack += 1.0f;
    auto iter = m_passiveEffects.begin();
    while(iter != m_passiveEffects.end())
    {
        iter->second->OnTurn();
        if(iter->second->IsStillActive())
            iter++;
        else
            iter = m_passiveEffects.erase(iter);
    }
}


float Entity::GetTimeToNextAttack()
{
    return m_toNextAttack / GetAttribute(BattleEnums::AttributeSpeed);
}
Entity::ControllType Entity::GetControllType()
{
    return m_controllTypeAtm;
}
std::vector<Skill>* Entity::GetSkillList()
{
    return &m_skills;
}


void Entity::CalculateMove(SceneManagerBattle* sm)
{
    //Check if controlled by AI
    if(m_controllTypeAtm == Entity::ControllAI)
    {
        m_AI->UseNextSkill();
        sm->TurnIsFinished();
    }
}

int Entity::GetTeamId()
{
    return m_teamId;
}
