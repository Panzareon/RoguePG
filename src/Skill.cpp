#include "Skill.h"
#include "InvalidArgumentException.h"
#include "Effect.h"
#include "GameController.h"

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
        //fill targets vector depending on targetType
        std::vector<Entity*>* e = ((SceneManagerBattle*)GameController::getInstance()->GetActiveSceneManager())->GetEnemies();
        std::vector<PartyMember*> * p = GameController::getInstance()->getParty()->GetActivePartyMembers();
        int teamId = user->GetTeamId();
        if(targetType == BattleEnums::TargetAll)
        {
            targets.insert(targets.end(), e->begin(), e->end());
            targets.insert(targets.end(), p->begin(), p->end());
        }
        else if(targetType == BattleEnums::TargetEnemyTeam)
        {
            //add all with different Team Id
            for(int i = 0; i < e->size(); i++)
            {
                if(e->at(i)->GetTeamId() != teamId)
                    targets.push_back(e->at(i));
            }
            for(int i = 0; i < p->size(); i++)
            {
                if(p->at(i)->GetTeamId() != teamId)
                    targets.push_back(p->at(i));
            }
        }
        else if(targetType == BattleEnums::TargetOwnTeam)
        {
            //add all with same Team Id
            for(int i = 0; i < e->size(); i++)
            {
                if(e->at(i)->GetTeamId() == teamId)
                    targets.push_back(e->at(i));
            }
            for(int i = 0; i < p->size(); i++)
            {
                if(p->at(i)->GetTeamId() == teamId)
                    targets.push_back(p->at(i));
            }
        }
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

std::vector<Effect*>* Skill::GetEffects()
{
    return &m_effects;
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
