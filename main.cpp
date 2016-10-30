#include <SFML/Graphics.hpp>
#include "SceneManagerDungeon.h"

#include <random>
#include <time.h>
#include <iostream>
#include "AnimatedNode.h"
#include "GameController.h"
#include "EffectFactoryList.h"
#include "Localization.h"
#include "CharacterClass.h"

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
    SceneManagerDungeon* sceneManager = new SceneManagerDungeon(&window,width,height, 30,30);
    controller->LoadSceneManager(sceneManager);


    Party party;
    //create party with 2 member
    int partyInitialSize = 2;
    for(int i = 0; i < partyInitialSize; i++)
    {
        PartyMember* p = CharacterClass::GetRandomCharacterClass()->GetNewPartyMember();
        p->SetTeamId(0);
        party.AddPartyMember(p);
    }
    controller->setParty(&party);

    while (window.isOpen())
    {
        std::cout << "nextTick" << std::endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        controller->Tick();
        window.display();
    }

    return 0;
}
