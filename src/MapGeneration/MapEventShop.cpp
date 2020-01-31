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

MapEventShop::MapEventShop()
{

}

MapEventShop::MapEventShop(int x, int y, ShopTypes type) : MapEventTile(true, x, y, false)
{
    //ctor
    m_type = type;
    m_innPrice = 10;
    SetAvailableItems();
    if(m_type != Inn)
    {
        int nrItems = GameController::getInstance()->GetPersistentProgress()->GetShopNrItems();
        for(int i = 0; i < nrItems; i++)
        {
            Restock();
        }
    }
}

MapEventShop::~MapEventShop()
{
    //dtor
}

void MapEventShop::Restock()
{
    int shopLvl = GameController::getInstance()->GetPersistentProgress()->GetShopLevel();
    float chance = 0.0f;
    for(int i = 1; i <= shopLvl; i++)
    {
        auto it = m_availableItemIds.find(i);
        if(it != m_availableItemIds.end())
        {
            for(auto itInner = it->second.begin(); itInner != it->second.end(); itInner++)
            {
                chance += itInner->first;
            }
        }
    }
    float random = rand() / (float)RAND_MAX;
    random *= chance;
    for(int i = 1; i <= shopLvl; i++)
    {
        auto it = m_availableItemIds.find(i);
        if(it != m_availableItemIds.end())
        {
            for(auto itInner = it->second.begin(); itInner != it->second.end(); itInner++)
            {
                random -= itInner->first;
                if(random <= 0.0f)
                {
                    m_sellItems.insert(std::pair<int, Item*>(itInner->second.first, ItemFactory::GetInstance()->GetEquipment(Equipment::MainHand, itInner->second.second)));
                    return;
                }
            }
        }
    }

}

void MapEventShop::SetAvailableItems()
{
    switch(m_type)
    {
    case SwordShop:
        m_availableItemIds[1].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(30, 1)));
        m_availableItemIds[2].insert(std::pair<float, std::pair<int, int> >(2.0f, std::pair<int, int>(100, 101)));
        m_availableItemIds[3].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(200, 1001)));
        break;
    case ShieldShop:
        m_availableItemIds[1].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(30, 2)));
        m_availableItemIds[2].insert(std::pair<float, std::pair<int, int> >(2.0f, std::pair<int, int>(100, 102)));
        m_availableItemIds[3].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(200, 1101)));
        break;
    case StaffShop:
        m_availableItemIds[1].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(30, 3)));
        m_availableItemIds[2].insert(std::pair<float, std::pair<int, int> >(2.0f, std::pair<int, int>(100, 103)));
        m_availableItemIds[3].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(200, 1201)));
        break;
    case SpellShop:
        m_availableItemIds[1].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(30, 4)));
        m_availableItemIds[2].insert(std::pair<float, std::pair<int, int> >(2.0f, std::pair<int, int>(100, 104)));
        m_availableItemIds[3].insert(std::pair<float, std::pair<int, int> >(1.0f, std::pair<int, int>(200, 1301)));
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
        m_node->moveNode(-2.0f, 10.0f);
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

    m_node->moveNode(-2.0f, 10.0f);
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
            member->at(i)->Heal(member->at(i)->GetAttribute(BattleEnums::Attribute::MaxHp));
            member->at(i)->RestoreMana(member->at(i)->GetAttribute(BattleEnums::Attribute::MaxMp));
        }
    }
    Quit();
}
