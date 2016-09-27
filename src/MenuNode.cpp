#include "MenuNode.h"
#include "Configuration.h"
#include "GameController.h"


MenuNode::MenuNode(int width)
{
    //ctor
    m_selected = 0;
    m_scrollPosition = 0;
    m_maxShownNumber = 4;
    m_width = width;
    m_cancelAvailable = false;
    //TODO: set Color
    m_backgroundColor = sf::Color::Black;
    m_foregroundColor = sf::Color::White;
    m_selectedColor = sf::Color::Blue;

    m_optionHeight = 24;
}

MenuNode::~MenuNode()
{
    //dtor
}

void MenuNode::AddOption(std::string name, std::function<void()> func)
{
    m_optionName.push_back(name);
    m_optionFunction.push_back(func);
}
void MenuNode::CancelAvailable(bool cancel)
{
    m_cancelAvailable = cancel;
}

void MenuNode::ResetOptions()
{
    m_optionName.clear();
    m_optionFunction.clear();
    for(unsigned int i = 0; i < m_children.size(); i++)
    {
        delete m_children[i];
    }
    m_children.clear();
}
void MenuNode::MoveUp()
{
    if(m_selected > 0)
        m_selected--;
}

void MenuNode::MoveDown()
{
    if(m_selected < m_optionName.size() - 1)
        m_selected ++;
}

void MenuNode::Use()
{
    if(m_optionFunction.size() > m_selected)
        m_optionFunction[m_selected]();
}
void MenuNode::onDraw(sf::RenderTarget& target, const sf::Transform& transformBase) const
{
    //Draw Menu
    //First Background
    int height = m_maxShownNumber;
    if(m_maxShownNumber > m_optionName.size())
    {
        height = m_optionName.size();
    }
    //TODO: save Shape as class member?
    sf::RectangleShape background(sf::Vector2f(m_width, height* m_optionHeight));
    //TODO: maybe use Texture
    background.setFillColor(m_backgroundColor);
    background.setOutlineColor(m_foregroundColor);
    background.setOutlineThickness(1.0f);
    sf::Transform transform(transformBase);
    target.draw(background, transform);

    //Background of selected option
    int pos = m_selected - m_scrollPosition;
    if(pos >= 0 && pos < m_maxShownNumber)
    {
        //if Selected is visible
        sf::RectangleShape selected(sf::Vector2f(m_width, m_optionHeight));
        selected.setFillColor(m_selectedColor);

        transform.translate(0.0f, pos * m_optionHeight);
        target.draw(selected, transform);
    }
    sf::Font* font = Configuration::GetInstance()->GetFont();
    //all visible options
    for(int i = 0; i < height; i++)
    {
        //draw text for m_scrollPosition + i at position i
        transform = transformBase;
        transform.translate(0.0f, i*m_optionHeight);
        sf::Text text(m_optionName[m_scrollPosition+i], *font);
        text.setCharacterSize(m_optionHeight);
        text.setColor(m_foregroundColor);

        target.draw(text, transform);
    }

}

void MenuNode::CheckKeyboardInput()
{
    //remove hidden sub menus
    for(unsigned int i = 0; i < m_children.size(); i++)
    {
        if(!m_children[i]->IsVisible())
        {
            delete m_children[i];
            m_children.erase(m_children.begin() + i);
            i--;
        }
    }

    //if there is a active child call this function on it
    if(m_children.size() > 0)
    {
        ((MenuNode*)m_children.back())->CheckKeyboardInput();
    }
    else
    {
        GameController* controller = GameController::getInstance();

        if(controller->IsKeyPressed(Configuration::MoveDown))
        {
            MoveDown();
        }
        else if(controller->IsKeyPressed(Configuration::MoveUp))
        {
            MoveUp();
        }

        if(controller->IsKeyPressed(Configuration::Accept))
        {
            Use();
        }
        else if(controller->IsKeyPressed(Configuration::Cancel))
        {
            //Cancel Menu / check if menu can be canceled
            if(m_cancelAvailable)
            {
                m_visible = false;
            }
        }
    }
}

