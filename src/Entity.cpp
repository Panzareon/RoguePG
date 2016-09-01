#include "Entity.h"
#include "AIRandom.h"

Entity::Entity()
{
    //ctor
    m_controllTypeAtm = Entity::ControllAI;
    m_AI = new AIRandom();

    //TODO: add actual values
    m_maxHp = 100;
    m_hp = m_maxHp;
    m_speed = 10;
    m_attack = 10;
    m_defense = 10;



    m_toNextAttack = 1.0f;
}

Entity::~Entity()
{
    //dtor
    if(m_AI != 0)
        delete m_AI;
}
void Entity::Attack()
{
    //TODO: play Attack animation
}

void Entity::GetHit(int attack, AttackType type)
{
    //TODO: maybe other dmg calculation?
    int dmg = attack - m_defense/2;
    //TODO: add resistance or weakness to Attack type
    m_hp -= dmg;
    //TODO: play get hit animation
    if(m_hp <= 0)
    {
        m_hp = 0;
        //TODO: handle death + death animation
    }
}

Entity::AttackType Entity::GetAttackType()
{
    //TODO: get Attack Type of weapon / currently active buffs
    return Physical;
}

bool Entity::IsDead()
{
    return m_hp <= 0;
}


int Entity::GetAttack()
{
    //TODO: return attack with buffs and debuffs
    return m_attack;
}


void Entity::PassTime(float Time)
{
    m_toNextAttack -= Time * m_speed;
}

void Entity::FinishedTurn()
{
    m_toNextAttack = 1.0f;
}


float Entity::GetTimeToNextAttack()
{
    return m_toNextAttack / m_speed;
}
Entity::ControllType Entity::GetControllType()
{
    return m_controllTypeAtm;
}
std::vector<Skill>* Entity::GetSkillList()
{
    return &m_skills;
}


void Entity::CalculateMove()
{
    //Check if controlled by AI
    if(m_controllTypeAtm == Entity::ControllAI)
    {
        m_AI->UseNextSkill();
    }
    else
    {
        //If controlled by User wait for GUI input
    }
}
