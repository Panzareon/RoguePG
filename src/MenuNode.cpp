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
    m_nextAvailable = false;
    m_previousAvailable = false;
    m_backgroundColor = sf::Color::Black;
    m_foregroundColor = sf::Color::White;
    m_outlineColor = sf::Color::White;
    m_foregroundColorDisabled = sf::Color(120,120,120);
    m_selectedColor = sf::Color::Blue;
    m_selectedDrawable = nullptr;
    m_paddingX = 0;
    m_paddingY = 0;
    m_background = sf::RectangleShape(sf::Vector2f(width,0));
    m_optionHeight = 24;
    m_fontSize = 24;
    m_spacing = 0;
    UpdateBackground();
}

void MenuNode::UpdateBackground()
{
    //First Background
    m_height = m_maxShownNumber;
    if(m_maxShownNumber > m_optionName.size())
    {
        m_height = m_optionName.size();
    }
    //TODO: save Shape as class member?
    m_background.setSize(sf::Vector2f(m_width, m_height* m_optionHeight));
    //TODO: maybe use Texture
    m_background.setFillColor(m_backgroundColor);
    m_background.setOutlineColor(m_outlineColor);
    m_background.setOutlineThickness(1.0f);
}

MenuNode::~MenuNode()
{
    //dtor
}

void MenuNode::AddOption(std::string name, std::function<void()> func, bool available)
{
    m_optionName.push_back(name);
    m_optionAvailable.push_back(available);
    m_optionFunction.push_back(func);
    UpdateBackground();
}

void MenuNode::AddDisabledOption(std::string name)
{
    m_optionName.push_back(name);
    m_optionAvailable.push_back(false);
    m_optionFunction.push_back(std::function<void()>());
    UpdateBackground();
}

void MenuNode::CallOnCancel(std::function<void()>func)
{
    m_cancelFunction = func;
}

void MenuNode::CancelAvailable(bool cancel)
{
    m_cancelAvailable = cancel;
}

void MenuNode::NextAvailable(bool next)
{
    m_nextAvailable = next;
}

void MenuNode::PreviousAvailable(bool prev)
{
    m_previousAvailable = prev;
}

void MenuNode::CallOnNext(std::function<void()>func)
{
    m_nextFunction = func;
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
    UpdateBackground();
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

void MenuNode::MoveRight()
{
    //Check if this should do anything
    if(m_nextAvailable)
    {
        if(m_nextFunction == nullptr)
        {
            Use();
        }
        else
        {
            m_nextFunction();
        }
    }
}

void MenuNode::Use()
{
    if(m_optionFunction.size() > m_selected)
        if(m_optionAvailable[m_selected])
            m_optionFunction[m_selected]();
}
void MenuNode::onDraw(sf::RenderTarget& target, const sf::Transform& transformBase) const
{
    //Draw Menu
    sf::Transform transform(transformBase);
    target.draw(m_background, transform);

    //Background of selected option
    int pos = m_selected - m_scrollPosition;
    if(pos >= 0 && pos < m_maxShownNumber)
    {
        //if Selected is visible
        transform.translate(0.0f, pos * m_optionHeight);
        if(m_selectedDrawable != nullptr)
        {
            target.draw(*m_selectedDrawable, transform);
        }
        else
        {
            sf::RectangleShape selected(sf::Vector2f(m_width, m_optionHeight));
            selected.setFillColor(m_selectedColor);
            target.draw(selected, transform);
        }

    }
    sf::Font* font = Configuration::GetInstance()->GetFont();
    //all visible options
    for(int i = 0; i < m_height; i++)
    {
        //draw text for m_scrollPosition + i at position i
        transform = transformBase;
        transform.translate(m_paddingX, i*m_optionHeight + m_paddingY);
        sf::Text text(m_optionName[m_scrollPosition+i], *font);
        text.setCharacterSize(m_fontSize);
        if(m_optionAvailable[m_scrollPosition+i])
            text.setColor(m_foregroundColor);
        else
            text.setColor(m_foregroundColorDisabled);

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
        else if(controller->IsKeyPressed(Configuration::Accept))
        {
            Use();
        }
        else if(controller->IsKeyPressed(Configuration::Cancel) || (controller->IsKeyPressed(Configuration::MoveLeft) && m_previousAvailable))
        {
            //Cancel Menu / check if menu can be canceled
            if(m_cancelAvailable)
            {
                if(m_cancelFunction)
                {
                    m_cancelFunction();
                }
                m_visible = false;
            }
        }
        else if(controller->IsKeyPressed(Configuration::MoveRight))
        {
            MoveRight();
        }
    }
}

int MenuNode::GetScrollPosition()
{
    return m_scrollPosition;
}

void MenuNode::SetMaxShownOptions(int nr)
{
    if(nr > 0)
    {
        m_maxShownNumber = nr;
    }
}


void MenuNode::SetBackgroundColor(sf::Color c)
{
    m_backgroundColor = c;
    UpdateBackground();
}

void MenuNode::SetForegroundColor(sf::Color c)
{
    m_foregroundColor = c;
}

void MenuNode::SetForegroundColorDisabled(sf::Color c)
{
    m_foregroundColorDisabled = c;
}

void MenuNode::SetSelectedColor(sf::Color c)
{
    m_selectedColor = c;
}

void MenuNode::SetOutlineColor(sf::Color c)
{
    m_outlineColor = c;
    UpdateBackground();
}

void MenuNode::SetSelectedTexture(Texture* texture)
{
    if(m_selectedDrawable != nullptr)
    {
        delete m_selectedDrawable;
    }
    m_selectedDrawable = new sf::Sprite(*texture);
}

void MenuNode::SetPadding(int x, int y)
{
    m_paddingX = x;
    m_paddingY = y;
}
void MenuNode::SetFontSize(int s)
{
    m_fontSize = s;
    m_optionHeight = m_spacing + m_fontSize;
}

void MenuNode::SetSpacing(int s)
{
    m_spacing = s;
    m_optionHeight = m_spacing + m_fontSize;
}


