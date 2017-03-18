#include "Party/PartyMember.h"
#include "Party/CharacterClass.h"
#include "Controller/GameController.h"
#include "Party/Equipment.h"
#include "Controller/NameGenerator.h"
#include <iostream>

PartyMember::PartyMember(CharacterClass* chrClass)
{
    //ctor
    m_controllTypeAtm = Entity::ControllUser;
    m_chrClass = chrClass;
    m_exp = 0;
    m_lvl = 1;

    std::string name = NameGenerator::GetInstance()->GetCapitalizedName(5, 10);
    SetName(name);

    for(int i = 0; i < Equipment::EQUIPMENT_POSITION_END; i++)
    {
        m_equipment[(Equipment::EquipmentPosition)i] = nullptr;
    }
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
        //Add Exp to Equipment
        for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
        {
            if(iter->second->IsEquipment())
            {
                ((Equipment*)iter->second)->AddExp(m_exp);
            }
        }
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

void PartyMember::GetStartingSkills(int nr)
{
    float skillChance = m_chrClass->GetSkillChance();
    for(int i = 0; i < nr; i++)
    {
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
}

void PartyMember::LevelUp()
{
    m_lvl++;
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

int PartyMember::GetExp()
{
    return m_exp;
}

void PartyMember::SetEquipment(Equipment::EquipmentPosition position, Equipment* equipment)
{
    if(m_equipment[position] != nullptr)
    {
        std::multimap<int, IPassiveEffect*> ::iterator it;
        for(it=m_passiveEffects.begin(); it!=m_passiveEffects.end(); ++it)
        {
            if((*it).second == m_equipment[position])
            {
                m_passiveEffects.erase(it);
                break;
            }
        }
        m_equipment[position]->UnEquip();
    }
    if(equipment != nullptr)
    {
        equipment->EquipTo(this);
        AddPassiveEffect(equipment);
    }
    m_equipment[position] = equipment;
    CheckMaxValues();
}

Equipment* PartyMember::GetEquipment(Equipment::EquipmentPosition position)
{
    return m_equipment[position];
}

