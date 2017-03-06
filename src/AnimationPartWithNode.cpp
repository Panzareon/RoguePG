#include "AnimationPartWithNode.h"
#include "GameController.h"

AnimationPartWithNode::AnimationPartWithNode()
{
    //ctor
    m_moveX = 0.0f;
    m_moveY = 0.0f;
    m_angle = 0.0f;
    m_scale = 1.0f;
}

AnimationPartWithNode::~AnimationPartWithNode()
{
    //dtor
}


void AnimationPartWithNode::SetStartTransform(sf::Transform tr)
{
    m_startTransform = tr;
}

void AnimationPartWithNode::SetTranslation(float moveX, float moveY)
{
    m_moveX = moveX;
    m_moveY = moveY;
}

void AnimationPartWithNode::SetRotation(float angle)
{
    m_angle = angle;
}

void AnimationPartWithNode::SetScaling(float scale)
{
    m_scale = scale;
}

void AnimationPartWithNode::Start()
{
    m_node->setTransform(m_startTransform);

    Node* anim = GameController::getInstance()->GetActiveSceneManager()->GetAnimationNode();
    anim->addChild(m_node);
}

void AnimationPartWithNode::Stop()
{
    m_node->GetParent()->removeChild(m_node);
    delete m_node;
}

void AnimationPartWithNode::AnimationStep(float percent)
{
    sf::Transform trans = m_startTransform;
    float scale = (m_scale - 1.0f) * percent + 1.0f;
    trans.scale(scale, scale, m_size.width / 2, m_size.height / 2);
    trans.rotate(m_angle * percent);
    trans.translate(m_moveX * percent, m_moveY * percent);

    m_node->setTransform(trans);
}
