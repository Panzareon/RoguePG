#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "MapFillDungeon.h"

#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::View view(sf::FloatRect(0,0,640,480));
    window.setView(view);
    window.setVerticalSyncEnabled(true);



    TileMap tileMap;
    TileMap tileMapWall;
    TileMap tileMapItems;
    TileMap tileMapAboveHero;
    TileMap tileMapAboveWall;
    tileMap.setTexture("texture/TileMap.png");
    tileMapWall.setTexture("texture/TileMap.png");
    tileMapItems.setTexture("texture/TileMap.png");
    tileMapAboveHero.setTexture("texture/TileMap.png");
    tileMapAboveWall.setTexture("texture/TileMap.png");
 //   tileMap.scale(0.2,0.2);

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



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            Map map(100,100,5);
            MapGenerator generator(&map);

            generator.CellularAutomata(0.45f);

            //generator.NumberRooms();

            MapFillDungeon mapFill(&map);
            mapFill.FillLayer(0);
            mapFill.FillLayer(1);
            mapFill.FillLayer(4);
            mapFill.FillLayer(2,3);

            map.writeToTileMap(tileMap,0);
            map.writeToTileMap(tileMapWall,1);
            map.writeToTileMap(tileMapItems,2);
            map.writeToTileMap(tileMapAboveHero,3);
            sf::Color halfTransparent(255,255,255,220);
            map.writeToTileMap(tileMapAboveWall,4, halfTransparent);

        }

        window.clear();
        window.draw(tileMap);
        window.draw(tileMapItems);
        window.draw(tileMapWall);
        window.draw(tileMapAboveHero);
        window.draw(tileMapAboveWall);
        window.display();

    }

    return 0;
}
