#include "SceneManager/SceneManagerMainMenu.h"
#include <SFML/Graphics.hpp>
#include "SceneManager/SceneManagerOptions.h"
#include "Controller/GameController.h"
#include "SceneGraph/DrawableNode.h"
#include "Controller/Localization.h"
#include "SceneManager/SceneManagerChooseHero.h"

#include <iostream>

namespace MenuFunctions
{
    void StartDungeon(SceneManagerMainMenu* sm)
    {
        sm->ChooseHero();
    }
    void Quit(SceneManagerMainMenu* sm)
    {
        sm->Quit();
    }
    void Options()
    {
        SceneManagerOptions* sm = new SceneManagerOptions();
        GameController::getInstance()->LoadSceneManager(sm);
    }
    void Load()
    {
        GameController* controller = GameController::getInstance();
        if(controller->LoadAvailable())
            controller->LoadFromFile();
    }
}

SceneManagerMainMenu::SceneManagerMainMenu()
{
    m_checkLoad = true;
    //ctor
    int padding = 8;

    //Set Background
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::InGameMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    GameController* controller = GameController::getInstance();
    int x = controller->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = controller->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);

    //Set Menu function
    m_mainMenu = new MenuNode(background->getBoundingBox().width - 2* padding);
    Localization* local = Localization::GetInstance();
    m_mainMenu->AddOption(local->GetLocalization("menu.continue"),std::function<void()>(&MenuFunctions::Load),controller->LoadAvailable());
    m_mainMenu->AddOption(local->GetLocalization("menu.startDungeon"),std::function<void()>(std::bind(&MenuFunctions::StartDungeon,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.option"),std::function<void()>(&MenuFunctions::Options),true);
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

void SceneManagerMainMenu::ChooseHero()
{
    m_checkLoad = true;
    GameController* controller = GameController::getInstance();
    controller->InitValues();
    controller->setParty(Party());

    controller->LoadSceneManager(new SceneManagerChooseHero());
}

void SceneManagerMainMenu::Quit()
{
    ((sf::RenderWindow*)GameController::getInstance()->GetRenderTarget())->close();
}

void SceneManagerMainMenu::Tick()
{
    if(m_checkLoad)
    {
        m_checkLoad = false;
        GameController* controller = GameController::getInstance();
        m_mainMenu->SetAvailableForOption(0, controller->LoadAvailable());
    }
    m_mainMenu->CheckKeyboardInput();
}

bool SceneManagerMainMenu::IsFinished()
{
    return false;
}

SceneManager::SceneManagerType SceneManagerMainMenu::GetType()
{
    return TypeMainMenu;
}
