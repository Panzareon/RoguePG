#ifndef MAPEVENT_H
#define MAPEVENT_H

#include "Controller/Enums.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"

class SceneManager;

class MapEvent
{
    public:
        MapEvent();
        MapEvent(bool needButton);
        virtual ~MapEvent();

        bool NeedButtonPress();
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime);
        virtual void Activate();
        bool IsFinished();

        virtual void AfterLoad(SceneManager* sm);


        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_needButton, m_isActivated, m_finished);
        }

        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(m_needButton, m_isActivated, m_finished);
        }

    protected:
        bool m_needButton;
        bool m_isActivated;
        bool m_finished;
    private:
};

#endif // MAPEVENT_H
