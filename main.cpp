#include <SFML/Graphics.hpp>
#include "SceneManager/SceneManagerMainMenu.h"

#include <random>
#include <time.h>
#include <iostream>
#include "Controller/GameController.h"
#include "Controller/Localization.h"
#include "Exception/GenericException.h"
#include <fstream>

int main()
{
    srand((int)time(NULL));
    GameController* controller = GameController::getInstance();
    int width = controller->GetWindowWidth();
    int height = controller->GetWindowHeight();

    Localization* local = Localization::GetInstance();
    sf::RenderWindow window(sf::VideoMode(width, height), local->GetLocalization("main.window.title"));
    sf::View view(sf::FloatRect(0,0, (float)width,(float)height));
    window.setView(view);
    window.setVerticalSyncEnabled(true);
    controller->SetRenderTarget(&window);

    SceneManager* sm = new SceneManagerMainMenu();
    controller->LoadSceneManager(sm);

    try
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::GainedFocus)
                    controller->SetWindowFocus(true);
                else if (event.type == sf::Event::LostFocus)
                    controller->SetWindowFocus(false);
                else if (event.type == sf::Event::KeyPressed)
                    Configuration::GetInstance()->SetLastKeyPressed(event.key.code);
            }

            controller->Tick();
            window.display();
        }
    }
    catch(std::exception& ex)
    {
        std::ofstream o("crash.log");
        o << ex.what() << std::endl;
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
