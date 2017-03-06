#include "AnimationPartText.h"

#include "DrawableNode.h"
#include "Configuration.h"

AnimationPartText::AnimationPartText(std::string str, sf::Color color, int fontSize)
{
    //ctor
    m_text = new sf::Text(str, *Configuration::GetInstance()->GetFont(), fontSize);
    m_text->setColor(color);
    m_node = new DrawableNode(m_text);
    m_size = m_text->getLocalBounds();
}

AnimationPartText::~AnimationPartText()
{
    //dtor
}

sf::Text* AnimationPartText::GetText()
{
    return m_text;
}
