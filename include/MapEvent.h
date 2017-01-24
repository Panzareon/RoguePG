#ifndef MAPEVENT_H
#define MAPEVENT_H

#include "Enums.h"
#include "SFML/Graphics/Rect.hpp"

class MapEvent
{
    public:
        MapEvent(bool needButton);
        virtual ~MapEvent();

        bool NeedButtonPress();
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection);
        virtual void Activate();
        bool IsFinished();

    protected:
        bool m_needButton;
        bool m_isActivated;
        bool m_finished;
    private:
};

#endif // MAPEVENT_H
