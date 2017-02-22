#ifndef MENUNODEITEMS_H
#define MENUNODEITEMS_H

#include "MenuNode.h"

//A Menu to select one of multiple Instances of a Class

class MenuNodeItems : public MenuNode
{
    public:
        MenuNodeItems(int width, std::function<void(void*)> onSelect);
        virtual ~MenuNodeItems();
        virtual void ResetOptions();
        virtual void MoveUp();
        virtual void MoveDown();
        virtual void AddOption(std::string name, std::function<void()> func, void* item, bool available = true);
        virtual void AddOption(std::string name, std::function<void()> func, bool available = true);
        virtual void AddDisabledOption(std::string name);

    protected:
        std::vector<void*> m_optionItems;

        std::function<void(void*)> m_onSelect;

    private:
};

#endif // MENUNODEITEMS_H
