#include "AnimatedNode.h"
#include "ShaderList.h"

AnimatedNode::AnimatedNode(sf::Sprite* sprite, int numberFrames)
{
    //ctor
    m_elapsedSeconds = 0.0f;
    m_sprite = *sprite;

    //Load shader
    if(sf::Shader::isAvailable())
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
    if(sf::Shader::isAvailable())
    {
        rs.shader = m_shader;
        m_shader->setParameter("frameId",(int)(m_elapsedSeconds*4) % m_numberFrames);
        m_shader->setParameter("numberFrames", m_numberFrames);
    }
    target.draw(m_sprite, rs);
}

void AnimatedNode::SetDirection(Enums::Direction direction)
{
    int textureDeltaY = 0;
    switch(direction)
    {
    case Enums::East:
        textureDeltaY = 1;
        break;
    case Enums::South:
        textureDeltaY = 2;
        break;
    case Enums::West:
        textureDeltaY = 3;
        break;
    }
    sf::IntRect rect = m_sprite.getTextureRect();
    rect.top = textureDeltaY * rect.height;
    m_sprite.setTextureRect(rect);
}
