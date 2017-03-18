#include "AI/AIRandom.h"
#include "Battle/Entity.h"
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
    int nrSkills = 0;
    for(int i = 0; i < skillList->size(); i++)
    {
        if(skillList->at(i)->GetManaUse() <= m_entity->GetMp())
            nrSkills++;
    }
    int skill = rand() % (nrSkills + 1);
    if(skill < nrSkills)
    {
        std::shared_ptr<Skill> toUse;
        for(int i = 0; i < skillList->size(); i++)
        {
            if(skillList->at(i)->GetManaUse() <= m_entity->GetMp())
            {
                if(skill == 0)
                    toUse = skillList->at(i);
                skill--;
            }
        }
        BattleEnums::Target target = toUse->GetDefaultTarget();
        if(target == BattleEnums::TargetEnemyTeamEntity)
            toUse->Use(m_entity, target, GetRandomEntity(m_entity->GetTeamId(), true));
        else if(target == BattleEnums::TargetOwnTeamEntity)
            toUse->Use(m_entity, target, GetRandomEntity(m_entity->GetTeamId(), false));
        else
            toUse->Use(m_entity, target, nullptr);
    }
    else
    {
        //Use Basic Attack
        m_entity->AttackEntity(GetRandomEntity(m_entity->GetTeamId(), true));
    }
}


