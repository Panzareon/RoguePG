#include "PartyMember.h"
#include "CharacterClass.h"

PartyMember::PartyMember(CharacterClass* chrClass)
{
    //ctor
    m_controllTypeAtm = Entity::ControllUser;
    m_chrClass = chrClass;
}

PartyMember::~PartyMember()
{
    //dtor
}

void PartyMember::AddExp(int ammount)
{
    float newAmmount = ammount;
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        if(newAmmount >= 0)
            newAmmount = iter->second->GetExp(newAmmount);
    }
    if(newAmmount > 0)
    {
        m_exp += newAmmount;
        //Level up if enough Exp
        //TODO: use an other calculation for needed exp
        if(m_exp > m_lvl * m_lvl * 10)
        {
            LevelUp();
        }
    }
}

void PartyMember::BattleFinished()
{
    auto iter = m_passiveEffects.begin();
    while(iter != m_passiveEffects.end())
    {
        if(iter->second->StaysAfterBattle())
            iter++;
        else
            iter = m_passiveEffects.erase(iter);
    }
}

void PartyMember::LevelUp()
{
    m_lvl++;
    float skillChance = m_chrClass->GetSkillChance();
    float random = (rand() / (float)RAND_MAX);
    if(skillChance > random)
    {
        Skill* newSkill = m_chrClass->GetNewSkill(this);
        if(newSkill != nullptr)
        {
            AddSkill(newSkill);
        }
    }
}


int PartyMember::GetLevel()
{
    return m_lvl;
}
