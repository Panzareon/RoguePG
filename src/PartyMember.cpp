#include "PartyMember.h"

PartyMember::PartyMember(int teamId): Entity(teamId)
{
    //ctor
    m_controllTypeAtm = Entity::ControllUser;
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
        m_exp += newAmmount;
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
