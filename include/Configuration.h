#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics.hpp>

class Configuration
{
    public:
        virtual ~Configuration();
        static Configuration* GetInstance();
        sf::Font* GetFont();

        sf::Keyboard::Key GetMoveUpKey();
        sf::Keyboard::Key GetMoveDownKey();
        sf::Keyboard::Key GetMoveRightKey();
        sf::Keyboard::Key GetMoveLeftKey();
        sf::Keyboard::Key GetAcceptKey();
        sf::Keyboard::Key GetCancelKey();


        int GetMaxPartySize();

    protected:
        Configuration();
        static Configuration* m_instance;
    private:
        sf::Font m_font;

        sf::Keyboard::Key m_moveUp;
        sf::Keyboard::Key m_moveDown;
        sf::Keyboard::Key m_moveRight;
        sf::Keyboard::Key m_moveLeft;

        sf::Keyboard::Key m_accept;
        sf::Keyboard::Key m_cancel;

        int m_maxPartySize;
};

#endif // CONFIGURATION_H
