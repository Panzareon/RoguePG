#include "SceneManagerStatus.h"
#include "Controller/GameController.h"
#include "Controller/Configuration.h"
#include "SceneGraph/DrawableNode.h"
#include "Controller/Localization.h"

SceneManagerStatus::SceneManagerStatus()
{
    //ctor
    m_finished = false;

    GameController* controller = GameController::getInstance();
    Party* party = controller->getParty();
    std::vector<PartyMember*>* partyMemberToShow = party->GetAllPartyMembers();
    PartyMember* member = partyMemberToShow->at(0);

    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::StatusMenu));
    Node* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);

    m_name = new TextNode();
    m_name->SetColor(sf::Color::Black);
    m_name->moveNode(5.0f, 5.0f);
    background->addChild(m_name);

    m_level = new TextNode();
    m_level->SetColor(sf::Color::Black);
    m_level->moveNode(5.0f, 105.0f);
    m_level->SetFontSize(20);
    background->addChild(m_level);


    sf::RectangleShape* expBackground = new sf::RectangleShape(sf::Vector2f(m_expWidth,m_expHeight));
    expBackground->setFillColor(sf::Color::White);
    expBackground->setOutlineColor(sf::Color::Black);
    expBackground->setOutlineThickness(1.0f);
    Node* expBackgroundNode = new DrawableNode(expBackground);
    expBackgroundNode->moveNode(10.0f, 150.0f);
    background->addChild(expBackgroundNode);

    m_exp = new sf::RectangleShape(sf::Vector2f(m_expWidth,m_expHeight));
    m_exp->setFillColor(sf::Color::Yellow);
    Node* expNode = new DrawableNode(m_exp);
    expBackgroundNode->addChild(expNode);


    m_manaAndHealth = new EntityBarsNode(member);
    m_manaAndHealth->moveNode(10.0f, 50.0f);

    background->addChild(m_manaAndHealth);

    Node* nextMember = GetAttributeNode(member, 0);
    nextMember->moveNode(0.0f, 210.0f);
    background->addChild(nextMember);


    ShowForEntity(member);
}

SceneManagerStatus::~SceneManagerStatus()
{
    //dtor
}

void SceneManagerStatus::Tick()
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

bool SceneManagerStatus::IsFinished()
{
    return m_finished;
}

bool SceneManagerStatus::IsTransparent()
{
    return true;
}

bool SceneManagerStatus::PausesSceneManagerBelow()
{
    return true;
}

void SceneManagerStatus::ShowForEntity(PartyMember* partyMember)
{
    m_name->SetText(partyMember->GetName());
    UpdateAttributeNode(partyMember, 0);
    m_manaAndHealth->SetEntity(partyMember);
    m_level->SetText(Localization::GetInstance()->GetLocalization("menu.status.level") + std::to_string(partyMember->GetLevel()));
    m_exp->setSize(sf::Vector2f(partyMember->GetExpPercent()* m_expWidth, m_expHeight));
}
