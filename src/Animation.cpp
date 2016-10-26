#include "Animation.h"

Animation::Animation()
{
    //ctor
    m_animationTime = 0.0f;
    //TODO: get actual Value
    m_maxTime = 2.0f;
}

Animation::~Animation()
{
    //dtor
}

void Animation::PassTime(float Time)
{
    m_animationTime += Time;
    //check if next Animation Step
    for(auto it = m_animationParts.begin(); it != m_animationParts.end(); it++)
    {
        (*it).animate(m_animationTime);
    }
}

bool Animation::IsFinished()
{
    return m_animationTime >= m_maxTime;
}
