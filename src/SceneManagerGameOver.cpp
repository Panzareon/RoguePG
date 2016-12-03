#include "SceneManagerGameOver.h"
#include "TextureList.h"
#include "DrawableNode.h"
#include "Configuration.h"

SceneManagerGameOver::SceneManagerGameOver(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
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
    if (sf::Keyboard::isKeyPressed(Configuration::GetInstance()->GetKey(Configuration::Accept)))
    {
        m_finished = true;
    }
}

bool SceneManagerGameOver::IsFinished()
{
    return m_finished;
}
