#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics.hpp>

class Configuration
{
    public:
        enum Keys{MoveUp, MoveDown, MoveRight,MoveLeft,Accept,Cancel};
        virtual ~Configuration();
        static Configuration* GetInstance();
        sf::Font* GetFont();


        sf::Keyboard::Key GetKey(Keys key);

        int GetMaxPartySize();

        int GetNumberKeys();

    protected:
        Configuration();
        static Configuration* m_instance;
    private:
        sf::Font m_font;

        std::vector<sf::Keyboard::Key> m_keys;

        int m_maxPartySize;
};

#endif // CONFIGURATION_H
