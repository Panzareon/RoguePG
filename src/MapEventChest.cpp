#include "MapEventChest.h"
#include "GameController.h"
#include "ItemFactory.h"
#include "Localization.h"
#include "SceneManagerMessage.h"

#include <iostream>

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
        Item* item = ItemFactory::GetInstance()->GetRandomEquipment(Equipment::MainHand);
        GameController* controller = GameController::getInstance();
        controller->getParty()->AddItem(item);
        std::cout << "Got Item" << std::endl;
        //Receive message
        std::string toDisplay;
        Localization* localization = Localization::GetInstance();
        std::vector<std::string> itemName;
        itemName.push_back(localization->GetLocalization(item->GetName()));
        toDisplay = localization->GetLocalizationWithStrings("chest.receive_item", &itemName);
        SceneManagerMessage* message = new SceneManagerMessage(toDisplay);
        controller->LoadSceneManager(message);
    }
}
