#include "PartyMember.h"
#include "CharacterClass.h"
#include "GameController.h"

PartyMember::PartyMember(CharacterClass* chrClass)
{
    //ctor
    m_controllTypeAtm = Entity::ControllUser;
    m_chrClass = chrClass;
    m_exp = 0;
    m_lvl = 1;
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
        while(m_exp > m_lvl * m_lvl * 10)
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
    std::default_random_engine* generator = GameController::getInstance()->GetRandomGenerator();
    for(int i = 0; i < BattleEnums::ATTRIBUTE_END; i++)
    {
        float chance = m_chrClass->GetAttributePerLevel((BattleEnums::Attribute)i);
        std::normal_distribution<float> distribution(chance,0.5f);
        float addf = distribution(*generator);
        int add = (int)addf;
        if(add > 0)
        {
            m_attributes[(BattleEnums::Attribute)i] += add;
        }
    }
}


int PartyMember::GetLevel()
{
    return m_lvl;
}

void PartyMember::Died()
{
    Entity::Died();

    //Remove this from Party and maybe add new one from inactive Members
    Party* p = GameController::getInstance()->getParty();
    p->UpdateActiveParty();
}

