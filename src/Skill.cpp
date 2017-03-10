#include "Skill.h"
#include "InvalidArgumentException.h"
#include "Effect.h"
#include "GameController.h"
#include "Localization.h"
#include "NameGenerator.h"

#include <math.h>

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
        std::vector<PartyMember*> * p = GameController::getInstance()->getParty()->GetActivePartyMembers();
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
                    targets.push_back(p->at(i));
            }
        }
        else if(targetType == BattleEnums::TargetEnemyTeam)
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
                    targets.push_back(p->at(i));
            }
        }
        else if(targetType == BattleEnums::TargetOwnTeam)
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

std::vector<Effect*>* Skill::GetEffects()
{
    return &m_effects;
}

void Skill::AddEffect(Effect* eff, bool isPositive)
{
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
