#ifndef FILLITEM_H
#define FILLITEM_H

#include "Map.h"

class FillItem
{
    public:
        enum ItemSize{Single, AboveHero, AndOneAbove, AtWallSingle, AtWallDouble};
        enum PlacingRestriction{Default, None, AtWall};
        enum Type{Blocking, Walkable, Wall};

        FillItem(int Item, int chance, int neededTile, int newTile, Type type = Blocking, ItemSize size = Single, PlacingRestriction restr = Default);
        virtual ~FillItem();

        bool CanInsertAt(Map* map, int x, int y, int LayerId, int LayerAboveHero, int LayerWallDecoration);
        void Insert(Map* map, int x, int y, int layerId, int layerAboveHero, int LayerWallDecoration);

        int GetChance();
        Type GetType();


    protected:
    private:

        int m_itemId;
        int m_chance;

        int m_insertType;

        int m_placeAtTile;
        ItemSize m_size;
        Type m_type;
        PlacingRestriction m_restr;
};

#endif // FILLITEM_H
