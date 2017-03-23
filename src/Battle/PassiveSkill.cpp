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
