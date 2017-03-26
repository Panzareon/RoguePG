#ifndef MENUNODEITEMS_H
#define MENUNODEITEMS_H

#include "MenuNode.h"

class SceneManagerGameMenu;

//A Menu to select one of multiple Instances of a Class

template<class T> class MenuNodeItems : public MenuNode
{
    public:
        MenuNodeItems(int width, std::function<void(T)> onSelect);
        virtual ~MenuNodeItems();
        virtual void ResetOptions();
        virtual void MoveUp();
        virtual void MoveDown();
        virtual void MoveRight();
        virtual void CallOnNext(std::function<void(T)> func);
        virtual void AddOptionWithItem(std::string name, std::function<void()> func, T item, bool available = true);
        virtual void AddOption(std::string name, std::function<void()> func, bool available = true);
        virtual void AddDisabledOption(std::string name);

    protected:
        std::vector<T> m_optionItems;

        std::function<void(T)> m_onSelect;
        std::function<void(T)> m_nextFunction;

    private:
};

#include "../src/SceneGraph/MenuNodeItems.tpp"

#endif // MENUNODEITEMS_H
