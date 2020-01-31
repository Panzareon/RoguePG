#include "Party/CharacterClass.h"
#include "Exception/InvalidArgumentException.h"
#include "Battle/EffectFactoryList.h"
#include <random>
#include "Party/PartyMember.h"
#include "Controller/GameController.h"
#include "Battle/PassiveSkill.h"

std::vector<CharacterClass*>* CharacterClass::m_classes = nullptr;

CharacterClass::CharacterClass(CharacterClassEnum chrClass, float skillChance,TextureList::TextureFiles battleSprite)
{
    //ctor
    m_classType = chrClass;
    m_skillChance = skillChance;
    m_battleSprite = battleSprite;
    //Set default Attribute increase per level to 1.0f
    for(int i = 0; i < (int)BattleEnums::Attribute::COUNT; i++)
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
        newClass = new CharacterClass(CharacterClassMage, 1.0f, TextureList::MageBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 15);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 5);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 12);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 10);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxMp, 1.3f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Int, 1.3f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamEntity, 0.7f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamRandomEntity, 0.1f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeam, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::Self, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamEntity, 0.025f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamRandomEntity, 0.025f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeam, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Physical, 0.04f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Water, 0.24f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Fire, 0.24f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Earth, 0.24f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Air, 0.24f);

        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Damage, 0.8f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Debuff, 0.2f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Buff, 1.0f, true);

        m_classes->at(CharacterClassMage) = newClass;


        newClass = new CharacterClass(CharacterClassBarbarian, 0.0f, TextureList::BarbarianBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 15);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 7);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 12);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 5);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 9);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 7);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxHp, 1.3f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxMp, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 1.3f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Int, 0.7f);

        m_classes->at(CharacterClassBarbarian) = newClass;


        newClass = new CharacterClass(CharacterClassPaladin, 0.5f, TextureList::PaladinBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 13);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 15);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 12);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 9);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 8);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxHp, 1.2f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxMp, 1.3f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 1.2f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Speed, 0.7f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamEntity, 0.08f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamRandomEntity, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeam, 0.3f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::Self, 0.1f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamEntity, 0.45f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamRandomEntity, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeam, 0.01f);

        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Physical, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Water, 0.35f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Fire, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Earth, 0.25f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Air, 0.3f);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffOffense, 0.2f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffDefense, 0.2f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Heal, 0.6f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Damage, 0.3f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Debuff, 0.7f, false);

        m_classes->at(CharacterClassPaladin) = newClass;

        newClass = new CharacterClass(CharacterClassThief, 0.3f, TextureList::ThiefBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 12);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 9);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 15);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 1.2f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Speed, 1.5f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamEntity, 0.65f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamRandomEntity, 0.15f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeam, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::Self, 0.09f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamEntity, 0.005f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamRandomEntity, 0.005f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeam, 0.09f);

        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Physical, 0.8f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Water, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Fire, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Earth, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Air, 0.05f);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffOffense, 0.5f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffDefense, 0.2f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Heal, 0.3f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Damage, 0.5f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Debuff, 0.5f, false);

        m_classes->at(CharacterClassThief) = newClass;


        newClass = new CharacterClass(CharacterClassCleric, 1.0f, TextureList::ClericBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 15);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 15);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 5);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 12);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 10);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxMp, 1.3f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Int, 1.3f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamEntity, 0.08f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamRandomEntity, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeam, 0.3f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::Self, 0.1f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamEntity, 0.45f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamRandomEntity, 0.05f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeam, 0.01f);

        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Physical, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Water, 0.35f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Fire, 0.05f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Earth, 0.25f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Air, 0.3f);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffOffense, 0.1f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffDefense, 0.1f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Heal, 0.8f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Damage, 0.3f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Debuff, 0.7f, false);

        m_classes->at(CharacterClassCleric) = newClass;


        newClass = new CharacterClass(CharacterClassWizard, 1.0f, TextureList::WizardBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 15);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 0);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 5);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 10);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxMp, 0.0f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Int, 1.0f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamEntity, 0.4f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamRandomEntity, 0.1f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeam, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::Self, 0.3f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamEntity, 0.08f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamRandomEntity, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeam, 0.1f);

        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Physical, 0.04f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Water, 0.24f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Fire, 0.24f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Earth, 0.24f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Air, 0.24f);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffOffense, 0.4f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffDefense, 0.4f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Heal, 0.2f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Damage, 0.8f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Debuff, 0.2f, false);

        m_classes->at(CharacterClassWizard) = newClass;

        newClass = new CharacterClass(CharacterClassVampire, 0.3f, TextureList::VampireBattleSprite);

        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxHp, 20);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MaxMp, 0);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Strength, 5);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Int, 10);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Defense, 8);
        newClass->SetBaseAttribute(BattleEnums::Attribute::MagicDefense, 12);
        newClass->SetBaseAttribute(BattleEnums::Attribute::Speed, 10);

        //Set increased and decreased Attribute per Level values
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxHp, 1.2f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::MaxMp, 0.0f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Strength, 0.7f);
        newClass->SetAttributePerLevel(BattleEnums::Attribute::Int, 1.2f);

        skillGenerator = newClass->GetSkillGenerator();
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamEntity, 0.4f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeamRandomEntity, 0.1f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeam, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::Self, 0.3f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamEntity, 0.08f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::OwnTeamRandomEntity, 0.01f);
        skillGenerator->AddSkillTarget(BattleEnums::Target::EnemyTeam, 0.1f);

        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Physical, 0.1f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Water, 0.225f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Fire, 0.225f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Earth, 0.225f);
        skillGenerator->AddSkillAttackType(BattleEnums::AttackType::Air, 0.225f);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffOffense, 0.2f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::BuffDefense, 0.2f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Heal, 0.6f, true);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Damage, 0.8f, false);
        skillGenerator->AddSkillEffectType(BattleEnums::EffectType::Debuff, 0.2f, false);

        m_classes->at(CharacterClassVampire) = newClass;



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
    PersistentProgress* progress = GameController::getInstance()->GetPersistentProgress();
    CharacterClassEnum retVal;
    int nrOfTries = 0;
    while(nrOfTries < 1000)
    {
        nrOfTries++;
        retVal = (CharacterClassEnum)(rand() % CHARACTER_CLASS_END);
        if(progress->IsClassUnlocked(retVal))
        {
            break;
        }
    }
    return GetCharacterClass(retVal);
}

PartyMember* CharacterClass::GetNewPartyMember()
{
    PartyMember* ret = new PartyMember(this);
    for(int i = 0; i < (int)BattleEnums::Attribute::COUNT; i++)
    {
        ret->InitAttribute((BattleEnums::Attribute)i, m_baseAttributes[(BattleEnums::Attribute)i]);
    }
    ret->SetBattleSprite(m_battleSprite);

    //Add special Character cases here
    if(m_classType == CharacterClassWizard)
    {
        //Add Passive Skill to not use MP
        PassiveSkill* sk = new PassiveSkill();
        std::vector<float>* strength = new std::vector<float>();
        strength->push_back(1.0f);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(100103)->GetEffectWithStrength(strength, BattleEnums::Target::Passive),true);
        ret->AddSkill(sk);
    }
    else if(m_classType == CharacterClassVampire)
    {
        //Add Passive Skill that skills cost less
        PassiveSkill* sk = new PassiveSkill();
        std::vector<float>* strength = new std::vector<float>();
        strength->push_back(0.5f);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(100103)->GetEffectWithStrength(strength, BattleEnums::Target::Passive),true);
        ret->AddSkill(sk);

        ret->SetUseHpInsteadOfMp(true);
    }



    ret->GetStartingSkills(1);
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
    return m_skillGenerator.GetNewSkill(10 + user->GetLevel());
}

std::string CharacterClass::GetName()
{
    switch(m_classType)
    {
    case CharacterClassMage:
        return "character_class.mage";
    case CharacterClassBarbarian:
        return "character_class.barbarian";
    case CharacterClassPaladin:
        return "character_class.paladin";
    case CharacterClassThief:
        return "character_class.thief";
    case CharacterClassCleric:
        return "character_class.cleric";
    case CharacterClassWizard:
        return "character_class.wizard";
    case CharacterClassVampire:
        return "character_class.vampire";
    }
    return "character_class.unknown";
}

CharacterClass::CharacterClassEnum CharacterClass::GetClassType()
{
    return m_classType;
}

TextureList::TextureFiles CharacterClass::GetClassSprite()
{
    return m_battleSprite;
}
