#include "Party/Item.h"
#include "Party/ItemFactory.h"

Item::Item()
{
    //ctor
}
Item::Item(int itemId, ItemType type)
{
    //ctor
    m_itemId = itemId;
    m_itemType = type;
}

Item::~Item()
{
    //dtor
}

int Item::GetItemId()
{
    return m_itemId;
}

Item::ItemType Item::GetItemType()
{
    return m_itemType;
}

std::string Item::GetName()
{
    return "item." + std::to_string(m_itemId);
}

std::string Item::GetDescription()
{
    return GetName() + ".desc";
}

void Item::LoadItem()
{
    ItemFactory::GetInstance()->LoadItem(m_itemType, m_itemId, this);
}
