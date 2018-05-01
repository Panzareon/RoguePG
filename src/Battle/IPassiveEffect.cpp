#include "Battle/IPassiveEffect.h"

IPassiveEffect::IPassiveEffect()
{
    //ctor
}

IPassiveEffect::~IPassiveEffect()
{
    //dtor
    for(int i = 0; i < m_onTurn.size(); i++)
        delete m_onTurn[i];
    for(int i = 0; i < m_attack.size(); i++)
        delete m_attack[i];
    for(int i = 0; i < m_getNeededMp.size(); i++)
        delete m_getNeededMp[i];
}

bool IPassiveEffect::IsEquipment()
{
    return false;
}

void IPassiveEffect::OnEffectStart()
{
    //NOOP
}

void IPassiveEffect::OnBattleFinished(Entity* target)
{
    //NOOP
}

bool IPassiveEffect::ShowEnemyHealth(bool base)
{
    return base;
}

bool IPassiveEffect::ShowCompleteMap(bool base)
{
    return base;
}

float IPassiveEffect::Movementspeed(float base)
{
    return base;
}

bool IPassiveEffect::DeleteEffect()
{
    return true;
}

void IPassiveEffect::OnTurn(Entity* target)
{
    for(int i = 0; i < m_onTurn.size(); i++)
        (*m_onTurn[i])(target, this);
}

void IPassiveEffect::AttackEntity(Attack* att, Entity* attacker)
{
    //Change Attack Damage or add Attack Type
    for(int i = 0; i < m_attack.size(); i++)
        (*m_attack[i])(att, attacker);
}

float IPassiveEffect::GetNeededMP(float base)
{
    //this is called to set the needed Mp for a skill
    for(int i = 0; i < m_getNeededMp.size(); i++)
        base = (*m_getNeededMp[i])(base);
}

void IPassiveEffect::AddOnTurnEffect(std::function<void(Entity*, IPassiveEffect*)>* onTurn)
{
    m_onTurn.push_back(onTurn);
}

void IPassiveEffect::AddGetNeededMp(std::function<float(float)>* getMp)
{
    m_getNeededMp.push_back(getMp);
}

void IPassiveEffect::AddAttack(std::function<void(Attack*, Entity*)>* attack)
{
    m_attack.push_back(attack);
}
