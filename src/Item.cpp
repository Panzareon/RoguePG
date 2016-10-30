#include "Item.h"

Item::Item(int itemId)
{
    //ctor
    m_itemId = itemId;
}

Item::~Item()
{
    //dtor
}

int Item::GetItemId()
{
    return m_itemId;
}
