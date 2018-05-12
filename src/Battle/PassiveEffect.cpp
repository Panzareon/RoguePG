#include "Battle/PassiveEffect.h"
#include "Battle/EffectBase.h"
#include "Localization.h"

PassiveEffect::PassiveEffect(bool buff, int duration, NamedItem* causingEffect, bool staysAfterBattle)
{
    //ctor
    m_buff = buff;
    m_duration = duration;
    m_staysAfterBattle = staysAfterBattle;
    m_causingEffect = causingEffect;
    m_movementspeedMultiplier = 1.0f;
    m_showEnemyHealth = false;
    m_additionalDescription = "";
    m_additionalDescriptionValues = nullptr;

    //Passive Effect have higher Prio (are called later) than equipment by default
    m_prio = 100;
}

PassiveEffect::PassiveEffect(bool buff, int duration, std::string name, std::string description, bool staysAfterBattle)
{
    //ctor
    m_buff = buff;
    m_duration = duration;
    m_staysAfterBattle = staysAfterBattle;
    m_causingEffect = nullptr;
    m_name = name;
    m_description = description;
    m_movementspeedMultiplier = 1.0f;
    m_showEnemyHealth = false;
    m_additionalDescription = "";
    m_additionalDescriptionValues = nullptr;

    //Passive Effect have higher Prio (are called later) than equipment by default
    m_prio = 100;
}

PassiveEffect::~PassiveEffect()
{
    //dtor
    for(int i = 0; i < m_resistanceFunction.size(); i++)
        delete m_resistanceFunction[i];
    for(int i = 0; i < m_attributeFunction.size(); i++)
        delete m_attributeFunction[i];
    for(int i = 0; i < m_onAttacked.size(); i++)
        delete m_onAttacked[i];
    for(int i = 0; i < m_getExp.size(); i++)
        delete m_getExp[i];
    for(int i = 0; i < m_onBattleFinished.size(); i++)
        delete m_onBattleFinished[i];
    for(int i = 0; i < m_onLooseHp.size(); i++)
        delete m_onLooseHp[i];

    if(m_additionalDescriptionValues != nullptr)
    {
        delete m_additionalDescriptionValues;
    }
}

void PassiveEffect::OnTurn(Entity* target)
{
    if(m_duration > 0)
    {
        m_duration--;
    }
    IPassiveEffect::OnTurn(target);
}

float PassiveEffect::GetResistance(float resistanceValue, BattleEnums::AttackType type)
{
    //If this Effect should change the resistance to a Attack Type, do it here
    for(int i = 0; i < m_resistanceFunction.size(); i++)
        resistanceValue = (*m_resistanceFunction[i])(resistanceValue,type);
    return resistanceValue;
}

float PassiveEffect::GetAttribute(float attributeValue, BattleEnums::Attribute attribute)
{
    //If this Effect should change the attribute do it here
    for(int i = 0; i < m_attributeFunction.size(); i++)
        attributeValue = (*m_attributeFunction[i])(attributeValue,attribute);
    return attributeValue;
}

float PassiveEffect::GetExp(float exp)
{
    //this is called when the Entity gains Exp
    for(int i = 0; i < m_getExp.size(); i++)
        exp = (*m_getExp[i])(exp);
    return exp;
}

void PassiveEffect::OnBattleFinished(Entity* target)
{
    //this is called when the Entity gains Exp
    for(int i = 0; i < m_onBattleFinished.size(); i++)
        (*m_onBattleFinished[i])(target);
}

void PassiveEffect::AddAttributeEffect(std::function<float(float, BattleEnums::Attribute)>* attributeFunction)
{
    m_attributeFunction.push_back(attributeFunction);
}

void PassiveEffect::GetAttacked(Attack* att, Entity* target, Entity* attacker)
{
    for(int i = 0; i < m_onAttacked.size(); i++)
        (*m_onAttacked[i])(att, target, attacker);
}

void PassiveEffect::AddOnAttacked(std::function<void(Attack*, Entity*, Entity*)>* onAttacked)
{
    m_onAttacked.push_back(onAttacked);
}

int PassiveEffect::LooseHp(Attack* att, Entity* target, Entity* attacker, int baseAmount)
{
    for(int i = 0; i < m_onLooseHp.size(); i++)
        baseAmount = (*m_onLooseHp[i])(att, target, attacker,baseAmount);
    return baseAmount;
}

void PassiveEffect::AddOnLooseHp(std::function<int(Attack*, Entity*, Entity*, int)>* onLooseHp)
{
    m_onLooseHp.push_back(onLooseHp);
}

void PassiveEffect::AddGetExp(std::function<float(float)>* getExp)
{
    m_getExp.push_back(getExp);
}

void PassiveEffect::AddGetResistance(std::function<float(float, BattleEnums::AttackType)>* getResistance)
{
    m_resistanceFunction.push_back(getResistance);
}

void PassiveEffect::AddOnBattleFinished(std::function<void(Entity*)>* onBattleFinished)
{
    m_onBattleFinished.push_back(onBattleFinished);
}


bool PassiveEffect::IsStillActive()
{
    return m_duration != 0;
}

bool PassiveEffect::StaysAfterBattle()
{
    return m_staysAfterBattle;
}

bool PassiveEffect::SetDuration(int duration)
{
    m_duration = duration;
}

int PassiveEffect::GetActivationPriority()
{
    return m_prio;
}

void PassiveEffect::SetActivationPriority(int prio)
{
    m_prio = prio;
}

std::string PassiveEffect::GetName()
{
    if(m_causingEffect != nullptr)
    {
        return m_causingEffect->GetName();
    }
    else
    {
        return m_name;
    }
}

std::string PassiveEffect::GetLocalizedDescription()
{
    std::string retval = "";

    if(m_duration > 0)
    {
        std::vector<float> values;
        values.push_back(m_duration);
        retval += Localization::GetInstance()->GetLocalizationWithFloats("effect.duration", &values) + " ";
    }

    if(m_causingEffect != nullptr)
    {
        retval += m_causingEffect->GetLocalizedDescription();
    }
    else
    {
        retval += m_description;
    }

    if(m_additionalDescription != "")
    {
        retval += " " + Localization::GetInstance()->GetLocalizationWithFloats(m_additionalDescription, m_additionalDescriptionValues);
    }

    return retval;
}

void PassiveEffect::AddDescription(std::string descriptionName, std::vector<float>* descriptionValues)
{
    m_additionalDescription = descriptionName;
    m_additionalDescriptionValues = descriptionValues;
}

bool PassiveEffect::ShowEnemyHealth(bool base)
{
    return base || m_showEnemyHealth;
}

bool PassiveEffect::ShowCompleteMap(bool base)
{
    return base || m_showCompleteMap;
}

float PassiveEffect::Movementspeed(float base)
{
    return base * m_movementspeedMultiplier;
}

void PassiveEffect::SetMovementSpeedMultiplier(float mult)
{
    m_movementspeedMultiplier *= mult;
}

void PassiveEffect::SetShowEnemyHealth(bool show)
{
    m_showEnemyHealth = show;
}

void PassiveEffect::SetShowCompleteMap(bool show)
{
    m_showCompleteMap = show;
}
