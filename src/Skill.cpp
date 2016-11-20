#include "Skill.h"
#include "InvalidArgumentException.h"
#include "Effect.h"

Skill::Skill(BattleEnums::Target target)
{
    //ctor
    m_defaultTarget = target;
    m_manaUse = 0.0f;
}

Skill::~Skill()
{
    //dtor
}
void Skill::Use(Entity* user, BattleEnums::Target targetType, Entity* target)
{
    std::vector<Entity*> targets;
    if(targetType == BattleEnums::TargetEnemyTeamEntity || targetType == BattleEnums::TargetOwnTeamEntity)
    {
        if(target == nullptr)
            throw InvalidArgumentException("Targeted Entity cannot be null");
        targets.push_back(target);
    }
    else if(targetType == BattleEnums::TargetSelf)
    {
        targets.push_back(user);
    }
    else
    {
        //TODO: fill targets vector depending on targetType
    }
    //Use this Skill + play animation
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        m_effects[i]->UseEffectOn(user, &targets);
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
void Skill::AddEffect(Effect* eff, bool isPositive)
{
    m_effects.push_back(eff);
    m_isPositive.push_back(isPositive);
    if(isPositive)
        m_manaUse += eff->GetValue();
    else
        m_manaUse -= 0.5 * eff->GetValue();
}

float Skill::GetManaUse()
{
    return m_manaUse;
}
