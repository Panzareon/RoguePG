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
    if(target == BattleEnums::TargetOwnTeam || target == BattleEnums::TargetOwnTeamEntity || target == BattleEnums::TargetSelf)
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
