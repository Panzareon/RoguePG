#include "Animation.h"

Animation::Animation(float maxTime)
{
    //ctor
    m_animationTime = 0.0f;
    m_maxTime = maxTime;
}

Animation::~Animation()
{
    //dtor
    for(auto it = m_animationParts.begin(); it != m_animationParts.end(); it++)
    {
        delete *it;
    }
}

void Animation::PassTime(float Time)
{
    m_animationTime += Time;
    //check if next Animation Step
    for(auto it = m_animationParts.begin(); it != m_animationParts.end(); it++)
    {
        (*it)->animate(m_animationTime);
    }
}

bool Animation::IsFinished()
{
    for(auto it = m_animationParts.begin(); it != m_animationParts.end(); it++)
    {
        if(!(*it)->IsFinished())
            return false;
    }
    return m_animationTime >= m_maxTime;
}

void Animation::AddStep(AnimationPart* part)
{
    m_animationParts.push_back(part);
}
