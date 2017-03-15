#ifndef MAPEVENTSHOP_H
#define MAPEVENTSHOP_H


class MapEventShop
{
    public:
        enum ShopTypes{SwordShop, ShieldShop, Inn, SpellShop, StaffShop, SHOP_TYPES_END};
        MapEventShop();
        virtual ~MapEventShop();

    protected:

    private:
};

#endif // MAPEVENTSHOP_H
