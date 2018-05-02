#include "SceneGraph/MenuNodeOption.h"

MenuNodeOption::MenuNodeOption(std::string name, bool available)
{
    //ctor
    m_name = name;
    m_available = available;
    m_value = "";
    m_node = nullptr;
}

MenuNodeOption::~MenuNodeOption()
{
    //dtor
    if(m_node != nullptr)
    {
        delete m_node;
    }
}
void MenuNodeOption::SetValue(std::string value)
{
    m_value = value;
}

void MenuNodeOption::SetNode(Node* node)
{
    m_node = node;
}

void MenuNodeOption::SetAvailable(bool available)
{
    m_available = available;
}

void MenuNodeOption::SetFunction(std::function<void()>addFunction)
{
    m_function = addFunction;
}

void MenuNodeOption::SetSelectFunction(std::function<void()>addFunction)
{
    m_selectFunction = addFunction;
}

std::string MenuNodeOption::GetName()
{
    return m_name;
}

std::string MenuNodeOption::GetValue()
{
    return m_value;
}

Node* MenuNodeOption::GetNode()
{
    return m_node;
}

bool MenuNodeOption::IsAvailable()
{
    return m_available;
}

void MenuNodeOption::CallFunction()
{
    if(m_function != nullptr)
    {
        m_function();
    }
}

void MenuNodeOption::CallSelectFunction()
{
    if(m_selectFunction != nullptr)
    {
        m_selectFunction();
    }
}
