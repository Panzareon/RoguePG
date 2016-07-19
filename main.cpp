#include <SFML/Graphics.hpp>
#include "SceneManagerDungeon.h"

#include <cmath>

#include "DrawableNode.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::View view(sf::FloatRect(0,0,640,480));
    window.setView(view);
    window.setVerticalSyncEnabled(true);

    SceneManagerDungeon sceneManager;


    sf::Clock clock;
    sf::Time FrameTime;
    float posx = 320;
    float posy = 240;

    while (window.isOpen())
    {
        FrameTime = clock.getElapsedTime();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Movement for now
        float MoveSpeed = 256.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            posx -= MoveSpeed * FrameTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            posx += MoveSpeed * FrameTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            posy -= MoveSpeed * FrameTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            posy += MoveSpeed * FrameTime.asSeconds();
        }
        view.setCenter(std::floor(posx), std::floor(posy));
        window.setView(view);



        window.clear();
        sceneManager.DrawScene(window);
        window.display();

    }

    return 0;
}
