#include "MapGeneration/MapEventChest.h"
#include "Controller/GameController.h"
#include "Party/ItemFactory.h"
#include "Controller/Localization.h"
#include "SceneManager/SceneManagerMessage.h"
#include "Controller/MathHelper.h"

#include <iostream>

MapEventChest::MapEventChest()
{

}

MapEventChest::MapEventChest(int x, int y) : MapEventTile(true, x, y, false)
{
    //ctor
}

MapEventChest::~MapEventChest()
{
    //dtor
}

void MapEventChest::Activate()
{
    if(!m_isActivated)
    {
        m_isActivated = true;
        //start this event (Give an item)
        if(rand() % 3 == 0)
        {
            //Get Item
            GameController* controller = GameController::getInstance();
            ItemFactory::ItemRarity rarity = ItemFactory::SpecialItem;
            if(controller->GetDungeonConfiguration()->GetDungeonId() <= 2)
            {
                rarity = ItemFactory::BaseItem;
            }
            Item* item = ItemFactory::GetInstance()->GetRandomEquipment(Equipment::MainHand, rarity);
            controller->getParty()->AddItem(item);
            //Receive message
            std::string toDisplay;
            Localization* localization = Localization::GetInstance();
            std::vector<std::string> itemName;
            itemName.push_back(localization->GetLocalization(item->GetName()));
            toDisplay = localization->GetLocalizationWithStrings("chest.receive_item", &itemName);
            SceneManagerMessage* message = new SceneManagerMessage(toDisplay);
            controller->LoadSceneManager(message);
        }
        else
        {
            //Get money
            int gold = MathHelper::GetInstance()->GetRandomInt(150, 50, true);
            GameController* controller = GameController::getInstance();
            controller->getParty()->AddMoney(gold);
            //Receive message
            std::string toDisplay;
            Localization* localization = Localization::GetInstance();
            std::vector<std::string> moneyValue;
            moneyValue.push_back(std::to_string(gold));
            toDisplay = localization->GetLocalizationWithStrings("chest.receive_gold", &moneyValue);
            SceneManagerMessage* message = new SceneManagerMessage(toDisplay);
            controller->LoadSceneManager(message);
        }
    }
}
