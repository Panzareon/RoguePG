#include "MenuNodeItems.h"
#include "InvalidFunctionException.h"
#include "SceneManagerGameMenu.h"
#include "Equipment.h"

template<class T> MenuNodeItems<T>::MenuNodeItems(int width, std::function<void(T*)> onSelect) : MenuNode(width)
{
    //ctor
    m_onSelect = onSelect;
}

template<class T> MenuNodeItems<T>::~MenuNodeItems()
{
    //dtor
}

template<class T> void MenuNodeItems<T>::ResetOptions()
{
    MenuNode::ResetOptions();
    m_optionItems.clear();
}

template<class T> void MenuNodeItems<T>::AddOptionWithItem(std::string name, std::function<void()>func, T* item, bool available)
{
    MenuNode::AddOption(name, func, available);
    m_optionItems.push_back(item);
}

template<class T> void MenuNodeItems<T>::AddOption(std::string name, std::function<void()>func, bool available)
{
    throw InvalidFunctionException("MenuNodeItems::AddOption only with item available!");
}

template<class T> void MenuNodeItems<T>::AddDisabledOption(std::string name)
{
    throw InvalidFunctionException("MenuNodeItems::AddDisabledOption not available!");
}

template<class T> void MenuNodeItems<T>::MoveUp()
{
    if(m_selected > 0)
    {
        m_selected--;
        m_onSelect(m_optionItems[m_selected]);
    }
}

template<class T> void MenuNodeItems<T>::MoveDown()
{
    if((int)m_selected < ((int)m_optionName.size()) - 1)
    {
        m_selected ++;
        m_onSelect(m_optionItems[m_selected]);
    }
}

