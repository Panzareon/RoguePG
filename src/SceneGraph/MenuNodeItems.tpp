#include "SceneGraph/MenuNodeItems.h"
#include "Exception/InvalidFunctionException.h"
#include "SceneManager/SceneManagerGameMenu.h"
#include "Party/Equipment.h"

template<class T> MenuNodeItems<T>::MenuNodeItems(int width, std::function<void(T)> onSelect) : MenuNode(width)
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

template<class T> void MenuNodeItems<T>::AddOptionWithItem(std::string name, std::function<void()>func, T item, bool available)
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

        if(!m_isMovingOption)
        {
            m_onSelect(m_optionItems[m_selected]);
            m_options[m_selected]->CallSelectFunction();
        }
    }
    if(m_selected < m_scrollPosition)
        m_scrollPosition--;
}

template<class T> void MenuNodeItems<T>::MoveDown()
{
    if((int)m_selected < ((int)m_options.size()) - 1)
    {
        m_selected ++;

        if(!m_isMovingOption)
        {
            m_onSelect(m_optionItems[m_selected]);
            m_options[m_selected]->CallSelectFunction();
        }
    }
    if(m_selected - m_scrollPosition >= m_maxShownNumber)
        m_scrollPosition++;
}


template<class T> void MenuNodeItems<T>::MoveRight()
{
    //Check if this should do anything
    if(m_nextAvailable && !m_isMovingOption)
    {
        if(m_nextFunction == nullptr)
        {
            Use();
        }
        else
        {
            m_nextFunction(m_optionItems[m_selected]);
        }
    }
}

template<class T> void MenuNodeItems<T>::CallOnNext(std::function<void(T)>func)
{
    m_nextFunction = func;
}

template<class T> void MenuNodeItems<T>::SortOption()
{
    if(m_selected != m_startingPosition)
    {
        std::swap(m_optionItems[m_selected], m_optionItems[m_startingPosition]);
    }
    MenuNode::SortOption();
}

