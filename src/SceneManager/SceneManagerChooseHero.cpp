#include "SceneManager/SceneManagerChooseHero.h"
#include "SceneGraph/DrawableNode.h"
#include "Party/CharacterClass.h"
#include "Controller/Localization.h"
#include "Controller/GameController.h"
#include "Party/ItemFactory.h"
#include "SceneManager/SceneManagerVillage.h"

SceneManagerChooseHero::SceneManagerChooseHero()
{
    GameController* controller = GameController::getInstance();
    //ctor
    m_finished = false;

    m_selected = 0;
    m_textNode = new TextNode("");
    m_gui->addChild(m_textNode);
    TextNode* selectHero = new TextNode(Localization::GetInstance()->GetLocalization("menu.chooseHero"));
    m_gui->addChild(selectHero);
    selectHero->moveNode(40.0f, 0.0f);

    PersistentProgress* progress = controller->GetPersistentProgress();

    int xPos = 50;
    int yPos = selectHero->getBoundingBox().height + 50.0f;
    for(int i = 0; i < (int)CharacterClass::CharacterClassEnum::COUNT; i++)
    {
        CharacterClass::CharacterClassEnum classEnum = (CharacterClass::CharacterClassEnum)i;
        bool available = progress->IsClassUnlocked(classEnum);
        m_classAvailable[classEnum] = available;

        CharacterClass* charClass = CharacterClass::GetCharacterClass(classEnum);

        sf::Sprite* classSprite = new sf::Sprite();
        if(available)
        {
            classSprite->setTexture(*TextureList::getTexture(charClass->GetClassSprite()));
        }
        else
        {
            classSprite->setTexture(*TextureList::getTexture(TextureList::TextureFiles::LockedCharacter));
        }
        DrawableNode* sprite = new DrawableNode(classSprite);
        sprite->setBoundingBox(classSprite->getLocalBounds());
        m_classNodes.push_back(sprite);
        sprite->moveNode(xPos, yPos);
        xPos += (int)classSprite->getLocalBounds().width + 30;
        m_gui->addChild(sprite);
    }

    sf::Sprite* targetSprite = new sf::Sprite(*TextureList::getTexture(TextureList::TextureFiles::TargetCursor));
    m_cursor = new DrawableNode(targetSprite);
    m_cursor->setBoundingBox(targetSprite->getLocalBounds());
    m_gui->addChild(m_cursor);


    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::TextureFiles::DescriptionBox));
    Node* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    background->moveNode(x,y);
    m_gui->addChild(background);



    m_description = new TextNode();
    m_description->SetColor(sf::Color::Black);
    background->addChild(m_description);
    m_description->moveNode(5, 5);
    m_description->SetFontSize(15);
    m_description->SetMaxLength(630);

    ShowForCharacterClass();
}

SceneManagerChooseHero::~SceneManagerChooseHero()
{
    //dtor
}

void SceneManagerChooseHero::ShowForCharacterClass()
{
    CharacterClass* charClass = CharacterClass::GetCharacterClass((CharacterClass::CharacterClassEnum)m_selected);
    if(m_classAvailable[(CharacterClass::CharacterClassEnum)m_selected])
    {
        m_textNode->SetText(Localization::GetInstance()->GetLocalization(charClass->GetName()));
    }
    else
    {
        m_textNode->SetText(Localization::GetInstance()->GetLocalization("character_class.locked"));
    }
    m_description->SetText(Localization::GetInstance()->GetLocalization(charClass->GetName() + ".desc"));

    sf::FloatRect selectedNode = m_classNodes[m_selected]->getGlobalBoundingBox();
    int xMid = selectedNode.left + selectedNode.width/2;
    sf::FloatRect cursorBounds = m_cursor->getBoundingBox();
    m_cursor->setPosition(xMid - cursorBounds.width / 2, selectedNode.top - cursorBounds.height);
    sf::FloatRect textBounds = m_textNode->getBoundingBox();
    m_textNode->setPosition(xMid - textBounds.width / 2, selectedNode.top + 40);
}

void SceneManagerChooseHero::Tick()
{
    GameController* controller = GameController::getInstance();
    if(controller->IsKeyPressed(Configuration::Accept) && m_classAvailable[(CharacterClass::CharacterClassEnum)m_selected])
    {
        StartDungeon();
    }
    else if(controller->IsKeyPressed(Configuration::MoveRight))
    {
        ChooseNext();
    }
    else if(controller->IsKeyPressed(Configuration::MoveLeft))
    {
        ChoosePrev();
    }
    else if(controller->IsKeyPressed(Configuration::Cancel))
    {
        m_finished = true;
    }
}

void SceneManagerChooseHero::StartDungeon()
{
    GameController* controller = GameController::getInstance();
    Party* party = controller->getParty();

    PartyMember* p;
    p = CharacterClass::GetCharacterClass((CharacterClass::CharacterClassEnum)m_selected)->GetNewPartyMember();
    p->SetTeamId(0);
    party->AddPartyMember(p);
    m_finished = true;



    PersistentProgress* progress = controller->GetPersistentProgress();
    party->AddMoney(progress->GetStartMoney());
    //create new party with x member
    int partyInitialSize = progress->GetStartMember();
    for(int i = 1; i < partyInitialSize; i++)
    {
        party->AddRandomMember();
    }

    std::vector<std::shared_ptr<PartyMember> > * partyMember = party->GetActivePartyMembers();
    ItemFactory* itemFactory = ItemFactory::GetInstance();
    for(int i = 0; i < 3; i++)
    {
        Equipment* equipment = (Equipment*)itemFactory->GetRandomEquipment(Equipment::EquipmentPosition::MainHand, ItemFactory::StartingItem);
        std::shared_ptr<Item> item = party->AddItem(equipment);
        if(partyMember->size() > i)
        {
            std::shared_ptr<PartyMember> member = partyMember->at(i);
            member->SetEquipment(Equipment::EquipmentPosition::MainHand, std::static_pointer_cast<Equipment>(item));
            member->Heal(member->GetAttribute(BattleEnums::Attribute::MaxHp));
        }

    }

    controller->LoadSceneManagerBefore(std::shared_ptr<SceneManager>(new SceneManagerVillage(30,20,time(NULL),new MapFillVillage())), this);
}

void SceneManagerChooseHero::ChooseNext()
{
    m_selected++;
    if(m_selected >= (int)CharacterClass::CharacterClassEnum::COUNT)
        m_selected = 0;
    ShowForCharacterClass();
}

void SceneManagerChooseHero::ChoosePrev()
{
    m_selected--;
    if(m_selected < 0)
        m_selected = (int)CharacterClass::CharacterClassEnum::COUNT - 1;
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
