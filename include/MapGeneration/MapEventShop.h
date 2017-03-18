#ifndef MAPEVENTSHOP_H
#define MAPEVENTSHOP_H

#include "MapEventTile.h"
#include "Party/Item.h"
#include "SceneGraph/Node.h"

#include <map>
#include "SceneGraph/MenuNode.h"

class MapEventShop : public MapEventTile
{
    public:
        enum ShopTypes{SwordShop, ShieldShop, Inn, SpellShop, StaffShop, SHOP_TYPES_END};
        MapEventShop(int x, int y, ShopTypes type);
        virtual ~MapEventShop();
        virtual void Activate();

        void BuyItem(Item* item);
        void Quit();
        void Sleep();

        void Restock();

    protected:
        void ShowShop();
        void ShowInn();

        MenuNode* m_node;


        std::multimap<int, Item*> m_sellItems;

        int m_innPrice;

        ShopTypes m_type;

    private:
};

#endif // MAPEVENTSHOP_H
