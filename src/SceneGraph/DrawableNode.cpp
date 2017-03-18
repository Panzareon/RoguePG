#include "SceneGraph/DrawableNode.h"

DrawableNode::DrawableNode(sf::Drawable *drawable)
{
    //ctor
    m_drawable = drawable;
}

DrawableNode::~DrawableNode()
{
    //dtor
    delete m_drawable;
}

void DrawableNode::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
    target.draw(*m_drawable, transform);
}
