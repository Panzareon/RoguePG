#include "Battle/PassiveEffect.h"
#include "Battle/EffectBase.h"

PassiveEffect::PassiveEffect(bool buff, int duration, NamedItem* causingEffect, bool staysAfterBattle)
{
    //ctor
    m_buff = buff;
    m_duration = duration;
    m_onTurn = nullptr;
    m_attributeFunction = nullptr;
    m_resistanceFunction = nullptr;
    m_attack = nullptr;
    m_onAttacked = nullptr;
    m_onBattleFinished = nullptr;
    m_getExp = nullptr;
    m_staysAfterBattle = staysAfterBattle;
    m_causingEffect = causingEffect;
}

PassiveEffect::~PassiveEffect()
{
    //dtor
    if(m_onTurn != nullptr)
        delete m_onTurn;
    if(m_resistanceFunction != nullptr)
        delete m_resistanceFunction;
    if(m_attributeFunction != nullptr)
        delete m_attributeFunction;
    if(m_attack != nullptr)
        delete m_attack;
    if(m_onAttacked != nullptr)
        delete m_onAttacked;
    if(m_getExp != nullptr)
        delete m_getExp;
}

void PassiveEffect::AddOnTurnEffect(std::function<void(Entity*, PassiveEffect*)>* onTurn)
{
    if(m_onTurn != nullptr)
        delete m_onTurn;
    m_onTurn = onTurn;
}

void PassiveEffect::OnTurn(Entity* target)
{
    if(m_duration > 0)
    {
        m_duration++;
    }
    if(m_onTurn != nullptr)
        (*m_onTurn)(target, this);
}

float PassiveEffect::GetResistance(float resistanceValue, BattleEnums::AttackType type)
{
    //If this Effect should change the resistance to a Attack Type, do it here
    if(m_resistanceFunction == nullptr)
        return resistanceValue;
    return (*m_resistanceFunction)(resistanceValue,type);
}

float PassiveEffect::GetAttribute(float attributeValue, BattleEnums::Attribute attribute)
{
    //If this Effect should change the attribute do it here
    if(m_attributeFunction == nullptr)
        return attributeValue;
    return (*m_attributeFunction)(attributeValue,attribute);
}

float PassiveEffect::GetExp(float exp)
{
    //this is called when the Entity gains Exp
    if(m_getExp == nullptr)
        return exp;
    return (*m_getExp)(exp);
}

void PassiveEffect::OnBattleFinished(Entity* target)
{
    //this is called when the Entity gains Exp
    if(m_onBattleFinished != nullptr)
        (*m_onBattleFinished)(target);
}

void PassiveEffect::AddAttributeEffect(std::function<float(float, BattleEnums::Attribute)>* attributeFunction)
{
    if(m_attributeFunction != nullptr)
        delete m_attributeFunction;
    m_attributeFunction = attributeFunction;
}
void PassiveEffect::AttackEntity(Attack* att, Entity* target, Entity* attacker)
{
    //Change Attack Damage or add Attack Type
    if(m_attack != nullptr)
        (*m_attack)(att, target, attacker);
}

void PassiveEffect::GetAttacked(Attack* att, Entity* target, Entity* attacker)
{
    if(m_onAttacked != nullptr)
        (*m_onAttacked)(att, target, attacker);
}

void PassiveEffect::AddAttack(std::function<void(Attack*, Entity*, Entity*)>* attack)
{
    if(m_attack != nullptr)
        delete m_attack;
    m_attack = attack;
}

void PassiveEffect::AddOnAttacked(std::function<void(Attack*, Entity*, Entity*)>* onAttacked)
{
    if(m_onAttacked != nullptr)
        delete m_onAttacked;
    m_onAttacked = onAttacked;
}

void PassiveEffect::AddGetExp(std::function<float(float)>* getExp)
{
    if(m_getExp != nullptr)
        delete m_getExp;
    m_getExp = getExp;
}

void PassiveEffect::AddGetResistance(std::function<float(float, BattleEnums::AttackType)>* getResistance)
{
    if(m_resistanceFunction != nullptr)
        delete m_resistanceFunction;
    m_resistanceFunction = getResistance;
}

void PassiveEffect::AddOnBattleFinished(std::function<void(Entity*)>* onBattleFinished)
{
    if(m_onBattleFinished != nullptr)
        delete m_onBattleFinished;
    m_onBattleFinished = onBattleFinished;
}


bool PassiveEffect::IsStillActive()
{
    return m_duration != 0;
}

bool PassiveEffect::StaysAfterBattle()
{
    return m_staysAfterBattle;
}

int PassiveEffect::GetActivationPriority()
{
    return m_prio;
}

std::string PassiveEffect::GetName()
{
    return m_causingEffect->GetName();
}

std::string PassiveEffect::GetLocalizedDescription()
{
    return m_causingEffect->GetLocalizedDescription();
}
