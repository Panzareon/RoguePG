#ifndef ITEM_H
#define ITEM_H


class Item
{
    public:
        Item(int itemId);
        virtual ~Item();

        int GetItemId();
    protected:
        int m_itemId;

    private:
};

#endif // ITEM_H
