#include "AnimationPart.h"

AnimationPart::AnimationPart(Animation* animation)
{
    //ctor
    m_status = 0;
    m_animation = animation;
}

AnimationPart::~AnimationPart()
{
    //dtor
}

void AnimationPart::animate(float newTime)
{
    if(!m_status == 0 && newTime > m_start)
    {
        //Start Animation
        m_status = 1;
        //TODO: Start Animation
    }
    else if(m_status == 1 && newTime > m_end)
    {
        //Stop Animation
        m_status = 2;
        //TODO: Stop Animation
    }
    else if(m_status == 1)
    {
        //Animation step
        float percent = (m_end - newTime) / (m_end - m_start);
        //TODO: actual Animation for percent from 0 to 1
    }
}
