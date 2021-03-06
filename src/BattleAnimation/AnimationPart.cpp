#include "BattleAnimation/AnimationPart.h"

AnimationPart::AnimationPart()
{
    //ctor
    m_status = 0;
}

AnimationPart::~AnimationPart()
{
    //dtor
}

void AnimationPart::SetTiming(float start, float end)
{
    m_start = start;
    m_end = end;
}


void AnimationPart::animate(float newTime)
{
    if(m_status == 0 && newTime > m_start)
    {
        //Start Animation
        m_status = 1;
        Start();
    }
    else if(m_status == 1 && newTime >= m_end)
    {
        //Stop Animation
        m_status = 2;
        Stop();
    }
    else if(m_status == 1)
    {
        //Animation step
        float percent = (newTime - m_start) / (m_end - m_start);
        AnimationStep(percent);
    }
}

bool AnimationPart::IsFinished()
{
    return m_status == 2;
}
