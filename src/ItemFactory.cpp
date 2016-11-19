#include "ItemFactory.h"

ItemFactory* ItemFactory::m_instance = nullptr;

ItemFactory::ItemFactory()
{
    //ctor
    //TODO: init all Items
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
    return new Item(m_itemIds[type][random], type);
}

Item* ItemFactory::GetRandomEquipment()
{
    int random = rand() % Equipment::EQUIPMENT_POSITION_END;
    return GetRandomEquipment((Equipment::EquipmentPosition) random);
}

Item* ItemFactory::GetRandomEquipment(Equipment::EquipmentPosition pos)
{
    int random = rand() % m_equipmentIds[pos].size();
    return new Equipment(m_equipmentIds[pos][random]);
}
