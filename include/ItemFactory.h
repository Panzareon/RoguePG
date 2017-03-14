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

        enum ItemRarity{StartingItem, BaseItem};

        Item* GetRandomItem(Item::ItemType type, ItemRarity rarity);
        Item* GetRandomEquipment(ItemRarity rarity);
        Item* GetRandomEquipment(Equipment::EquipmentPosition pos, ItemRarity rarity);

    protected:
        static ItemFactory* m_instance;
        ItemFactory();

        std::map<Item::ItemType, std::map<ItemRarity, std::vector<int> > > m_itemIds;
        std::map<Equipment::EquipmentPosition, std::map<ItemRarity, std::vector<int> > > m_equipmentIds;

    private:
};

#endif // ITEMFACTORY_H
