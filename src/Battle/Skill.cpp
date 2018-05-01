#include "Battle/Skill.h"
#include "Exception/InvalidArgumentException.h"
#include "Battle/Effect.h"
#include "Controller/GameController.h"
#include "Controller/Localization.h"
#include "Controller/NameGenerator.h"

#include <math.h>

Skill::Skill()
{
    //ctor
    m_manaUseBase = 0.0f;
}

Skill::Skill(BattleEnums::Target target)
{
    //ctor
    m_defaultTarget = target;
    m_manaUseBase = 0.0f;

    m_name = NameGenerator::GetInstance()->GetCapitalizedName(3,6);
}

Skill::~Skill()
{
    //dtor
}
void Skill::Use(Entity* user, BattleEnums::Target targetType, Entity* target)
{
    if(!user->UseMp(GetManaUse()))
        return;

    Localization* local = Localization::GetInstance();
    ((SceneManagerBattle*)GameController::getInstance()->GetActiveSceneManager())->SetDescription(local->GetLocalization(GetName()));

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
        std::vector<std::shared_ptr<PartyMember> > * p = GameController::getInstance()->getParty()->GetActivePartyMembers();
        int teamId = user->GetTeamId();
        if(targetType == BattleEnums::TargetAll)
        {
            //add all that are not dead
            for(int i = 0; i < e->size(); i++)
            {
                if(!e->at(i)->IsDead())
                    targets.push_back(e->at(i));
            }
            for(int i = 0; i < p->size(); i++)
            {
                if(!p->at(i)->IsDead())
                    targets.push_back(p->at(i).get());
            }
        }
        else if(targetType == BattleEnums::TargetEnemyTeam || targetType == BattleEnums::TargetEnemyTeamRandomEntity)
        {
            //add all with different Team Id
            for(int i = 0; i < e->size(); i++)
            {
                if(e->at(i)->GetTeamId() != teamId && !e->at(i)->IsDead())
                    targets.push_back(e->at(i));
            }
            for(int i = 0; i < p->size(); i++)
            {
                if(p->at(i)->GetTeamId() != teamId && !p->at(i)->IsDead())
                    targets.push_back(p->at(i).get());
            }
        }
        else if(targetType == BattleEnums::TargetOwnTeam || targetType == BattleEnums::TargetOwnTeamRandomEntity)
        {
            //add all with same Team Id
            for(int i = 0; i < e->size(); i++)
            {
                if(e->at(i)->GetTeamId() == teamId && !e->at(i)->IsDead())
                    targets.push_back(e->at(i));
            }
            for(int i = 0; i < p->size(); i++)
            {
                if(p->at(i)->GetTeamId() == teamId && !p->at(i)->IsDead())
                    targets.push_back(p->at(i).get());
            }
        }

        if(targetType == BattleEnums::TargetEnemyTeamRandomEntity || targetType == BattleEnums::TargetOwnTeamRandomEntity)
        {
            //Remove all but one random target from the targets vector
            if(targets.size() > 1)
            {
                //The Id of the random Target to be chosen
                int targetId = rand() % targets.size();

                if(targetId > 0)
                {
                    //Remove all before the chosen target
                    targets.erase(targets.begin(), targets.begin() + targetId);
                }

                if(targets.size() > 1)
                {
                    //Remove all after the chosen target
                    targets.erase(targets.begin() + 1, targets.end());
                }
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
    if(m_effects.size() > 0)
        return Localization::GetInstance()->GetLocalization(m_effects[0]->GetName());
    return m_name;
}

std::string Skill::GetLocalizedDescription()
{
    Localization* localization = Localization::GetInstance();
    std::string toLocalize("effect.target.");
    toLocalize += std::to_string(m_defaultTarget);
    std::string retval = localization->GetLocalization(toLocalize);
    for(int i = 0; i < m_effects.size(); i++)
    {
        retval += " " + m_effects[i]->GetLocalizedDescription();
    }
    return retval;
}

std::vector<EffectBase*>* Skill::GetEffects()
{
    return &m_effects;
}

Skill::SkillType Skill::GetSkillType()
{
    return Usable;
}

void Skill::AddEffect(EffectBase* eff, bool isPositive)
{
    m_effectIds.push_back(eff->GetFactory()->GetId());
    m_effectStrength.push_back(*eff->GetStrength());
    m_effects.push_back(eff);
    m_isPositive.push_back(isPositive);
    if(isPositive)
        m_manaUseBase += eff->GetValue();
    else
        m_manaUseBase -= 0.5 * eff->GetValue();
}

int Skill::GetManaUse()
{
    return std::ceil(std::sqrt(m_manaUseBase));
}

int Skill::GetManaBase()
{
    return m_manaUseBase;
}
