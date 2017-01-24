#include "MapEvent.h"

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
bool MapEvent::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection)
{
    return true;
}

void MapEvent::Activate()
{
    if(!m_isActivated)
    {
        m_isActivated = true;
        //TODO: start this event
    }
}
