#include "SceneManager/SceneManagerEquipment.h"
#include "SceneGraph/TextureList.h"
#include "SceneGraph/DrawableNode.h"
#include "Controller/GameController.h"
#include "Controller/Localization.h"
#include "SceneGraph/MenuNodeItems.h"


namespace MenuFunctions
{

    void SelectMember(SceneManagerEquipment* sm, PartyMember* member)
    {
        sm->SelectMember(member);
    }

    void SelectEquipment(SceneManagerEquipment* sm, std::shared_ptr<Equipment> item)
    {
        sm->SelectEquipment(item);
    }

    void Equip(SceneManagerEquipment* sm, std::shared_ptr<Equipment> item)
    {
        sm->Equip(item);
    }

    void SelectEquipmentSkills(SceneManagerEquipment* sm, std::shared_ptr<Equipment> item)
    {
        sm->SelectEquipmentSkills(true);
    }
    void DeselectEquipmentSkills(SceneManagerEquipment* sm)
    {
        sm->SelectEquipmentSkills(false);
    }

    void SelectSkill(SceneManagerEquipment* sm, Skill* skill)
    {
        sm->SelectSkill(skill);
    }

    void MoveEquipment(SceneManagerEquipment* sm, int id, int newPosition)
    {
        sm->MoveItemPosition(id, newPosition);
    }
}

SceneManagerEquipment::SceneManagerEquipment()
{
    //ctor

    m_equipmentItems = nullptr;
    m_equipmentSkills = nullptr;
    m_selectedMember = nullptr;
    m_equipmentDescription = nullptr;
    m_equipmentSkillsSelected = false;
    m_equipmentSkillBase = nullptr;


    int HeroSelectWidth = 314;
    int MemberHeight = 104;
    int padding = 3;
    m_maxShownHeroes = 3;
    m_finished = false;

    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::EquipmentMenu));
    m_background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    m_background->moveNode(x,y);
    m_gui->addChild(m_background);
    //Hero Selection
    m_mainMenu = new MenuNode(HeroSelectWidth);
    m_mainMenu->NextAvailable(true);
    Party* party = GameController::getInstance()->getParty();
    std::vector<std::shared_ptr<PartyMember> >* member = party->GetAllPartyMembers();
    for(int i = 0; i < member->size(); i++)
    {
        m_mainMenu->AddOption(member->at(i)->GetName(), std::function<void()>(std::bind(&MenuFunctions::SelectMember,this,member->at(i).get())));
        Node* nextMember = GetAttributeNode(member->at(i).get(), i);
        m_mainMenu->AddNodeToOption(i, nextMember);
        member->at(i)->SaveBeforeEquipping();
    }
    m_background->addChild(m_mainMenu);

    //Set Menu looks
    m_mainMenu->SetMaxShownOptions(m_maxShownHeroes);
    m_mainMenu->moveNode(3,3);
    m_mainMenu->SetPadding(padding,padding);
    m_mainMenu->SetBackgroundColor(sf::Color::Transparent);
    m_mainMenu->SetForegroundColor(sf::Color::Black);
    m_mainMenu->SetOutlineColor(sf::Color::Transparent);
    m_mainMenu->SetSelectedTexture(TextureList::getTexture(TextureList::EquipmentSelected));
    m_mainMenu->SetFontSize(30);
    m_mainMenu->SetSpacing(74);
    m_mainMenu->SetVisibleWithSubmenu(true);
}

SceneManagerEquipment::~SceneManagerEquipment()
{
    //dtor
    ReSelectEquipment();
}

void SceneManagerEquipment::Tick()
{
    GameController* controller = GameController::getInstance();
    if(m_equipmentSkillsSelected)
        m_equipmentSkills->CheckKeyboardInput();
    else
        m_mainMenu->CheckKeyboardInput();
    //Check menu Key
    if(controller->IsKeyPressed(Configuration::Cancel))
    {
        //Close Menu
        m_finished = true;
    }
}

bool SceneManagerEquipment::IsFinished()
{
    return m_finished;
}

bool SceneManagerEquipment::IsTransparent()
{
    return true;
}

bool SceneManagerEquipment::PausesSceneManagerBelow()
{
    return true;
}


void SceneManagerEquipment::SelectMember(PartyMember* member)
{
    Party* party = GameController::getInstance()->getParty();
    m_selectedMember = party->GetSharedPointerOf(member);
    //Show Equipment Menu for this member
    m_equipmentItems = new MenuNodeItems<std::shared_ptr<Equipment>>(150, std::function<void(std::shared_ptr<Equipment>)>(std::bind(&MenuFunctions::SelectEquipment,this,std::placeholders::_1)));
    m_mainMenu->addChild(m_equipmentItems);
    m_equipmentItems->CancelAvailable(true);
    m_equipmentItems->NextAvailable(true);
    m_equipmentItems->CallOnNext(std::function<void(std::shared_ptr<Equipment>)>(std::bind(&MenuFunctions::SelectEquipmentSkills,this,std::placeholders::_1)));
    m_equipmentItems->EnableSorting(std::function<void(int,int)>(std::bind(&MenuFunctions::MoveEquipment,this, std::placeholders::_1,std::placeholders::_2)));
    m_equipmentItems->PreviousAvailable(true);
    //Set Menu looks
    m_equipmentItems->SetMaxShownOptions(12);
    m_equipmentItems->moveNode(322,1);
    m_equipmentItems->SetBackgroundColor(sf::Color::Transparent);
    m_equipmentItems->SetForegroundColor(sf::Color::Black);
    m_equipmentItems->SetOutlineColor(sf::Color::Transparent);
    m_equipmentItems->SetSelectedColor(sf::Color::Blue);
    m_equipmentItems->SetFontSize(20);
    m_equipmentItems->SetSpacing(5);
    //For now only Weapons
    m_pos = Equipment::MainHand;
    std::shared_ptr<Equipment> equip;
    m_equipmentItems->CallOnCancel(std::function<void()>(std::bind(&MenuFunctions::Equip,this,member->GetEquipment(m_pos))));
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
        m_equipmentDescription->SetMaxLength(630);
    }

    //Get stats of member now
    for(int i = 0; i < (int)BattleEnums::Attribute::COUNT; i++)
    {
        m_memberStats[(BattleEnums::Attribute)i] = member->GetAttribute((BattleEnums::Attribute)i);
    }

    bool first = true;

    for(auto item = party->GetItems()->begin(); item != party->GetItems()->end(); item++)
    {
        //Check if this Item can be Equipped
        if((*item).second->GetItemType() == Item::ItemTypeEquipment)
        {
            equip = std::static_pointer_cast<Equipment>((*item).second);
            if(equip->GetEquipmentPosition() == m_pos)
            {
                //Add Item to Menu
                m_equipmentItems->AddOptionWithItem(loc->GetLocalization(equip->GetName()), std::function<void()>(std::bind(&MenuFunctions::Equip,this,equip)), equip, true);

                if(first)
                {
                    //Equip first available Item if not equipped otherwise
                    SetEquipmentSkillMenu(equip);
                    m_selectedEquipment = equip;
                    if(!equip->IsEquipped())
                        SelectEquipment(equip);
                    first = false;
                }

            }
        }
    }
}

void SceneManagerEquipment::SelectEquipment(std::shared_ptr<Equipment> equipment)
{
    m_selectedEquipment = equipment;
    //For now only Weapons
    if(equipment != nullptr)
    {
        SetEquipmentSkillMenu(equipment);
        if(equipment->IsEquipped())
        {
            std::shared_ptr<PartyMember> lastEquiped = equipment->GetEquipTarget();
            lastEquiped->SetEquipment(Equipment::MainHand, nullptr);
        }
        m_selectedMember->SetEquipment(Equipment::MainHand, equipment);
        UpdateMemberStats(true);

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

void SceneManagerEquipment::Equip(std::shared_ptr<Equipment> equipment)
{
    SelectEquipment(equipment);
    m_equipmentItems->setVisibility(false);
    m_equipmentDescription->setVisibility(false);
    m_selectedMember = nullptr;
    RemoveEquipmentSkillMenu();
    ReSelectEquipment();
    UpdateMemberStats();
}

void SceneManagerEquipment::SelectEquipmentSkills(bool selected)
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

void SceneManagerEquipment::SelectSkill(Skill* skill)
{
    m_equipmentDescription->SetText(skill->GetLocalizedDescription());
}

void SceneManagerEquipment::MoveItemPosition(int from, int to)
{
    std::vector<std::pair<int,std::shared_ptr<Item>>>::iterator fromIt;
    std::vector<std::pair<int,std::shared_ptr<Item>>>::iterator toIt;
    int equipmentId = 0;
    std::shared_ptr<Equipment> equip;
    Party* party = GameController::getInstance()->getParty();
    for(auto item = party->GetItems()->begin(); item != party->GetItems()->end(); item++)
    {
        //Check if this Item can be Equipped
        if((*item).second->GetItemType() == Item::ItemTypeEquipment)
        {
            equip = std::static_pointer_cast<Equipment>((*item).second);
            if(equip->GetEquipmentPosition() == m_pos)
            {
                if(equipmentId == from)
                {
                    fromIt = item;
                }
                if(equipmentId == to)
                {
                    toIt = item;
                }
                equipmentId++;
            }
        }
    }

    std::pair<int,std::shared_ptr<Item>> temp = *fromIt;
    party->GetItems()->erase(fromIt);
    party->GetItems()->insert(toIt, temp);
}

void SceneManagerEquipment::UpdateMemberStats(bool selectedOnly)
{
    Party* party = GameController::getInstance()->getParty();
    std::vector<std::shared_ptr<PartyMember> >* member = party->GetAllPartyMembers();
    int scrollPosition = m_mainMenu->GetScrollPosition();
    PartyMember* mem;
    for(int i = scrollPosition; i < member->size() && i < scrollPosition + m_maxShownHeroes; i++)
    {
        if(!selectedOnly || member->at(i) == m_selectedMember)
        {
            mem = member->at(i).get();
            UpdateAttributeNode(mem, i);
            for(int j = 0; j < (int)BattleEnums::Attribute::COUNT; j++)
            {
                int attributeValue = mem->GetAttribute((BattleEnums::Attribute)j);
                if(mem == m_selectedMember.get() && attributeValue > m_memberStats[(BattleEnums::Attribute)j])
                {
                    m_attributeNodes[i][(BattleEnums::Attribute)j]->SetColor(sf::Color::Green);
                }
                else if(mem == m_selectedMember.get() && attributeValue < m_memberStats[(BattleEnums::Attribute)j])
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
}

void SceneManagerEquipment::RemoveEquipmentSkillMenu()
{
    if(m_equipmentSkillBase != nullptr)
    {
        m_equipmentSkillBase->setVisibility(false);
    }
}

void SceneManagerEquipment::SetEquipmentSkillMenu(std::shared_ptr<Equipment> equipment)
{
    int height = 25;
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


        m_equipmentSkills = new MenuNodeItems<Skill*>(width, std::function<void(Skill*)>(std::bind(&MenuFunctions::SelectSkill,this,std::placeholders::_1)));
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

void SceneManagerEquipment::ReSelectEquipment()
{
    std::vector<std::shared_ptr<PartyMember> >* member = GameController::getInstance()->getParty()->GetAllPartyMembers();
    for(int i = 0; i < member->size(); i++)
    {
        member->at(i)->ResetAfterEquipping();
    }
}
