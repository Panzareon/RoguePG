#include "MenuNodeItems.h"
#include "InvalidFunctionException.h"

MenuNodeItems::MenuNodeItems(int width, std::function<void(void*)> onSelect) : MenuNode(width)
{
    //ctor
    m_onSelect = onSelect;
}

MenuNodeItems::~MenuNodeItems()
{
    //dtor
}

void MenuNodeItems::ResetOptions()
{
    MenuNode::ResetOptions();
    m_optionItems.clear();
}

void MenuNodeItems::AddOption(std::string name, std::function<void()>func, void* item, bool available)
{
    MenuNode::AddOption(name, func, available);
    m_optionItems.push_back(item);
}

void MenuNodeItems::AddOption(std::string name, std::function<void()>func, bool available)
{
    throw InvalidFunctionException("MenuNodeItems::AddOption only with item available!");
}

void MenuNodeItems::AddDisabledOption(std::string name)
{
    throw InvalidFunctionException("MenuNodeItems::AddDisabledOption not available!");
}

void MenuNodeItems::MoveUp()
{
    if(m_selected > 0)
    {
        m_selected--;
        m_onSelect(m_optionItems[m_selected]);
    }
}

void MenuNodeItems::MoveDown()
{
    if(m_selected < m_optionName.size() - 1)
    {
        m_selected ++;
        m_onSelect(m_optionItems[m_selected]);
    }
}
