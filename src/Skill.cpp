#include "Skill.h"

#include "Effect.h"

Skill::Skill(Entity* user, BattleEnums::Target target)
{
    //ctor
    m_user = user;
    m_defaultTarget = target;
}

Skill::~Skill()
{
    //dtor
}
void Skill::Use(BattleEnums::Target targetType, Entity* target)
{
    std::vector<Entity*> targets;
    if(targetType == BattleEnums::TargetEnemyTeamEntity || targetType == BattleEnums::TargetOwnTeamEntity)
    {
        targets.push_back(target);
    }
    else if(targetType == BattleEnums::TargetSelf)
    {
        targets.push_back(m_user);
    }
    else
    {
        //TODO: fill targets vector depending on targetType
    }
    //Use this Skill + play animation
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        m_effects[i]->UseEffectOn(m_user, &targets);
    }
}

BattleEnums::Target Skill::GetDefaultTarget()
{
    return m_defaultTarget;
}

std::string Skill::GetName()
{
    //TODO: return actual value
    return "Test-Skill";
}
void Skill::AddEffect(Effect* eff)
{
    m_effects.push_back(eff);
    m_manaUse += eff->GetValue(GetDefaultTarget());
}
