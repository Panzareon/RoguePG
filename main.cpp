#include <SFML/Graphics.hpp>
#include "SceneManagerDungeon.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::View view(sf::FloatRect(0,0,640,480));
    window.setView(view);
    window.setVerticalSyncEnabled(true);

    SceneManagerDungeon sceneManager(&window);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sceneManager.NextTick();
        window.display();
    }

    return 0;
}
