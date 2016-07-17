#ifndef FILLITEM_H
#define FILLITEM_H

#include "Map.h"

class FillItem
{
    public:
        enum ItemSize{Single, AboveHero, AndOneAbove};
        enum Type{Blocking, Walkable};

        FillItem(int Item, int chance, Type type = Blocking, ItemSize size = Single);
        virtual ~FillItem();

        bool CanInsertAt(Map* map, int x, int y);
        void Insert(Map* map, int x, int y, int layerId, int layerAboveHero);

        int GetChance();
        Type GetType();


    protected:
    private:

        int m_itemId;
        int m_chance;
        ItemSize m_size;
        Type m_type;
};

#endif // FILLITEM_H
