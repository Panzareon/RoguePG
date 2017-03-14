#include "SceneManagerMessage.h"
#include "GameController.h"

SceneManagerMessage::SceneManagerMessage(std::string toDisplay)
{
    //ctor
    m_text = new TextNode(toDisplay);
    m_gui->addChild(m_text);
    sf::FloatRect rect = m_text->getBoundingBox();
    int x = GameController::getInstance()->GetWindowWidth() - rect.width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - rect.height;
    y /= 2;
    m_text->moveNode(x,y);
    m_finished = false;
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

