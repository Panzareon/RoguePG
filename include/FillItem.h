#ifndef FILLITEM_H
#define FILLITEM_H

#include "Map.h"

class FillItem
{
    public:
        enum ItemSize{Single, AboveHero, AndOneAbove, AtWallDouble};
        enum PlacingRestriction{Default, None, AtWall};
        enum Type{Blocking, Walkable, Wall};

        FillItem(int Item, int chance, Type type = Blocking, ItemSize size = Single, PlacingRestriction restr = Default);
        virtual ~FillItem();

        bool CanInsertAt(Map* map, int x, int y, int LayerId, int LayerAboveHero);
        void Insert(Map* map, int x, int y, int layerId, int layerAboveHero);

        int GetChance();
        Type GetType();


    protected:
    private:

        int m_itemId;
        int m_chance;
        ItemSize m_size;
        Type m_type;
        PlacingRestriction m_restr;
};

#endif // FILLITEM_H
