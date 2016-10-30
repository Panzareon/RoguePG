#include "AnimationPartSprite.h"
#include "Animation.h"
#include "DrawableNode.h"
#include "GameController.h"

AnimationPartSprite::AnimationPartSprite(TextureList::TextureFiles sprite)
{
    //ctor
    m_moveX = 0.0f;
    m_moveY = 0.0f;
    m_angle = 0.0f;
    m_scale = 1.0f;
    m_texture = sprite;
}

AnimationPartSprite::~AnimationPartSprite()
{
    //dtor
}

void AnimationPartSprite::SetStartTransform(sf::Transform tr)
{
    m_startTransform = tr;
}

void AnimationPartSprite::SetTranslation(float moveX, float moveY)
{
    m_moveX = moveX;
    m_moveY = moveY;
}

void AnimationPartSprite::SetRotation(float angle)
{
    m_angle = angle;
}

void AnimationPartSprite::SetScaling(float scale)
{
    m_scale = scale;
}

void AnimationPartSprite::Start()
{
    m_sprite = new sf::Sprite();
    m_sprite->setTexture(*TextureList::getTexture(m_texture));
    m_node = new DrawableNode(m_sprite);
    m_node->setTransform(m_startTransform);

    Node* anim = GameController::getInstance()->GetActiveSceneManager()->GetAnimationNode();
    anim->addChild(m_node);
}

void AnimationPartSprite::Stop()
{
    m_node->GetParent()->removeChild(m_node);
    delete m_node;
}

void AnimationPartSprite::AnimationStep(float percent)
{
    sf::Transform trans = m_startTransform;
    float scale = (m_scale - 1.0f) * percent + 1.0f;
    sf::FloatRect r = m_sprite->getLocalBounds();
    trans.scale(scale, scale, r.width / 2, r.height / 2);
    trans.rotate(m_angle * percent);
    trans.translate(m_moveX * percent, m_moveY * percent);

    m_node->setTransform(trans);
}
