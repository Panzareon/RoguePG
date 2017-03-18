#include "SceneManager/SceneManagerGameOver.h"
#include "SceneGraph/TextureList.h"
#include "SceneGraph/DrawableNode.h"
#include "Controller/Configuration.h"
#include "Controller/GameController.h"

SceneManagerGameOver::SceneManagerGameOver()
{
    //ctor
    m_finished = false;

    sf::Sprite* s = new sf::Sprite(*TextureList::getTexture(TextureList::GameOverScreen));
    DrawableNode* screen = new DrawableNode(s);
    m_gui->addChild(screen);
}

SceneManagerGameOver::~SceneManagerGameOver()
{
    //dtor
}

void SceneManagerGameOver::Tick()
{
    if (GameController::getInstance()->IsKeyPressed(Configuration::Accept))
    {
        m_finished = true;
    }
}

bool SceneManagerGameOver::IsFinished()
{
    return m_finished;
}
