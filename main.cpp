#include <SFML/Graphics.hpp>
#include "SceneManagerDungeon.h"

#include <iostream>
#include "AnimatedNode.h"
#include "GameController.h"
#include "EffectFactoryList.h"

int main()
{
    GameController* controller = GameController::getInstance();
    int width = controller->GetWindowWidth();
    int height = controller->GetWindowHeight();

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    sf::View view(sf::FloatRect(0,0,width,height));
    window.setView(view);
    window.setVerticalSyncEnabled(true);

    controller->SetRenderTarget(&window);
    SceneManagerDungeon* sceneManager = new SceneManagerDungeon(&window,width,height, 30,30);
    controller->LoadSceneManager(sceneManager);


    //TODO: create actual party
    Party party;
    PartyMember* member = new PartyMember();

    Skill* newSkill = new Skill(member);
    newSkill->AddEffect(EffectFactoryList::GetInstance()->getRandom()->GetEffectWithValue(10.0f, BattleEnums::TargetEnemyTeamEntity));
    member->AddSkill(newSkill);
    party.AddPartyMember(member);
    controller->setParty(&party);

    while (window.isOpen())
    {
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
