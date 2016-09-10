#include "PassiveEffect.h"

PassiveEffect::PassiveEffect(Entity* target, bool buff, int duration)
{
    //ctor
    m_target = target;
    m_buff = buff;
    m_duration = duration;
}

PassiveEffect::~PassiveEffect()
{
    //dtor
}

void PassiveEffect::OnTurn()
{
    if(m_duration > 0)
    {
        m_duration++;
    }
}

float PassiveEffect::GetAttribute(float attributeValue, BattleEnums::Attribute attribute)
{
    //If this Effect should change the attribute do it here
    return attributeValue;
}

bool PassiveEffect::IsStillActive()
{
    return m_duration != 0;
}

int PassiveEffect::GetActivationPriority()
{
    return m_prio;
}
