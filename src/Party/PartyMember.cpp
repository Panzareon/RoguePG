#include "Party/PartyMember.h"
#include "Party/CharacterClass.h"
#include "Controller/GameController.h"
#include "Party/Equipment.h"
#include "Controller/NameGenerator.h"
#include <iostream>

PartyMember::PartyMember()
{
    m_chrClass = nullptr;
    Init();
}

PartyMember::PartyMember(CharacterClass* chrClass)
{
    //ctor
    m_chrClass = chrClass;
    Init();
}

PartyMember::~PartyMember()
{
    //dtor
}

void PartyMember::SetCharacterClass(CharacterClass* chrClass)
{
    if(m_chrClass == nullptr)
    {
        m_chrClass  = chrClass;
    }
}

void PartyMember::Init()
{
    m_controllTypeAtm = Entity::ControllUser;
    m_exp = 0;
    m_lvl = 1;
    m_neededExpMultiplier = 10.0f;

    std::string name = NameGenerator::GetInstance()->GetCapitalizedName(5, 10);
    SetName(name);

    for(int i = 0; i < Equipment::EQUIPMENT_POSITION_END; i++)
    {
        m_equipment[(Equipment::EquipmentPosition)i] = nullptr;
    }
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
                ((Equipment*)iter->second.get())->AddExp(m_exp);
            }
        }
        //Level up if enough Exp
        //TODO: use an other calculation for needed exp
        while(m_exp > NeededExp(m_lvl))
        {
            LevelUp();
        }
    }
}

float PartyMember::GetExpPercent()
{
    return ((float)m_exp - NeededExp(m_lvl - 1)) / (float)(NeededExp(m_lvl));
}

int PartyMember::NeededExp(int lvl)
{
    return lvl * lvl * m_neededExpMultiplier;
}

void PartyMember::BattleFinished()
{
    auto iter = m_passiveEffects.begin();
    while(iter != m_passiveEffects.end())
    {
        iter->second->OnBattleFinished(this);
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

void PartyMember::SetEquipment(Equipment::EquipmentPosition position, std::shared_ptr<Equipment> equipment)
{
    if(m_equipment[position] != nullptr)
    {
        std::multimap<int, std::shared_ptr<IPassiveEffect>> ::iterator it;
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
        equipment->EquipTo(GameController::getInstance()->getParty()->GetSharedPointerOf(this));
        AddPassiveEffect(equipment);
    }
    m_equipment[position] = equipment;
    CheckMaxValues();
}

std::shared_ptr<Equipment> PartyMember::GetEquipment(Equipment::EquipmentPosition position)
{
    return m_equipment[position];
}

CharacterClass* PartyMember::GetClass() const
{
    return m_chrClass;
}

void PartyMember::SaveBeforeEquipping()
{
    m_missingHp = GetHp() / (float)GetAttribute(BattleEnums::AttributeMaxHp);
    m_missingMp = GetMp() / (float)GetAttribute(BattleEnums::AttributeMaxMp);
    m_lastEquipment = m_equipment;
}

void PartyMember::ResetAfterEquipping()
{
    m_hp = GetAttribute(BattleEnums::AttributeMaxHp) * m_missingHp;
    if(m_hp < 1 && m_missingHp > 0.0f)
        m_hp = 1;

    m_mp = GetAttribute(BattleEnums::AttributeMaxMp) * m_missingMp;
    if(m_mp < 0)
        m_mp = 0;

    //Reequip all lost equipment
    for(auto it = m_lastEquipment.begin(); it != m_lastEquipment.end(); it++)
    {
        if(m_equipment[it->first] == nullptr)
        {
            if(it->second != nullptr && !it->second->IsEquipped())
            {
                SetEquipment(it->first, it->second);
            }
        }
    }
    m_lastEquipment = m_equipment;
}

bool PartyMember::ShowEnemyHealth()
{
    bool ret = false;
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        ret = iter->second->ShowEnemyHealth(ret);
    }
    return ret;
}

bool PartyMember::ShowCompleteMap()
{
    bool ret = false;
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        ret = iter->second->ShowCompleteMap(ret);
    }
    return ret;
}

float PartyMember::MovementSpeed(float base)
{
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        base = iter->second->Movementspeed(base);
    }
    return base;
}

