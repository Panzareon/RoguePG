#include "Battle/SkillGenerator.h"
#include "Battle/EffectFactoryList.h"
#include <iostream>
#include "Battle/PassiveSkill.h"

SkillGenerator::SkillGenerator()
{
    //ctor
}

SkillGenerator::~SkillGenerator()
{
    //dtor
}

void SkillGenerator::AddSkillTarget(BattleEnums::Target target, float chance)
{
    m_skillTarget.insert(std::pair<float, BattleEnums::Target>(chance, target));
}

void SkillGenerator::AddSkillAttackType(BattleEnums::AttackType attackType, float chance)
{
    m_skillAttackType.insert(std::pair<float, BattleEnums::AttackType>(chance, attackType));
}

void SkillGenerator::AddSkillEffectType(BattleEnums::EffectType effectType, float chance, bool positive)
{
    if(positive)
        m_skillPositiveEffectType.insert(std::pair<float, BattleEnums::EffectType>(chance, effectType));
    else
        m_skillNegativeEffectType.insert(std::pair<float, BattleEnums::EffectType>(chance, effectType));
}

Skill* SkillGenerator::GetNewSkill(float strength)
{
    BattleEnums::Target target;
    BattleEnums::AttackType attackType;
    BattleEnums::EffectType effectType;

    target = GetRandomTarget();
    bool positive = false;
    if(target == BattleEnums::TargetOwnTeam || target == BattleEnums::TargetOwnTeamEntity || target == BattleEnums::TargetSelf ||  target == BattleEnums::TargetOwnTeamRandomEntity)
        positive = true;
    if(target == BattleEnums::TargetPassive)
    {
        Skill* newSkill = new PassiveSkill();
        float manaUse = 0.0f;
        effectType = BattleEnums::EffectTypePassive;

        do
        {
            attackType = GetRandomAttackType();


            newSkill->AddEffect(EffectFactoryList::GetInstance()->getRandom(attackType, effectType)->GetEffectWithValue(strength - manaUse, target), true);
            manaUse = newSkill->GetManaBase();
        }
        while(manaUse < strength * 0.9);
        return newSkill;

    }
    else
    {
        Skill* newSkill = new Skill(target);
        float manaUse = 0.0f;

        do
        {
            attackType = GetRandomAttackType();
            effectType = GetRandomEffectType(positive);


            newSkill->AddEffect(EffectFactoryList::GetInstance()->getRandom(attackType, effectType)->GetEffectWithValue(strength - manaUse, target), true);
            manaUse = newSkill->GetManaBase();
        }
        while(manaUse < strength * 0.9);
        return newSkill;
    }
}

BattleEnums::Target SkillGenerator::GetRandomTarget()
{
    #ifdef CHECK_GENERATORS
    //Checks if there are errors defining the Skill generator values

    float value = 0.0f;
    auto itCheck = m_skillTarget.begin();
    for(; itCheck != m_skillTarget.end(); itCheck++)
    {
        auto it2 = itCheck;
        it2++;
        for(; it2 != m_skillTarget.end(); it2++)
        {
            if(itCheck->second == it2->second)
            {
                std::cout << "Target double defined: " << itCheck->second << std::endl;
            }
        }
        value += itCheck->first;
    }
    if(value != 1.0f)
    {
        std::cout << "Target has not combined chance of 1 but of: " << value << std::endl;
    }

    #endif // CHECK_GENERATORS

    float random = rand() / (float)RAND_MAX;
    auto it = m_skillTarget.begin();
    for(; it != m_skillTarget.end(); it++)
    {
        if(it->first > random)
        {
            return it->second;
        }
        random -= it->first;
    }
    it--;
    return it->second;
}

BattleEnums::AttackType SkillGenerator::GetRandomAttackType()
{
    #ifdef CHECK_GENERATORS
    //Checks if there are errors defining the Skill generator values

    float value = 0.0f;
    auto itCheck = m_skillAttackType.begin();
    for(; itCheck != m_skillAttackType.end(); itCheck++)
    {
        auto it2 = itCheck;
        it2++;
        for(; it2 != m_skillAttackType.end(); it2++)
        {
            if(itCheck->second == it2->second)
            {
                std::cout << "AttackType double defined: " << itCheck->second << std::endl;
            }
        }
        value += itCheck->first;
    }
    if(value != 1.0f)
    {
        std::cout << "AttackType has not combined chance of 1 but of: " << value << std::endl;
    }

    #endif // CHECK_GENERATORS


    float random = rand() / (float)RAND_MAX;
    auto it = m_skillAttackType.begin();
    for(; it != m_skillAttackType.end(); it++)
    {
        if(it->first > random)
        {
            return it->second;
        }
        random -= it->first;
    }
    it--;
    return it->second;
}

BattleEnums::EffectType SkillGenerator::GetRandomEffectType(bool positive)
{
    #ifdef CHECK_GENERATORS
    //Checks if there are errors defining the Skill generator values

    float value = 0.0f;
    auto itCheck = m_skillPositiveEffectType.begin();
    for(; itCheck != m_skillPositiveEffectType.end(); itCheck++)
    {
        auto it2 = itCheck;
        it2++;
        for(; it2 != m_skillPositiveEffectType.end(); it2++)
        {
            if(itCheck->second == it2->second)
            {
                std::cout << "PositiveEffectType double defined: " << itCheck->second << std::endl;
            }
        }
        value += itCheck->first;
    }
    if(value != 1.0f)
    {
        std::cout << "PositiveEffectType has not combined chance of 1 but of: " << value << std::endl;
    }

    value = 0.0f;
    itCheck = m_skillNegativeEffectType.begin();
    for(; itCheck != m_skillNegativeEffectType.end(); itCheck++)
    {
        auto it2 = itCheck;
        it2++;
        for(; it2 != m_skillNegativeEffectType.end(); it2++)
        {
            if(itCheck->second == it2->second)
            {
                std::cout << "NegativeEffectType double defined: " << itCheck->second << std::endl;
            }
        }
        value += itCheck->first;
    }
    if(value != 1.0f)
    {
        std::cout << "NegativeEffectType has not combined chance of 1 but of: " << value << std::endl;
    }
    #endif // CHECK_GENERATORS

    float random = rand() / (float)RAND_MAX;
    std::multimap<float, BattleEnums::EffectType>::iterator it, endIt;
    if(positive)
    {
        it = m_skillPositiveEffectType.begin();
        endIt = m_skillPositiveEffectType.end();
    }
    else
    {
        it = m_skillNegativeEffectType.begin();
        endIt = m_skillNegativeEffectType.end();
    }
    for(; it != endIt; it++)
    {
        if(it->first > random)
        {
            return it->second;
        }
        random -= it->first;
    }
    it--;
    return it->second;
}
