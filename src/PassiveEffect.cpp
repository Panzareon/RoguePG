#include "PassiveEffect.h"

PassiveEffect::PassiveEffect(Entity* target, bool buff, int duration)
{
    //ctor
    m_target = target;
    m_buff = buff;
    m_duration = duration;
    m_onTurn = nullptr;
    m_attributeFunction = nullptr;
}

PassiveEffect::~PassiveEffect()
{
    //dtor
    if(m_onTurn != nullptr)
        delete m_onTurn;
    if(m_attributeFunction != nullptr)
        delete m_attributeFunction;
}

void PassiveEffect::AddOnTurnEffect(std::function<void(Entity*, PassiveEffect*)>* onTurn)
{
    if(m_onTurn != nullptr)
        delete m_onTurn;
    m_onTurn = onTurn;
}

void PassiveEffect::OnTurn()
{
    if(m_duration > 0)
    {
        m_duration++;
    }
    if(m_onTurn != nullptr)
        (*m_onTurn)(m_target, this);
}

float PassiveEffect::GetAttribute(float attributeValue, BattleEnums::Attribute attribute)
{
    //If this Effect should change the attribute do it here
    if(m_attributeFunction == nullptr)
        return attributeValue;
    return (*m_attributeFunction)(attributeValue,attribute);
}

void PassiveEffect::AddAttributeEffect(std::function<float(float, BattleEnums::Attribute)>* attributeFunction)
{
    if(m_attributeFunction != nullptr)
        delete m_attributeFunction;
    m_attributeFunction = attributeFunction;
}

bool PassiveEffect::IsStillActive()
{
    return m_duration != 0;
}

int PassiveEffect::GetActivationPriority()
{
    return m_prio;
}
