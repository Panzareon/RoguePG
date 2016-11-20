#include "ItemFactory.h"
#include "InvalidArgumentException.h"

ItemFactory* ItemFactory::m_instance = nullptr;

ItemFactory::ItemFactory()
{
    //ctor
    //TODO: init all ItemIds
}

ItemFactory::~ItemFactory()
{
    //dtor
}
ItemFactory* ItemFactory::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new ItemFactory();
    }
    return m_instance;
}

Item* ItemFactory::GetRandomItem(Item::ItemType type)
{
    if(type == Item::ItemTypeEquipment)
        return GetRandomEquipment();
    int random = rand() % m_itemIds[type].size();
    int itemId = m_itemIds[type][random];
    Item* retval = new Item(itemId, type);
    switch(itemId)
    {
        //TODO: Init Item with Id itemId

    default:
        std::string msg("Invalid ItemId ");
        msg.append(std::to_string(itemId));
        msg.append(" given.");
        throw GenericException(msg);
    }
    return new Item(itemId, type);
}

Item* ItemFactory::GetRandomEquipment()
{
    int random = rand() % Equipment::EQUIPMENT_POSITION_END;
    return GetRandomEquipment((Equipment::EquipmentPosition) random);
}

Item* ItemFactory::GetRandomEquipment(Equipment::EquipmentPosition pos)
{
    int random = rand() % m_equipmentIds[pos].size();
    int itemId = m_equipmentIds[pos][random];
    Equipment* retval = new Equipment(itemId);
    switch(pos)
    {
        //TODO: Init Equipment with Id itemId
    default:
        std::string msg("Invalid ItemId ");
        msg.append(std::to_string(itemId));
        msg.append(" given.");
        throw GenericException(msg);
    }
    return retval;
}
