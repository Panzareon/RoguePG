#include "SceneManagerGameMenu.h"
#include "TextureList.h"
#include "DrawableNode.h"
#include "GameController.h"

SceneManagerGameMenu::SceneManagerGameMenu(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
{
    //ctor
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::InGameMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    m_gui->addChild(background);
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
    //TODO: Check Menu inputs
    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel))
    {
        //Close Menu
        m_finished = true;
    }
}
