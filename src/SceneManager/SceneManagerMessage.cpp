#include "SceneManager/SceneManagerMessage.h"
#include "Controller/GameController.h"
#include "SceneGraph/DrawableNode.h"

SceneManagerMessage::SceneManagerMessage(std::string toDisplay, float minDisplayTime)
{
    //ctor
    m_text = new TextNode(toDisplay);
    sf::FloatRect rect = m_text->getBoundingBox();
    int width = GameController::getInstance()->GetWindowWidth();
    m_text->SetMaxLength(width - 20);

    int x = width - rect.width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - rect.height;
    y /= 2;

    m_background = new sf::RectangleShape(sf::Vector2f(rect.width + 4.0f, rect.height + 10.0f));
    m_background->setFillColor(sf::Color::Black);
    m_background->setOutlineColor(sf::Color::White);
    m_background->setOutlineThickness(1.0f);

    m_backgroundNode = new DrawableNode(m_background);
    m_backgroundNode->moveNode(x - 2.0f ,y);
    m_text->moveNode(2.0f, 0.0f);

    m_gui->addChild(m_backgroundNode);
    m_backgroundNode->addChild(m_text);

    m_minDisplayTime = minDisplayTime;
    m_displayedTime = 0.0f;
    m_finished = false;
    m_menu = nullptr;
}

SceneManagerMessage::~SceneManagerMessage()
{
    //dtor
}

bool SceneManagerMessage::IsTransparent()
{
    return true;
}

bool SceneManagerMessage::PausesSceneManagerBelow()
{
    return true;
}

void SceneManagerMessage::Tick()
{
    if(m_menu != nullptr)
    {
        m_menu->CheckKeyboardInput();
        if(!m_menu->IsVisible())
        {
            m_finished = true;
        }
        return;
    }
    GameController* controller = GameController::getInstance();
    m_displayedTime += controller->GetTickTimeSeconds();

    //Show the Message at least for the given Time
    if(m_displayedTime < m_minDisplayTime)
    {
        return;
    }
    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel) || controller->IsKeyPressed(Configuration::Accept))
    {
        m_finished = true;
        if(m_onAccept != nullptr)
            m_onAccept();
    }
}

bool SceneManagerMessage::IsFinished()
{
    return m_finished;
}

void SceneManagerMessage::OnAccept(std::function<void()>func)
{
    m_onAccept = func;
}

void SceneManagerMessage::AddMenuNode(MenuNode* node)
{
    m_text->addChild(node);
    node->moveNode(0.0f, m_text->getBoundingBox().height);
    m_menu = node;
}
