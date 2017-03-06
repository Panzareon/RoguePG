#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"
#include "Equipment.h"
#include <vector>
#include <map>

class ItemFactory
{
    public:
        virtual ~ItemFactory();
        static ItemFactory* GetInstance();

        Item* GetRandomItem(Item::ItemType type);
        Item* GetRandomEquipment();
        Item* GetRandomEquipment(Equipment::EquipmentPosition pos);

    protected:
        static ItemFactory* m_instance;
        ItemFactory();

        std::map<Item::ItemType, std::vector<int>> m_itemIds;
        std::map<Equipment::EquipmentPosition, std::vector<int>> m_equipmentIds;

    private:
};

#endif // ITEMFACTORY_H
