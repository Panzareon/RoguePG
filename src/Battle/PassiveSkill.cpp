#include "PassiveSkill.h"

PassiveSkill::PassiveSkill() : Skill(BattleEnums::TargetPassive), PassiveEffect(true, -1, this, true)
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
    return Passive;
}

void PassiveSkill::AddEffect(EffectBase* eff, bool isPositive)
{
    Skill::AddEffect(eff, isPositive);
    eff->AddToPassiveEffect(this);
}
