#include "SceneManager/SceneManagerMessage.h"
#include "Controller/GameController.h"
#include "SceneGraph/DrawableNode.h"

SceneManagerMessage::SceneManagerMessage(std::string toDisplay)
{
    //ctor
    m_text = new TextNode(toDisplay);
    sf::FloatRect rect = m_text->getBoundingBox();
    int x = GameController::getInstance()->GetWindowWidth() - rect.width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - rect.height;
    y /= 2;

    m_background = new sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
    m_background->setFillColor(sf::Color::Black);

    m_backgroundNode = new DrawableNode(m_background);
    m_backgroundNode->moveNode(x,y);

    m_gui->addChild(m_backgroundNode);
    m_backgroundNode->addChild(m_text);

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
