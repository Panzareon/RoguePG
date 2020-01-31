#include "SceneManager/SceneManagerGameMenu.h"
#include "SceneManager/SceneManagerEquipment.h"
#include "SceneManager/SceneManagerStatus.h"
#include "SceneManager/SceneManagerMessage.h"
#include "Controller/GameController.h"
#include "SceneGraph/DrawableNode.h"
#include "Controller/Localization.h"

#include <iostream>

namespace MenuFunctions
{
    void OpenEquipment()
    {
        SceneManagerEquipment* sm = new SceneManagerEquipment();
        GameController::getInstance()->LoadSceneManager(sm);
    }

    void OpenStatus()
    {
        SceneManagerStatus* sm = new SceneManagerStatus();
        GameController::getInstance()->LoadSceneManager(sm);
    }

    void Quit(SceneManagerGameMenu* sm)
    {
        sm->Quit();
    }

    void Save(SceneManagerGameMenu* smgm)
    {
        GameController::getInstance()->SaveToFile();
        SceneManagerMessage* sm = new SceneManagerMessage(Localization::GetInstance()->GetLocalization("menu.save.finished"));
        sm->OnAccept(std::function<void()>(std::bind(&MenuFunctions::Quit,smgm)));
        GameController::getInstance()->LoadSceneManager(sm);
    }

    void Options();
}

SceneManagerGameMenu::SceneManagerGameMenu()
{
    //ctor
    int padding = 8;



    //Set Background
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::TextureFiles::InGameMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);

    //Add Money amount
    Localization* local = Localization::GetInstance();

    std::vector<std::string> moneyValue;
    moneyValue.push_back(std::to_string(GameController::getInstance()->getParty()->GetMoney()));
    TextNode* money = new TextNode(local->GetLocalizationWithStrings("menu.money", &moneyValue));
    money->SetFontSize(25);
    money->SetColor(sf::Color::Black);

    sf::FloatRect rect = money->getBoundingBox();

    sf::RectangleShape* moneyBackground = new sf::RectangleShape(sf::Vector2f(rect.width + 6.0f, rect.height + 10.0f));
    moneyBackground->setFillColor(sf::Color::White);
    moneyBackground->setOutlineColor(sf::Color::Black);
    moneyBackground->setOutlineThickness(2.0f);

    Node* moneyBackgroundNode = new DrawableNode(moneyBackground);
    moneyBackgroundNode->moveNode(20.0f, y + 5.0f);

    money->moveNode(2.0f, 0.0f);
    m_gui->addChild(moneyBackgroundNode);
    moneyBackgroundNode->addChild(money);

    //Set Menu function
    m_mainMenu = new MenuNode(background->getBoundingBox().width - 2* padding);
    m_mainMenu->SetMaxShownOptions(5);
    m_mainMenu->AddOption(local->GetLocalization("menu.equipment"),std::function<void()>(&MenuFunctions::OpenEquipment),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.status"),std::function<void()>(&MenuFunctions::OpenStatus),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.option"),std::function<void()>(&MenuFunctions::Options),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.save"),std::function<void()>(std::bind(&MenuFunctions::Save,this)),true);
    background->addChild(m_mainMenu);

    //Set Menu looks
    m_mainMenu->SetPadding(padding,padding);
    m_mainMenu->SetBackgroundColor(sf::Color::Transparent);
    m_mainMenu->SetForegroundColor(sf::Color::Black);
    m_mainMenu->SetOutlineColor(sf::Color::Transparent);
    m_mainMenu->SetSelectedTexture(TextureList::getTexture(TextureList::TextureFiles::InGameMenuSelected));
    m_mainMenu->SetFontSize(50);
    m_mainMenu->SetSpacing(29);
    m_finished = false;
}

SceneManagerGameMenu::~SceneManagerGameMenu()
{
    //dtor
}

bool SceneManagerGameMenu::IsTransparent()
{
    return true;
}

bool SceneManagerGameMenu::PausesSceneManagerBelow()
{
    return true;
}

bool SceneManagerGameMenu::IsFinished()
{
    return m_finished;
}


void SceneManagerGameMenu::Tick()
{
    GameController* controller = GameController::getInstance();
    //Check Menu inputs
    m_mainMenu->CheckKeyboardInput();
    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel))
    {
        //Close Menu
        m_finished = true;
    }
}


void SceneManagerGameMenu::Quit()
{
    //Quit to Main menu
    GameController::getInstance()->QuitTo(SceneManager::SceneManagerType::MainMenu);
}

SceneManager::SceneManagerType SceneManagerGameMenu::GetType()
{
    return SceneManagerType::Menu;
}
