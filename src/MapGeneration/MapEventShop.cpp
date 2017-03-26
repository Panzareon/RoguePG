#include "MapGeneration/MapEventShop.h"
#include "Party/ItemFactory.h"
#include "Controller/GameController.h"
#include "SceneManager/SceneManagerMessage.h"
#include "Controller/Localization.h"

#include <iostream>

namespace MenuFunctions
{
    void BuyItem(MapEventShop* shop, Item* item)
    {
        shop->BuyItem(item);
    }
    void QuitShop(MapEventShop* shop)
    {
        shop->Quit();
    }
    void Heal(MapEventShop* shop)
    {
        shop->Sleep();
    }
}

MapEventShop::MapEventShop(int x, int y, ShopTypes type) : MapEventTile(true, x, y, false)
{
    //ctor
    m_type = type;
    m_innPrice = 10;
    Restock();
}

MapEventShop::~MapEventShop()
{
    //dtor
}

void MapEventShop::Restock()
{
    switch(m_type)
    {
    case SwordShop:
        m_sellItems.insert(std::pair<int, Item*>(100, ItemFactory::GetInstance()->GetEquipment(Equipment::MainHand, 101)));
        break;
    case ShieldShop:
        m_sellItems.insert(std::pair<int, Item*>(100, ItemFactory::GetInstance()->GetEquipment(Equipment::MainHand, 102)));
        break;
    case StaffShop:
        m_sellItems.insert(std::pair<int, Item*>(100, ItemFactory::GetInstance()->GetEquipment(Equipment::MainHand, 103)));
        break;
    case SpellShop:
        m_sellItems.insert(std::pair<int, Item*>(100, ItemFactory::GetInstance()->GetEquipment(Equipment::MainHand, 104)));
        break;
    }
}

void MapEventShop::Activate()
{
    if(m_type == Inn)
    {
        ShowInn();
    }
    else
    {
        ShowShop();
    }
}

void MapEventShop::ShowShop()
{
    Party* party = GameController::getInstance()->getParty();
    Localization* localization = Localization::GetInstance();
    SceneManagerMessage* sm;
    if(m_sellItems.size() > 0)
    {
        sm = new SceneManagerMessage(localization->GetLocalization("menu.shop.buy"));
        m_node = new MenuNode(300);
        m_node->CancelAvailable(true);
        int i = 0;
        for(auto it = m_sellItems.begin(); it != m_sellItems.end(); it++)
        {
            m_node->AddOption(localization->GetLocalization(it->second->GetName()),std::function<void()>(std::bind(MenuFunctions::BuyItem,this, it->second)), party->GetMoney() >= it->first);
            m_node->AddValueToOption(i, std::to_string(it->first));
            i++;
        }
        m_node->moveNode(0.0f, 5.0f);
        sm->AddMenuNode(m_node);
    }
    else
    {
        sm = new SceneManagerMessage(localization->GetLocalization("menu.shop.buy.nothing"));
    }

    GameController::getInstance()->LoadSceneManager(sm);
}

void MapEventShop::ShowInn()
{
    Party* party = GameController::getInstance()->getParty();
    Localization* localization = Localization::GetInstance();
    std::vector<float> neededMoney;
    neededMoney.push_back(m_innPrice);
    SceneManagerMessage* sm = new SceneManagerMessage(localization->GetLocalizationWithFloats("menu.shop.inn", &neededMoney));
    m_node = new MenuNode(300);
    m_node->CancelAvailable(true);
    m_node->AddOption(localization->GetLocalization("menu.yes"),std::function<void()>(std::bind(MenuFunctions::Heal,this)), party->GetMoney() >= m_innPrice);
    m_node->AddOption(localization->GetLocalization("menu.no"),std::function<void()>(std::bind(MenuFunctions::QuitShop, this)));

    m_node->moveNode(0.0f, 5.0f);
    sm->AddMenuNode(m_node);

    GameController::getInstance()->LoadSceneManager(sm);
}

void MapEventShop::BuyItem(Item* item)
{
    for(auto it = m_sellItems.begin(); it != m_sellItems.end(); it++)
    {
        if(it->second == item)
        {
            Party* party = GameController::getInstance()->getParty();
            if(party->RemoveMoney(it->first))
            {
                party->AddItem(item);
                m_sellItems.erase(it);
            }
            break;
        }
    }
    Quit();
}

void MapEventShop::Quit()
{
    m_node->setVisibility(false);
}

void MapEventShop::Sleep()
{
    Party* party = GameController::getInstance()->getParty();
    if(party->RemoveMoney(m_innPrice))
    {
        std::vector<std::shared_ptr<PartyMember> >* member = party->GetAllPartyMembers();
        for(int i = 0; i < member->size(); i++)
        {
            member->at(i)->Heal(member->at(i)->GetAttribute(BattleEnums::AttributeMaxHp));
            member->at(i)->RestoreMana(member->at(i)->GetAttribute(BattleEnums::AttributeMaxMp));
        }
    }
    Quit();
}
