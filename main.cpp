#include <SFML/Graphics.hpp>
#include "SceneManagerDungeon.h"

#include <iostream>
#include "AnimatedNode.h"
#include "GameController.h"
#include "EffectFactoryList.h"
#include "Localization.h"

int main()
{
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


    //TODO: create actual party
    Party party;
    PartyMember* member = new PartyMember();

    BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
    Skill* newSkill = new Skill(member,target);
    newSkill->AddEffect(EffectFactoryList::GetInstance()->getRandom(BattleEnums::AttackTypeFire, BattleEnums::EffectTypeDamage)->GetEffectWithValue(10.0f, target));
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
