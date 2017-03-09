#include "SceneManagerMainMenu.h"
#include <SFML/Graphics.hpp>
#include "TextureList.h"
#include "DrawableNode.h"
#include "GameController.h"
#include "Localization.h"
#include "CharacterClass.h"
#include "ItemFactory.h"

#include <iostream>

namespace MenuFunctions
{
    void StartDungeon(SceneManagerMainMenu* sm)
    {
        sm->StartDungeon();
    }
    void Quit(SceneManagerMainMenu* sm)
    {
        sm->Quit();
    }
    void Keybindings(SceneManagerMainMenu* sm)
    {
        sm->Keybindings();
    }
    void SetKey(SceneManagerMainMenu* sm, Configuration::Keys key)
    {
        sm->SetKey(key);
    }
}

SceneManagerMainMenu::SceneManagerMainMenu(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
{
    //ctor
    //ctor
    int padding = 8;
    m_configKey = false;

    //Set Background
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::InGameMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);

    //Set Menu function
    m_mainMenu = new MenuNode(background->getBoundingBox().width - 2* padding);
    Localization* local = Localization::GetInstance();
    m_mainMenu->AddOption(local->GetLocalization("menu.startDungeon"),std::function<void()>(std::bind(&MenuFunctions::StartDungeon,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.keyBindings"),std::function<void()>(std::bind(&MenuFunctions::Keybindings,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.quit"),std::function<void()>(std::bind(&MenuFunctions::Quit,this)),true);
    background->addChild(m_mainMenu);

    //Set Menu looks
    m_mainMenu->SetPadding(padding,padding);
    m_mainMenu->SetBackgroundColor(sf::Color::Transparent);
    m_mainMenu->SetForegroundColor(sf::Color::Black);
    m_mainMenu->SetOutlineColor(sf::Color::Transparent);
    m_mainMenu->SetSelectedTexture(TextureList::getTexture(TextureList::InGameMenuSelected));
    m_mainMenu->SetFontSize(45);
    m_mainMenu->SetSpacing(34);
}

SceneManagerMainMenu::~SceneManagerMainMenu()
{
    //dtor
}

void SceneManagerMainMenu::StartDungeon()
{
    GameController* controller = GameController::getInstance();
    Party* party = new Party();
    //create new party with 2 member
    int partyInitialSize = 2;
    for(int i = 0; i < partyInitialSize; i++)
    {
        PartyMember* p = CharacterClass::GetRandomCharacterClass()->GetNewPartyMember();
        p->SetTeamId(0);
        party->AddPartyMember(p);
    }
    controller->setParty(party);

    std::vector<PartyMember*>* partyMember = party->GetActivePartyMembers();
    ItemFactory* itemFactory = ItemFactory::GetInstance();
    for(int i = 0; i < 3; i++)
    {
        Equipment* equipment = (Equipment*)itemFactory->GetRandomEquipment(Equipment::MainHand);
        party->AddItem(equipment);
        if(partyMember->size() > i)
        {
            partyMember->at(i)->SetEquipment(Equipment::MainHand, equipment);
            partyMember->at(i)->Heal(partyMember->at(i)->GetAttribute(BattleEnums::AttributeMaxHp));
        }

    }

    DungeonConfiguration * config = new DungeonConfiguration(5, time(NULL));
    config->PlayMusic();
    controller->SetDungeonConfiguration(config);
    controller->GotoNextLevel();
}

void SceneManagerMainMenu::Keybindings()
{
    m_keybindings = new MenuNode(320);
    m_keybindings->SetPadding(3,0);
    m_keybindings->SetMaxShownOptions((int)Configuration::KEYS_END);
    m_keybindings->CancelAvailable(true);
    m_mainMenu->addChild(m_keybindings);
    Configuration* config = Configuration::GetInstance();
    Configuration::Keys key;
    Localization* local = Localization::GetInstance();
    for(int i = 0; i < (int)Configuration::KEYS_END; i++)
    {
        key = (Configuration::Keys) i;
        m_keybindings->AddOption(local->GetLocalization("menu.keyBindings." + config->KeyToString(key)), std::function<void()>(std::bind(&MenuFunctions::SetKey,this, key)));
        m_keybindings->AddValueToOption(i, config->KeyToString(config->GetKey(key)));
    }
}

void SceneManagerMainMenu::SetKey(Configuration::Keys key)
{
    m_updateKey = key;
    m_configKey = true;
    Configuration::GetInstance()->ResetLastKey();
    m_keybindings->AddValueToOption((int)m_updateKey, "_");
}

void SceneManagerMainMenu::Quit()
{
    ((sf::RenderWindow*)GameController::getInstance()->GetRenderTarget())->close();
}

void SceneManagerMainMenu::Tick()
{
    if(!m_configKey)
    {
        m_mainMenu->CheckKeyboardInput();
    }
    else
    {
        //set Keybindings
        Configuration* config = Configuration::GetInstance();
        sf::Keyboard::Key key = config->GetLastKey();
        if(key != sf::Keyboard::Unknown)
        {
            if(config->SetKeyConfig(m_updateKey, key))
            {
                GameController::getInstance()->IsKeyPressed(m_updateKey);
                m_keybindings->AddValueToOption((int)m_updateKey, config->KeyToString(key));
                m_configKey = false;
            }
        }
    }

}

bool SceneManagerMainMenu::IsFinished()
{
    return false;
}
