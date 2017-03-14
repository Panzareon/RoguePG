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

    void SelectEquipmentSkills(SceneManagerGameMenu* sm, Equipment* item)
    {
        sm->SelectEquipmentSkills(true);
    }
    void DeselectEquipmentSkills(SceneManagerGameMenu* sm)
    {
        sm->SelectEquipmentSkills(false);
    }

    void SelectSkill(SceneManagerGameMenu* sm, Skill* skill)
    {
        sm->SelectSkill(skill);
    }

    void CloseEquipmentMenu(SceneManagerGameMenu* sm)
    {
        sm->CloseEquipment();
    }

    void Options();
}

SceneManagerGameMenu::SceneManagerGameMenu()
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
    m_equipmentSkills = nullptr;
    m_selectedMember = nullptr;
    m_equipmentDescription = nullptr;
    m_equipmentSkillsSelected = false;
    m_equipmentSkillBase = nullptr;

    //Set Menu function
    m_mainMenu = new MenuNode(background->getBoundingBox().width - 2* padding);
    Localization* local = Localization::GetInstance();
    m_mainMenu->AddOption(local->GetLocalization("menu.equipment"),std::function<void()>(std::bind(&MenuFunctions::OpenEquipment,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.option"),std::function<void()>(&MenuFunctions::Options),true);
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
    if(m_equipmentMenu != nullptr && m_equipmentMenu->IsVisible())
    {
        if(m_equipmentSkillsSelected)
            m_equipmentSkills->CheckKeyboardInput();
        else
            m_equipmentMenu->CheckKeyboardInput();
    }
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
    m_background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    m_background->moveNode(x,y);
    m_gui->addChild(m_background);
    //Hero Selection
    m_equipmentMenu = new MenuNode(HeroSelectWidth);
    m_equipmentMenu->CancelAvailable(true);
    m_equipmentMenu->CallOnCancel( std::function<void()>(std::bind(&MenuFunctions::CloseEquipmentMenu,this)));
    m_equipmentMenu->NextAvailable(true);
    Party* party = GameController::getInstance()->getParty();
    std::vector<PartyMember*>* member = party->GetAllPartyMembers();
    m_attributeNodes.resize(member->size());
    for(int i = 0; i < member->size(); i++)
    {
        m_equipmentMenu->AddOption(member->at(i)->GetName(), std::function<void()>(std::bind(&MenuFunctions::SelectMember,this,member->at(i))));
        Node* nextMember = new Node();
        m_equipmentMenu->AddNodeToOption(i, nextMember);
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
    m_background->addChild(m_equipmentMenu);

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

void SceneManagerGameMenu::CloseEquipment()
{
    m_background->setVisibility(false);
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
    m_equipmentItems->NextAvailable(true);
    m_equipmentItems->CallOnNext(std::function<void(Equipment*)>(std::bind(&MenuFunctions::SelectEquipmentSkills,this,std::placeholders::_1)));
    m_equipmentItems->PreviousAvailable(true);
    //Set Menu looks
    m_equipmentItems->SetMaxShownOptions(9);
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
    if(m_equipmentDescription != nullptr)
    {
        m_equipmentDescription->setVisibility(true);
    }
    else
    {
        m_equipmentDescription = new TextNode();
        m_equipmentDescription->SetColor(sf::Color::Black);
        m_gui->addChild(m_equipmentDescription);
        m_equipmentDescription->moveNode(5, 356);
        m_equipmentDescription->SetFontSize(15);
    }

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
                    SetEquipmentSkillMenu(equip);
                    m_selectedEquipment = equip;
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
    m_selectedEquipment = equipment;
    //For now only Weapons
    if(equipment != nullptr)
    {
        SetEquipmentSkillMenu(equipment);
        if(!equipment->IsEquiped())
        {
            m_selectedMember->SetEquipment(Equipment::MainHand, equipment);
            UpdateMemberStats();
        }
        m_equipmentDescription->SetText( Localization::GetInstance()->GetLocalization(equipment->GetDescription()));
    }
    else
    {
        m_selectedMember->SetEquipment(Equipment::MainHand, equipment);
        if(m_equipmentSkills != nullptr)
        {
            m_equipmentSkills->setVisibility(false);
        }
    }
}

void SceneManagerGameMenu::Equip(Equipment* equipment)
{
    SelectEquipment(equipment);
    m_equipmentItems->setVisibility(false);
    m_equipmentDescription->setVisibility(false);
    m_selectedMember = nullptr;
    RemoveEquipmentSkillMenu();
    UpdateMemberStats();
}

void SceneManagerGameMenu::SelectEquipmentSkills(bool selected)
{
    m_equipmentSkillsSelected = selected;
    m_equipmentSkills->ShowSelected(selected);
    //Still show the menu even if it is not selected
    m_equipmentSkills->setVisibility(true);
    if(selected)
    {
        m_equipmentDescription->SetText(m_selectedEquipment->GetSkillsToLearn()->begin()->second->GetLocalizedDescription());
    }
    else
    {
        m_equipmentDescription->SetText( Localization::GetInstance()->GetLocalization(m_selectedEquipment->GetDescription()));
    }
}

void SceneManagerGameMenu::SelectSkill(Skill* skill)
{
    m_equipmentDescription->SetText(skill->GetLocalizedDescription());
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

void SceneManagerGameMenu::RemoveEquipmentSkillMenu()
{
    if(m_equipmentSkillBase != nullptr)
    {
        m_equipmentSkillBase->setVisibility(false);
    }
}

void SceneManagerGameMenu::SetEquipmentSkillMenu(Equipment* equipment)
{
    int height = 45;
    int width = 150;
    if(m_equipmentSkills != nullptr)
    {
        m_equipmentSkills->ResetOptions();
        m_equipmentSkillBase->setVisibility(true);
    }
    else
    {
        int fontSize = 15;
        m_equipmentSkillBase = new Node();
        m_equipmentSkillBase->moveNode(485,4);
        m_background->addChild(m_equipmentSkillBase);

        //Set learning displays
        m_equipmentSkillLearned = new sf::RectangleShape();
        m_equipmentSkillLearned->setFillColor(sf::Color::Green);
        DrawableNode* learned = new DrawableNode(m_equipmentSkillLearned);
        m_equipmentSkillBase->addChild(learned);
        m_equipmentSkillLearning = new sf::RectangleShape();
        m_equipmentSkillLearning->setFillColor(sf::Color::Red);
        m_equipmentSkillLearningNode = new DrawableNode(m_equipmentSkillLearning);
        m_equipmentSkillBase->addChild(m_equipmentSkillLearningNode);


        m_equipmentSkills = new MenuNodeItems<Skill>(width, std::function<void(Skill*)>(std::bind(&MenuFunctions::SelectSkill,this,std::placeholders::_1)));
        m_equipmentSkillBase->addChild(m_equipmentSkills);
        m_equipmentSkills->PreviousAvailable(true);
        m_equipmentSkills->CallOnCancel(std::function<void()>(std::bind(&MenuFunctions::DeselectEquipmentSkills,this)));
        m_equipmentSkills->CancelAvailable(true);

        //Set Menu looks
        m_equipmentSkills->SetMaxShownOptions(9);
        m_equipmentSkills->SetPadding(2,0);
        m_equipmentSkills->SetBackgroundColor(sf::Color::Transparent);
        m_equipmentSkills->SetForegroundColorDisabled(sf::Color::Black);
        m_equipmentSkills->SetForegroundColor(sf::Color::Black);
        m_equipmentSkills->SetOutlineColor(sf::Color::Transparent);
        m_equipmentSkills->SetSelectedColor(sf::Color::Blue);
        m_equipmentSkills->SetFontSize(fontSize);
        m_equipmentSkills->SetSpacing(height - fontSize);
        m_equipmentSkills->ShowSelected(false);


    }
    Localization* localization = Localization::GetInstance();
    std::map<int, std::shared_ptr<Skill>>* skills = equipment->GetSkillsToLearn();
    int optionNr = 0;
    for(auto it = skills->begin(); it != skills->end(); it++)
    {
        m_equipmentSkills->AddOptionWithItem(localization->GetLocalization(it->second->GetName()), nullptr, it->second.get(), false);
        m_equipmentSkills->AddValueToOption(optionNr++, std::to_string((int)it->second->GetManaUse()));
    }
    //Display how far learned
    int learnedHeight = equipment->GetLevel(m_selectedMember) - 1;
    bool showLearning = learnedHeight < skills->size();
    if(skills->size() < learnedHeight)
    {
        learnedHeight = skills->size();
    }
    learnedHeight *= height;
    m_equipmentSkillLearned->setSize(sf::Vector2f(width,learnedHeight));
    if(showLearning)
    {
        m_equipmentSkillLearningNode->setVisibility(true);
        m_equipmentSkillLearning->setPosition(sf::Vector2f(0, learnedHeight));
        int learningWidth = equipment->GetEquipmentExpPercent(m_selectedMember) * width;
        m_equipmentSkillLearning->setSize(sf::Vector2f(learningWidth, height));
    }
    else
    {
        m_equipmentSkillLearningNode->setVisibility(false);
    }
}

