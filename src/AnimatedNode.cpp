#include "AnimatedNode.h"

sf::Shader* AnimatedNode::m_shader = 0;

AnimatedNode::AnimatedNode(sf::Sprite* sprite, int numberFrames)
{
    //ctor
    m_elapsedSeconds = 0.0f;
    m_sprite = *sprite;

    if(m_shader == 0)
    {
        m_shader = new sf::Shader();
        //TODO: get Filename from somewhere else
        m_shader->loadFromFile("shader/spriteSheetAnimation.frag", sf::Shader::Fragment);
    }
    m_numberFrames = numberFrames;
}

AnimatedNode::~AnimatedNode()
{
    //dtor
}
void AnimatedNode::Tick(float seconds)
{
    m_elapsedSeconds += seconds;
}

void AnimatedNode::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
    sf::RenderStates rs(transform);
    rs.shader = m_shader;
    m_shader->setParameter("frameId",(int)m_elapsedSeconds % m_numberFrames);
    m_shader->setParameter("numberFrames", m_numberFrames);
    target.draw(m_sprite, rs);
}
