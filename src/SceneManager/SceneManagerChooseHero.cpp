#include "SceneManagerChooseHero.h"
#include "SceneGraph/DrawableNode.h"
#include "Party/CharacterClass.h"
#include "Controller/Localization.h"
#include "Controller/GameController.h"

SceneManagerChooseHero::SceneManagerChooseHero()
{
    //ctor
    m_finished = false;

    m_selected = 0;
    m_textNode = new TextNode("");
    m_gui->addChild(m_textNode);
    m_textNode->moveNode(0.0f, 60.0f);
    TextNode* selectHero = new TextNode(Localization::GetInstance()->GetLocalization("menu.chooseHero"));
    m_gui->addChild(selectHero);
    m_classSprite = new sf::Sprite();
    DrawableNode* sprite = new DrawableNode(m_classSprite);
    sprite->moveNode(0.0f, selectHero->getBoundingBox().height + 5.0f);
    m_gui->addChild(sprite);
    ShowForCharacterClass();
}

SceneManagerChooseHero::~SceneManagerChooseHero()
{
    //dtor
}

void SceneManagerChooseHero::ShowForCharacterClass()
{
    CharacterClass* charClass = CharacterClass::GetCharacterClass((CharacterClass::CharacterClassEnum)m_selected);
    m_classSprite->setTexture(*TextureList::getTexture(charClass->GetClassSprite()));
    m_textNode->SetText(Localization::GetInstance()->GetLocalization(charClass->GetName()));
}

void SceneManagerChooseHero::Tick()
{
    GameController* controller = GameController::getInstance();
    if(controller->IsKeyPressed(Configuration::Accept))
    {
        PartyMember* p;
        p = CharacterClass::GetCharacterClass((CharacterClass::CharacterClassEnum)m_selected)->GetNewPartyMember();
        p->SetTeamId(0);
        controller->getParty()->AddPartyMember(p);
        m_finished = true;
    }
    else if(controller->IsKeyPressed(Configuration::MoveDown) || controller->IsKeyPressed(Configuration::MoveRight))
    {
        ChooseNext();
    }
    else if(controller->IsKeyPressed(Configuration::MoveUp) || controller->IsKeyPressed(Configuration::MoveLeft))
    {
        ChoosePrev();
    }
}

void SceneManagerChooseHero::ChooseNext()
{
    m_selected++;
    if(m_selected >= CharacterClass::CHARACTER_CLASS_END)
        m_selected = 0;
    ShowForCharacterClass();
}

void SceneManagerChooseHero::ChoosePrev()
{
    m_selected--;
    if(m_selected < 0)
        m_selected = CharacterClass::CHARACTER_CLASS_END - 1;
    ShowForCharacterClass();
}

bool SceneManagerChooseHero::IsFinished()
{
    return m_finished;
}

bool SceneManagerChooseHero::IsTransparent()
{
    return false;
}

bool SceneManagerChooseHero::PausesSceneManagerBelow()
{
    return true;
}
