#include "Battle/IPassiveEffect.h"

IPassiveEffect::IPassiveEffect()
{
    //ctor
}

IPassiveEffect::~IPassiveEffect()
{
    //dtor
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

float IPassiveEffect::Movementspeed(float base)
{
    return base;
}

bool IPassiveEffect::DeleteEffect()
{
    return true;
}


float IPassiveEffect::GetNeededMP(float base)
{
    //this is called to set the needed Mp for a skill
    for(int i = 0; i < m_getNeededMp.size(); i++)
        base = (*m_getNeededMp[i])(base);
}

void IPassiveEffect::AddGetNeededMp(std::function<float(float)>* getMp)
{
    m_getNeededMp.push_back(getMp);
}
