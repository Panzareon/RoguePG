#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    public:
        enum ItemType{ItemTypeUsable, ItemTypeEquipment, ItemTypeQuestItem, ITEM_TYPE_END};
        Item();
        Item(int itemId, ItemType type);
        virtual ~Item();

        std::string GetName();
        std::string GetDescription();

        int GetItemId();
        ItemType GetItemType();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_itemId, m_itemType);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(m_itemId, m_itemType);
        }
    protected:
        int m_itemId;
        ItemType m_itemType;

    private:
};

#endif // ITEM_H
