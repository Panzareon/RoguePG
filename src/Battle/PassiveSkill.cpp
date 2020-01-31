#include "Battle/PassiveSkill.h"

PassiveSkill::PassiveSkill() : Skill(BattleEnums::Target::Passive), PassiveEffect(true, -1, this, true)
{
    //ctor
}

PassiveSkill::~PassiveSkill()
{
    //dtor
}

std::string PassiveSkill::GetName()
{
    return Skill::GetName();
}

std::string PassiveSkill::GetLocalizedDescription()
{
    return Skill::GetLocalizedDescription();
}

Skill::SkillType PassiveSkill::GetSkillType()
{
    return SkillType::Passive;
}

void PassiveSkill::AddEffect(EffectBase* eff, bool isPositive)
{
    Skill::AddEffect(eff, isPositive);
    eff->AddToPassiveEffect(this);
}

bool PassiveSkill::DeleteEffect()
{
    return false;
}
