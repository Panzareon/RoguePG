#include "CharacterClass.h"
#include "InvalidArgumentException.h"
#include "EffectFactoryList.h"
#include <random>

std::vector<CharacterClass*>* CharacterClass::m_classes = nullptr;

CharacterClass::CharacterClass(CharacterClassEnum chrClass, float skillChance)
{
    //ctor
    m_classType = chrClass;
    m_skillChance = skillChance;
    //Set default Attribute increase per level to 1.0f
    for(int i = 0; i < BattleEnums::ATTRIBUTE_END; i++)
    {
        m_attributesPerLevel[(BattleEnums::Attribute)i] = 1.0f;
    }
}

CharacterClass::~CharacterClass()
{
    //dtor
}

CharacterClass* CharacterClass::GetCharacterClass(CharacterClassEnum chrClass)
{
    if(m_classes == nullptr)
    {
        m_classes = new std::vector<CharacterClass*>;
        m_classes->resize(CHARACTER_CLASS_END);
        //TODO: initialize Character Classes
        CharacterClass * newClass = new CharacterClass(CharacterClassFireMage, 0.8f);

        newClass->SetBaseAttribute(BattleEnums::AttributeMaxHp, 10);
        newClass->SetBaseAttribute(BattleEnums::AttributeStrength, 5);
        newClass->SetBaseAttribute(BattleEnums::AttributeInt, 12);
        newClass->SetBaseAttribute(BattleEnums::AttributeDefense, 8);
        newClass->SetBaseAttribute(BattleEnums::AttributeMagicDefense, 10);
        newClass->SetBaseAttribute(BattleEnums::AttributeSpeed, 10);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::AttributeStrength, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::AttributeInt, 1.3f);

        newClass->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 1.0f);
        newClass->AddSkillAttackType(BattleEnums::AttackTypeFire, 1.0f);
        newClass->AddSkillEffectType(BattleEnums::EffectTypeDamage, 1.0f);

        m_classes->at(CharacterClassFireMage) = newClass;
        //finished Initializing Character Classes
    }
    if(chrClass >= 0 && chrClass < CHARACTER_CLASS_END)
    {
        return m_classes->at(chrClass);
    }
    else
    {
        std::string msg("No Character Class with id ");
        msg.append(std::to_string(chrClass));
        throw InvalidArgumentException(msg);
    }
}

CharacterClass* CharacterClass::GetRandomCharacterClass()
{
    return GetCharacterClass((CharacterClassEnum)(rand() % CHARACTER_CLASS_END));
}

PartyMember* CharacterClass::GetNewPartyMember()
{
    PartyMember* ret = new PartyMember(this);
    for(int i = 0; i < BattleEnums::ATTRIBUTE_END; i++)
    {
        ret->InitAttribute((BattleEnums::Attribute)i, m_baseAttributes[(BattleEnums::Attribute)i]);
    }
    return ret;
}

Skill* CharacterClass::GetNewSkill(PartyMember* user)
{
    float strength = user->GetLevel();
    BattleEnums::Target target;
    BattleEnums::AttackType attackType;
    BattleEnums::EffectType effectType;

    target = GetRandomTarget();
    Skill* newSkill = new Skill(user,target);
    float manaUse = 0.0f;

    do
    {
        attackType = GetRandomAttackType();
        effectType = GetRandomEffectType();


        newSkill->AddEffect(EffectFactoryList::GetInstance()->getRandom(attackType, effectType)->GetEffectWithValue(strength - manaUse, target), true);
        manaUse = newSkill->GetManaUse();
    }
    while(manaUse < strength * 0.9);
    return newSkill;
}

float CharacterClass::GetSkillChance()
{
    return m_skillChance;
}

BattleEnums::Target CharacterClass::GetRandomTarget()
{
    float random = rand() / (float)RAND_MAX;
    auto it = m_skillTarget.begin();
    for(; it != m_skillTarget.end(); it++)
    {
        if(it->first < random)
        {
            return it->second;
        }
    }
    it--;
    return it->second;
}

BattleEnums::AttackType CharacterClass::GetRandomAttackType()
{
    float random = rand() / (float)RAND_MAX;
    auto it = m_skillAttackType.begin();
    for(; it != m_skillAttackType.end(); it++)
    {
        if(it->first < random)
        {
            return it->second;
        }
    }
    it--;
    return it->second;
}

BattleEnums::EffectType CharacterClass::GetRandomEffectType()
{
    float random = rand() / (float)RAND_MAX;
    auto it = m_skillEffectType.begin();
    for(; it != m_skillEffectType.end(); it++)
    {
        if(it->first < random)
        {
            return it->second;
        }
    }
    it--;
    return it->second;
}

void CharacterClass::AddSkillTarget(BattleEnums::Target target, float chance)
{
    m_skillTarget.insert(std::pair<float, BattleEnums::Target>(chance, target));
}

void CharacterClass::AddSkillAttackType(BattleEnums::AttackType attackType, float chance)
{
    m_skillAttackType.insert(std::pair<float, BattleEnums::AttackType>(chance, attackType));
}

void CharacterClass::AddSkillEffectType(BattleEnums::EffectType effectType, float chance)
{
    m_skillEffectType.insert(std::pair<float, BattleEnums::EffectType>(chance, effectType));
}

float CharacterClass::GetAttributePerLevel(BattleEnums::Attribute attr)
{
    return m_attributesPerLevel[attr];
}

void CharacterClass::SetBaseAttribute(BattleEnums::Attribute attr, int value)
{
    m_baseAttributes[attr] = value;
}

void CharacterClass::SetAttributePerLevel(BattleEnums::Attribute attr, float value)
{
    m_attributesPerLevel[attr] = value;
}

