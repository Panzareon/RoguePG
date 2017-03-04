#include "TextNode.h"
#include "Configuration.h"

TextNode::TextNode(std::string text)
{
    //ctor
    sf::Font* font = Configuration::GetInstance()->GetFont();
    m_text = sf::Text(text, *font);
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
}

void TextNode::SetText(std::string text)
{
    m_text.setString(text);
}

void TextNode::SetColor(sf::Color c)
{
    m_text.setColor(c);
}

sf::FloatRect TextNode::getBoundingBox()
{
    return m_text.getLocalBounds();
}

