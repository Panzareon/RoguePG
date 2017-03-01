#include "MapEventChest.h"
#include "GameController.h"
#include "ItemFactory.h"
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
        GameController::getInstance()->getParty()->AddItem(ItemFactory::GetInstance()->GetRandomEquipment(Equipment::MainHand));
        std::cout << "Got Item" << std::endl;
        //TODO: Receive message
    }
}
