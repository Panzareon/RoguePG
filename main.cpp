#include <SFML/Graphics.hpp>
#include "SceneManagerMainMenu.h"

#include <random>
#include <time.h>
#include <iostream>
#include "AnimatedNode.h"
#include "GameController.h"
#include "EffectFactoryList.h"
#include "Localization.h"
#include "CharacterClass.h"
#include "GenericException.h"

int main()
{
    srand(time(NULL));
    GameController* controller = GameController::getInstance();
    int width = controller->GetWindowWidth();
    int height = controller->GetWindowHeight();

    Localization* local = Localization::GetInstance();
    sf::RenderWindow window(sf::VideoMode(width, height), local->GetLocalization("main.window.title"));
    sf::View view(sf::FloatRect(0,0,width,height));
    window.setView(view);
    window.setVerticalSyncEnabled(true);
    controller->SetRenderTarget(&window);

    SceneManager* sm = new SceneManagerMainMenu(&window,width, height );
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
            }

            controller->Tick();
            window.display();
        }
    }
    catch(GenericException ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
