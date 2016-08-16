#include <SFML/Graphics.hpp>
#include "SceneManagerDungeon.h"

#include <iostream>
#include "AnimatedNode.h"

int main()
{
    int width = 640;
    int height = 480;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    sf::View view(sf::FloatRect(0,0,width,height));
    window.setView(view);
    window.setVerticalSyncEnabled(true);

    SceneManagerDungeon sceneManager(&window,width,height, 30,30);


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
