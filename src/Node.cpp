#include "Node.h"

Node::Node()
{
    //ctor
    m_transform = sf::Transform::Identity;
}

Node::~Node()
{
    //dtor
}

void Node::draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const
{
    // combine the parent transform with the node's one
    sf::Transform combinedTransform = parentTransform * m_transform;

    // let the node draw itself
    onDraw(target, combinedTransform);

    // draw its children
    for (std::size_t i = 0; i < m_children.size(); ++i)
        m_children[i]->draw(target, combinedTransform);
}

void Node::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
    //NOOP
}

sf::Transform Node::getTransform()
{
    return m_transform;
}

void Node::setTransform(sf::Transform newTransform)
{
    m_transform = newTransform;
}
