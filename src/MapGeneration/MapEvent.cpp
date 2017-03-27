#include "MapGeneration/MapEvent.h"

MapEvent::MapEvent()
{
    //ctor
    m_needButton = false;
    m_isActivated = false;
    m_finished = false;
}

MapEvent::MapEvent(bool needButton)
{
    //ctor
    m_needButton = needButton;
    m_isActivated = false;
    m_finished = false;
}

MapEvent::~MapEvent()
{
    //dtor
}

bool MapEvent::NeedButtonPress()
{
    return m_needButton;
}
bool MapEvent::IsFinished()
{
    return m_finished;
}
bool MapEvent::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime)
{
    return true;
}

void MapEvent::AfterLoad(SceneManager* sm)
{
    //NOOP
}


void MapEvent::Activate()
{
    if(!m_isActivated)
    {
        m_isActivated = true;
        //start this event
        //NOOP
    }
}
