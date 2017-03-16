#include "EntityNode.h"

EntityNode::EntityNode(SceneManagerBattle* sm, Entity* entity): AnimatedNode(entity->GetBattleSprite(), entity->GetNumberSprites())
{
    //ctor
    m_smb = sm;
    m_entity = entity;
    entity->SetNode(this);
    m_targetedNode = nullptr;
}

EntityNode::~EntityNode()
{
    //dtor
    if(m_targetedNode != nullptr)
        delete m_targetedNode;
}

void EntityNode::SetTargetedNode(Node* node)
{
    if(m_targetedNode != nullptr)
        delete m_targetedNode;
    m_targetedNode = node;
}

void EntityNode::draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const
{
    //Hide if Entity is dead
    if(m_visible && m_entity != nullptr && !m_entity->IsDead())
    {
        // combine the parent transform with the node's one
        sf::Transform combinedTransform = parentTransform * m_transform;

        // let the node draw itself
        onDraw(target, combinedTransform);

        // draw its children
        for (std::size_t i = 0; i < m_children.size(); ++i)
            m_children[i]->draw(target, combinedTransform);

        if(m_smb->IsEntityTargeted(m_entity))
            if(m_targetedNode != nullptr)
                m_targetedNode->draw(target, combinedTransform);
    }
}
void EntityNode::SetEntity(Entity* entity)
{
    m_entity = entity;
    if(entity != nullptr)
    {
        entity->SetNode(this);
        SetSprite(entity->GetBattleSprite(), entity->GetNumberSprites());
    }
}
