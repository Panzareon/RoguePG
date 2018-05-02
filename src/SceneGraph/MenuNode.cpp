#include "SceneGraph/MenuNode.h"
#include "Controller/Configuration.h"
#include "Controller/GameController.h"


MenuNode::MenuNode(int width)
{
    //ctor
    m_selected = 0;
    m_scrollPosition = 0;
    m_maxShownNumber = 4;
    m_width = width;
    m_visibleWithSubmenu = false;
    m_cancelAvailable = false;
    m_nextAvailable = false;
    m_previousAvailable = false;
    m_showSelected = true;
    m_sortingAvailable = false;
    m_isMovingOption = false;
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
    if(m_maxShownNumber > m_options.size())
    {
        m_height = m_options.size();
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
    for(int i = 0; i < m_options.size(); i++)
    {
        delete m_options[i];
    }
}

void MenuNode::AddOption(std::string name, std::function<void()> func, bool available)
{
    MenuNodeOption* option = new MenuNodeOption(name, available);
    option->SetFunction(func);
    m_options.push_back(option);
    UpdateBackground();
}

void MenuNode::AddDisabledOption(std::string name)
{
    MenuNodeOption* option = new MenuNodeOption(name, false);
    m_options.push_back(option);
    UpdateBackground();
}

void MenuNode::AddDisabledOption(std::string name, std::function<void()> onSelect)
{
    MenuNodeOption* option = new MenuNodeOption(name, false);
    option->SetSelectFunction(onSelect);
    m_options.push_back(option);
    UpdateBackground();
}

void MenuNode::AddOption(std::string name, std::function<void()>func, std::function<void()>onSelect, bool available)
{
    MenuNodeOption* option = new MenuNodeOption(name, available);
    option->SetFunction(func);
    option->SetSelectFunction(onSelect);
    m_options.push_back(option);
    UpdateBackground();

}

void MenuNode::AddValueToOption(int optionNr, std::string value)
{
    if(m_options.size() > optionNr)
        m_options[optionNr]->SetValue(value);
}

void MenuNode::AddNodeToOption(int optionNr, Node* node)
{
    if(m_options.size() > optionNr)
        m_options[optionNr]->SetNode(node);
}

void MenuNode::CallOnCancel(std::function<void()>func)
{
    m_cancelFunction = func;
}

void MenuNode::CancelAvailable(bool cancel)
{
    m_cancelAvailable = cancel;
}

void MenuNode::EnableSorting(std::function<void(int, int)>onSort)
{
    m_sortFunction = onSort;
    m_sortingAvailable = true;
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
    m_selected = 0;
    for(int i = 0; i < m_options.size(); i++)
    {
        delete m_options[i];
    }
    m_options.clear();
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
    if(m_selected < m_scrollPosition)
        m_scrollPosition--;
    if(!m_isMovingOption)
    {
        m_options[m_selected]->CallSelectFunction();
    }
}

void MenuNode::MoveDown()
{
    if(m_selected < m_options.size() - 1)
        m_selected ++;
    if(m_selected - m_scrollPosition >= m_maxShownNumber)
        m_scrollPosition++;
    if(!m_isMovingOption)
    {
        m_options[m_selected]->CallSelectFunction();
    }
}

void MenuNode::MoveRight()
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

void MenuNode::Use()
{
    m_options[m_selected]->CallFunction();
}
void MenuNode::onDraw(sf::RenderTarget& target, const sf::Transform& transformBase) const
{
    //if there is a active child do not draw this
    if(m_children.size() > 0 && !m_visibleWithSubmenu)
    {
        return;
    }
    //Draw Menu
    sf::Transform transform(transformBase);
    target.draw(m_background, transform);

    //Background of selected option
    int pos = m_selected - m_scrollPosition;
    if(pos >= 0 && pos < m_maxShownNumber && m_showSelected)
    {
        //if Selected is visible
        transform.translate(0.0f, pos * m_optionHeight);
        if(m_isMovingOption)
        {
            if(m_selected > m_startingPosition)
            {
                //Show below the item if a option below the moving option is selected
                transform.translate(0.0f, m_optionHeight);
            }
            //Draw a line where the Option would land
            sf::RectangleShape selected(sf::Vector2f(m_width, 4.0f));
            selected.setFillColor(sf::Color(255, 141, 20));
            target.draw(selected, transform);
        }
        else
        {
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
    }
    sf::Font* font = Configuration::GetInstance()->GetFont();
    //all visible options
    for(int i = 0; i < m_height; i++)
    {
        //draw text for m_scrollPosition + i at position i
        transform = transformBase;
        transform.translate(m_paddingX, i*m_optionHeight + m_paddingY);

        MenuNodeOption* option = m_options[m_scrollPosition+i];
        sf::Text text(option->GetName(), *font);
        text.setCharacterSize(m_fontSize);
        if(option->IsAvailable())
            text.setColor(m_foregroundColor);
        else
            text.setColor(m_foregroundColorDisabled);

        target.draw(text, transform);

        if(option->GetNode() != nullptr)
        {
            option->GetNode()->draw(target, transform);
        }
        if(option->GetValue() != "")
        {
            sf::Text value(option->GetValue(), *font);
            value.setCharacterSize(m_fontSize);
            if(option->IsAvailable())
                value.setColor(m_foregroundColor);
            else
                value.setColor(m_foregroundColorDisabled);


            transform = transformBase;
            transform.translate(m_width - m_paddingX - value.getLocalBounds().width, i*m_optionHeight + m_paddingY);

            target.draw(value, transform);
        }
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

        if(m_isMovingOption)
        {
            if(controller->IsKeyPressed(Configuration::Accept))
            {
                SortOption();
                m_isMovingOption = false;
            }
            else if(controller->IsKeyPressed(Configuration::Cancel))
            {
                m_isMovingOption = false;
            }
        }
        else
        {
            if(controller->IsKeyPressed(Configuration::Accept))
            {
                Use();
            }
            else if(m_cancelAvailable && (controller->IsKeyPressed(Configuration::Cancel) || (m_previousAvailable && controller->IsKeyPressed(Configuration::MoveLeft))))
            {
                //Cancel Menu / check if menu can be canceled
                m_visible = false;
                if(m_cancelFunction)
                {
                    m_cancelFunction();
                }
            }
            else if(m_nextAvailable && controller->IsKeyPressed(Configuration::MoveRight))
            {
                MoveRight();
            }
        }

        if(controller->IsKeyPressed(Configuration::MoveDown))
        {
            MoveDown();
        }
        else if(controller->IsKeyPressed(Configuration::MoveUp))
        {
            MoveUp();
        }

        //Move the selected Option
        if(m_sortingAvailable && controller->IsKeyPressed(Configuration::Action))
        {
            if(m_isMovingOption)
            {
                SortOption();
            }
            else
            {
                m_startingPosition = m_selected;
            }
            m_isMovingOption = !m_isMovingOption;
        }
    }
}

int MenuNode::GetScrollPosition()
{
    return m_scrollPosition;
}

int MenuNode::GetNrOptions()
{
    return m_options.size();
}

void MenuNode::ShowSelected(bool show)
{
    m_showSelected = show;
    if(show)
    {
        m_options[m_selected]->CallSelectFunction();
    }
}

void MenuNode::SetMaxShownOptions(int nr)
{
    if(nr > 0)
    {
        m_maxShownNumber = nr;
        UpdateBackground();
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

void MenuNode::SetVisibleWithSubmenu(bool visible)
{
    m_visibleWithSubmenu = visible;
}

void MenuNode::SortOption()
{
    if(m_selected != m_startingPosition)
    {
        MenuNodeOption* temp = m_options[m_startingPosition];
        m_options.erase(m_options.begin() + m_startingPosition);
        m_options.insert(m_options.begin() + m_selected,temp);
        if(m_sortFunction != nullptr)
        {
            m_sortFunction(m_startingPosition, m_selected);
        }
    }
}
