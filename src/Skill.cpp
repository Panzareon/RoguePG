#include "Skill.h"

Skill::Skill()
{
    //ctor
}

Skill::~Skill()
{
    //dtor
}
void Skill::Use(BattleEnums::Target targetType, Entity* target)
{
    //TODO: Use this Skill + play animation
}

BattleEnums::Target Skill::GetDefaultTarget()
{
    //TODO: return actual value
    return BattleEnums::TargetEnemyTeamEntity;
}

std::string Skill::GetName()
{
    //TODO: return actual value
    return "Test-Skill";
}
