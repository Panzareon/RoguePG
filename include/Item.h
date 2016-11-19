#ifndef ITEM_H
#define ITEM_H


class Item
{
    public:
        enum ItemType{ItemTypeUsable, ItemTypeEquipment, ItemTypeQuestItem, ITEM_TYPE_END};
        Item(int itemId, ItemType type);
        virtual ~Item();

        int GetItemId();
        ItemType GetItemType();
    protected:
        int m_itemId;
        ItemType m_itemType;

    private:
};

#endif // ITEM_H
