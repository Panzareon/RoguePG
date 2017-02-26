#include "SceneManagerGameMenu.h"
#include "TextureList.h"
#include "DrawableNode.h"
#include "GameController.h"
#include "Localization.h"
#include "MenuNodeItems.h"

#include <iostream>

namespace MenuFunctions
{
    void OpenEquipment(SceneManagerGameMenu* sm)
    {
        sm->OpenEquipment();
    }
    void Quit(SceneManagerGameMenu* sm)
    {
        sm->Quit();
    }

    void SelectMember(SceneManagerGameMenu* sm, PartyMember* member)
    {
        sm->SelectMember(member);
    }

    void SelectEquipment(SceneManagerGameMenu* sm, Equipment* item)
    {
        sm->SelectEquipment(static_cast<Equipment*>(item));
    }

    void Equip(SceneManagerGameMenu* sm, Equipment* item)
    {
        sm->Equip(static_cast<Equipment*>(item));
    }
}

SceneManagerGameMenu::SceneManagerGameMenu(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
{
    //ctor
    int padding = 8;
    m_maxShownHeroes = 3;
    m_attributeNodePosition[BattleEnums::AttributeMaxHp] = std::pair<int,int>(25,40);
    m_attributeNodePosition[BattleEnums::AttributeStrength] = std::pair<int,int>(110,40);
    m_attributeNodePosition[BattleEnums::AttributeInt] = std::pair<int,int>(190,40);
    m_attributeNodePosition[BattleEnums::AttributeSpeed] = std::pair<int,int>(263,40);
    m_attributeNodePosition[BattleEnums::AttributeMaxMp] = std::pair<int,int>(25,75);
    m_attributeNodePosition[BattleEnums::AttributeDefense] = std::pair<int,int>(110,75);
    m_attributeNodePosition[BattleEnums::AttributeMagicDefense] = std::pair<int,int>(190,75);



    //Set Background
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::InGameMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);

    m_equipmentMenu = nullptr;
    m_equipmentItems = nullptr;
    m_selectedMember = nullptr;

    //Set Menu function
    m_mainMenu = new MenuNode(background->getBoundingBox().width - 2* padding);
    Localization* local = Localization::GetInstance();
    m_mainMenu->AddOption(local->GetLocalization("menu.equipment"),std::function<void()>(std::bind(&MenuFunctions::OpenEquipment,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.quit"),std::function<void()>(std::bind(&MenuFunctions::Quit,this)),true);
    background->addChild(m_mainMenu);

    //Set Menu looks
    m_mainMenu->SetPadding(padding,padding);
    m_mainMenu->SetBackgroundColor(sf::Color::Transparent);
    m_mainMenu->SetForegroundColor(sf::Color::Black);
    m_mainMenu->SetOutlineColor(sf::Color::Transparent);
    m_mainMenu->SetSelectedTexture(TextureList::getTexture(TextureList::InGameMenuSelected));
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
    if(m_equipmentMenu != nullptr)
        m_equipmentMenu->CheckKeyboardInput();
    else
        m_mainMenu->CheckKeyboardInput();
    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel))
    {
        //Close Menu
        m_finished = true;
    }
}


void SceneManagerGameMenu::OpenEquipment()
{
    int HeroSelectWidth = 314;
    int MemberHeight = 104;
    int padding = 3;

    std::cout << "Equipment" << std::endl;
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::EquipmentMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);
    //Hero Selection
    m_equipmentMenu = new MenuNode(HeroSelectWidth);
    m_equipmentMenu->CancelAvailable(true);
    Party* party = GameController::getInstance()->getParty();
    std::vector<PartyMember*>* member = party->GetAllPartyMembers();
    m_attributeNodes.resize(m_maxShownHeroes);
    for(int i = 0; i < member->size(); i++)
    {
        m_equipmentMenu->AddOption(member->at(i)->GetName(), std::function<void()>(std::bind(&MenuFunctions::SelectMember,this,member->at(i))));
        if(i < m_maxShownHeroes)
        {
            Node* nextMember = new Node();
            nextMember->moveNode(0,MemberHeight*i);
            background->addChild(nextMember);
            for(int j = 0; j < BattleEnums::ATTRIBUTE_END; j++)
            {
                TextNode* node = new TextNode(std::to_string(member->at(i)->GetAttribute((BattleEnums::Attribute)j)));
                node->SetColor(sf::Color::Black);
                node->SetFontSize(25);
                m_attributeNodes[i][(BattleEnums::Attribute)j] = node;
                nextMember->addChild(node);
                std::pair<int,int> pos = m_attributeNodePosition[(BattleEnums::Attribute)j];
                node->moveNode(pos.first,pos.second);
            }
        }
    }
    background->addChild(m_equipmentMenu);

    //Set Menu looks
    m_equipmentMenu->SetMaxShownOptions(m_maxShownHeroes);
    m_equipmentMenu->moveNode(3,3);
    m_equipmentMenu->SetPadding(padding,padding);
    m_equipmentMenu->SetBackgroundColor(sf::Color::Transparent);
    m_equipmentMenu->SetForegroundColor(sf::Color::Black);
    m_equipmentMenu->SetOutlineColor(sf::Color::Transparent);
    m_equipmentMenu->SetSelectedTexture(TextureList::getTexture(TextureList::EquipmentSelected));
    m_equipmentMenu->SetFontSize(30);
    m_equipmentMenu->SetSpacing(74);
}

void SceneManagerGameMenu::Quit()
{
    //Quit to Main menu
    GameController::getInstance()->QuitToMainMenu();
}

void SceneManagerGameMenu::SelectMember(PartyMember* member)
{
    Party* party = GameController::getInstance()->getParty();
    m_selectedMember = member;
    //Show Equipment Menu for this member
    m_equipmentItems = new MenuNodeItems<Equipment>(150, std::function<void(Equipment*)>(std::bind(&MenuFunctions::SelectEquipment,this,std::placeholders::_1)));
    m_equipmentMenu->addChild(m_equipmentItems);
    m_equipmentItems->CancelAvailable(true);
    //Set Menu looks
    m_equipmentItems->SetMaxShownOptions(m_maxShownHeroes);
    m_equipmentItems->moveNode(322,1);
    m_equipmentItems->SetBackgroundColor(sf::Color::Transparent);
    m_equipmentItems->SetForegroundColor(sf::Color::Black);
    m_equipmentItems->SetOutlineColor(sf::Color::Transparent);
    m_equipmentItems->SetSelectedColor(sf::Color::Blue);
    m_equipmentItems->SetFontSize(30);
    m_equipmentItems->SetSpacing(5);
    //For now only Weapons
    Equipment::EquipmentPosition pos = Equipment::MainHand;
    Equipment* equip;
    m_equipmentItems->CallOnCancel(std::function<void()>(std::bind(&MenuFunctions::Equip,this,member->GetEquipment(pos))));
    Localization* loc = Localization::GetInstance();

    //Node for Equipment Description
    m_equipmentDescription = new TextNode();
    m_equipmentDescription->SetColor(sf::Color::Black);
    m_gui->addChild(m_equipmentDescription);
    m_equipmentDescription->moveNode(5, 353);

    //Get stats of member now
    for(int i = 0; i < BattleEnums::ATTRIBUTE_END; i++)
    {
        m_memberStats[(BattleEnums::Attribute)i] = member->GetAttribute((BattleEnums::Attribute)i);
    }

    bool first = true;

    for(auto item = party->GetItems()->begin(); item != party->GetItems()->end(); item++)
    {
        //Check if this Item can be Equipped
        if((*item).second->GetItemType() == Item::ItemTypeEquipment)
        {
            equip = (Equipment*)((*item).second);
            if(equip->GetEquipmentPosition() == pos)
            {
                //Add Item to Menu
                m_equipmentItems->AddOptionWithItem(loc->GetLocalization(equip->GetName()), std::function<void()>(std::bind(&MenuFunctions::Equip,this,equip)), equip, !equip->IsEquiped());

                if(first)
                {
                    //Equip first available Item if not equipped otherwise
                    if(!equip->IsEquiped())
                        SelectEquipment(equip);
                    first = false;
                }

            }
        }
    }
}

void SceneManagerGameMenu::SelectEquipment(Equipment* equipment)
{
    //For now only Weapons
    if(equipment != nullptr && !equipment->IsEquiped())
    {
        m_selectedMember->SetEquipment(Equipment::MainHand, equipment);
        UpdateMemberStats();
    }
    m_equipmentDescription->SetText( Localization::GetInstance()->GetLocalization(equipment->GetDescription()));
}

void SceneManagerGameMenu::Equip(Equipment* equipment)
{
    SelectEquipment(equipment);
    m_equipmentItems->setVisibility(false);
    m_selectedMember = nullptr;
    UpdateMemberStats();
}

void SceneManagerGameMenu::UpdateMemberStats()
{
    Party* party = GameController::getInstance()->getParty();
    std::vector<PartyMember*>* member = party->GetAllPartyMembers();
    int scrollPosition = m_equipmentMenu->GetScrollPosition();
    PartyMember* mem;
    for(int i = scrollPosition; i < member->size() && i < scrollPosition + m_maxShownHeroes; i++)
    {
        mem = member->at(i);
        for(int j = 0; j < BattleEnums::ATTRIBUTE_END; j++)
        {
            int attributeValue = mem->GetAttribute((BattleEnums::Attribute)j);
            m_attributeNodes[i][(BattleEnums::Attribute)j]->SetText(std::to_string(attributeValue));
            if(mem == m_selectedMember && attributeValue > m_memberStats[(BattleEnums::Attribute)j])
            {
                m_attributeNodes[i][(BattleEnums::Attribute)j]->SetColor(sf::Color::Green);
            }
            else if(mem == m_selectedMember && attributeValue < m_memberStats[(BattleEnums::Attribute)j])
            {
                m_attributeNodes[i][(BattleEnums::Attribute)j]->SetColor(sf::Color::Red);
            }
            else
            {
                m_attributeNodes[i][(BattleEnums::Attribute)j]->SetColor(sf::Color::Black);
            }
        }
    }
}
