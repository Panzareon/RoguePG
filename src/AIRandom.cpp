#include "AIRandom.h"
#include "Entity.h"
#include <random>

AIRandom::AIRandom(Entity* entity) : AIBase(entity)
{
    //ctor
}

AIRandom::~AIRandom()
{
    //dtor
}
void AIRandom::UseNextSkill()
{
    //select random skill and use it
    std::vector<std::shared_ptr<Skill>>* skillList = m_entity->GetSkillList();
    int nrSkills = skillList->size();
    int skill = rand() % (nrSkills + 1);
    if(skill < nrSkills)
    {
        std::shared_ptr<Skill> toUse = skillList->at(skill);
        BattleEnums::Target target = toUse->GetDefaultTarget();
        if(target == BattleEnums::TargetEnemyTeamEntity)
            toUse->Use(target, GetRandomEntity(m_entity->GetTeamId(), true));
        else if(target == BattleEnums::TargetOwnTeamEntity)
            toUse->Use(target, GetRandomEntity(m_entity->GetTeamId(), false));
        else
            toUse->Use(target, nullptr);
    }
    else
    {
        //Use Basic Attack
        m_entity->AttackEntity(GetRandomEntity(m_entity->GetTeamId(), true));
    }
}


