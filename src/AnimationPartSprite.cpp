#include "AnimationPartSprite.h"
#include "Animation.h"
#include "DrawableNode.h"
#include "GameController.h"

AnimationPartSprite::AnimationPartSprite(TextureList::TextureFiles sprite)
{
    //ctor
    m_texture = sprite;
    m_sprite = new sf::Sprite();
    m_sprite->setTexture(*TextureList::getTexture(m_texture));
    m_size = m_sprite->getLocalBounds();

    m_node = new DrawableNode(m_sprite);
}

AnimationPartSprite::~AnimationPartSprite()
{
    //dtor
}

sf::Sprite* AnimationPartSprite::GetSprite()
{
    return m_sprite;
}
