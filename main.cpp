#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "MapFillDungeon.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::View view(sf::FloatRect(0,0,640,480));
    window.setView(view);



    TileMap tileMap;
    tileMap.setTexture("texture/TileMap.png");
 //   tileMap.scale(0.2,0.2);

    Map map(30,30,1);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Movement for now
        float MoveSpeed = 0.3f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            view.move(-MoveSpeed,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            view.move(MoveSpeed,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            view.move(0,-MoveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            view.move(0,MoveSpeed);
        }
        window.setView(view);



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            MapGenerator generator(&map);

            generator.CellularAutomata(0.45f);

            //generator.NumberRooms();

            MapFillDungeon mapFill(&map);
            mapFill.FillLayer(0);

            map.writeToTileMap(tileMap,0);

        }

        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}
