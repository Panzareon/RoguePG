#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    public:
        enum ItemType{ItemTypeUsable, ItemTypeEquipment, ItemTypeQuestItem, ITEM_TYPE_END};
        Item(int itemId, ItemType type);
        virtual ~Item();

        std::string GetName();
        std::string GetDescription();
        int GetItemId();
        ItemType GetItemType();
    protected:
        int m_itemId;
        ItemType m_itemType;

    private:
};

#endif // ITEM_H
