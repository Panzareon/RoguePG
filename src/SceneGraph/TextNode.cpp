#include "SceneGraph/TextNode.h"
#include "Controller/Configuration.h"

TextNode::TextNode(std::string text)
{
    //ctor
    sf::Font* font = Configuration::GetInstance()->GetFont();
    m_text = sf::Text(text, *font);
    m_maxLength = 0;
}

TextNode::~TextNode()
{
    //dtor
}

void TextNode::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
    target.draw(m_text, transform);
}

void TextNode::SetFontSize(int fontSize)
{
    m_text.setCharacterSize(fontSize);
    UpdateString();
}

void TextNode::SetText(std::string text)
{
    m_text.setString(text);
    UpdateString();
}

void TextNode::SetColor(sf::Color c)
{
    m_text.setColor(c);
}

void TextNode::SetMaxLength(int length)
{
    m_maxLength = length;
    UpdateString();
}

void TextNode::UpdateString()
{
    //if there is no bounds, do nothing
    if(m_maxLength == 0)
    {
        return;
    }

    //If the width is already smaller than the bound, do nothing
    if(m_text.getLocalBounds().width <= m_maxLength)
    {
        return;
    }

    std::string remaining = m_text.getString();
    std::string finalString = "";
    std::string temp = "";
    while(remaining.size() > 0)
    {
        int i = 0;
        for(; i < remaining.size() && remaining[i] != ' '; i++)
        {
            temp += remaining[i];
        }
        temp += ' ';
        m_text.setString(temp);

        if(m_text.getLocalBounds().width <= m_maxLength)
        {
            finalString = temp;
        }
        else
        {
            finalString += "\n";
            finalString += remaining.substr(0, i);
            finalString += ' ';
            temp = finalString;
        }
        remaining.erase(0, i + 1);
    }
    m_text.setString(finalString);
}

sf::FloatRect TextNode::getBoundingBox()
{
    return m_text.getLocalBounds();
}

