#ifndef MAPEVENT_H
#define MAPEVENT_H

#include "Controller/Enums.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"

class MapEvent
{
    public:
        MapEvent(bool needButton);
        virtual ~MapEvent();

        bool NeedButtonPress();
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime);
        virtual void Activate();
        bool IsFinished();

    protected:
        bool m_needButton;
        bool m_isActivated;
        bool m_finished;
    private:
};

#endif // MAPEVENT_H
