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
        CharacterClass * newClass;
        SkillGenerator* skillGenerator;
        //TODO: initialize Character Classes
        newClass = new CharacterClass(CharacterClassFireMage, 0.8f);

        newClass->SetBaseAttribute(BattleEnums::AttributeMaxHp, 10);
        newClass->SetBaseAttribute(BattleEnums::AttributeMaxMp, 15);
        newClass->SetBaseAttribute(BattleEnums::AttributeStrength, 5);
        newClass->SetBaseAttribute(BattleEnums::AttributeInt, 12);
        newClass->SetBaseAttribute(BattleEnums::AttributeDefense, 8);
        newClass->SetBaseAttribute(BattleEnums::AttributeMagicDefense, 10);
        newClass->SetBaseAttribute(BattleEnums::AttributeSpeed, 10);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::AttributeMaxMp, 1.3f);
        newClass->SetAttributePerLevel(BattleEnums::AttributeStrength, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::AttributeInt, 1.3f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.8f);
        skillGenerator->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::TargetSelf, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackTypeFire, 1.0f);

        skillGenerator->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.8f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectTypeDebuff, 0.2f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectTypeBuff, 1.0f, true);

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


float CharacterClass::GetSkillChance()
{
    return m_skillChance;
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

SkillGenerator* CharacterClass::GetSkillGenerator()
{
    return &m_skillGenerator;
}

Skill* CharacterClass::GetNewSkill(PartyMember* user)
{
    return m_skillGenerator.GetNewSkill(user->GetLevel());
}
