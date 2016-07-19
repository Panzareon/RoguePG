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

    SceneManagerDungeon sceneManager(&window,width,height);

//
//        sf::Texture heroTexture;
//        sf::String texturePath = "texture/skeleton-large.png";
//        if(!heroTexture.loadFromFile(texturePath))
//        {
//            std::cout << "Could not load Texture: " << texturePath.toAnsiString() << std::endl;
//        }
//        sf::Sprite hero;
//        hero.setTexture(heroTexture);
//        hero.setTextureRect(sf::IntRect(0,0,63,63));
//        AnimatedNode* heroNode = new AnimatedNode(hero);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sceneManager.NextTick();
//
//        heroNode->Tick(.01f);
//        heroNode->draw(window,sf::Transform::Identity);
        window.display();
    }

    return 0;
}
