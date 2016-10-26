#include "AnimatedNode.h"
#include "ShaderList.h"

AnimatedNode::AnimatedNode(sf::Sprite* sprite, int numberFrames)
{
    //ctor
    m_elapsedSeconds = 0.0f;
    m_sprite = *sprite;

    //Load shader
    m_shader = ShaderList::GetShader(ShaderList::AnimatedSpriteShader);

    //Set number of Frames to circle through
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
