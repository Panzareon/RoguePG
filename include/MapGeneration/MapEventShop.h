#ifndef MAPEVENTSHOP_H
#define MAPEVENTSHOP_H

#include "MapEventTile.h"
#include "Party/Item.h"
#include "Party/ItemFactory.h"
#include "SceneGraph/Node.h"

#include <map>
#include "SceneGraph/MenuNode.h"

class MapEventShop : public MapEventTile
{
    public:
        enum ShopTypes{SwordShop, ShieldShop, Inn, SpellShop, StaffShop, SHOP_TYPES_END};
        MapEventShop();
        MapEventShop(int x, int y, ShopTypes type);
        virtual ~MapEventShop();
        virtual void Activate();

        void BuyItem(Item* item);
        void Quit();
        void Sleep();

        void Restock();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            std::multimap<int, int> sellItems;
            for(auto it = m_sellItems.begin(); it != m_sellItems.end(); it++)
            {
                sellItems.insert(std::pair<int, int>(it->first, it->second->GetItemId()));
            }
            archive(cereal::base_class<MapEventTile>( this ), m_type, m_innPrice, sellItems);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            std::multimap<int, int> sellItems;
            archive(cereal::base_class<MapEventTile>( this ), m_type, m_innPrice, sellItems);
            for(auto it = sellItems.begin(); it != sellItems.end(); it++)
            {
                m_sellItems.insert(std::pair<int, Item*>(it->first, ItemFactory::GetInstance()->GetEquipment(Equipment::MainHand, it->second)));
            }
        }

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
