#include "EntityNode.h"

EntityNode::EntityNode(sf::Sprite* sprite, SceneManagerBattle* sm, Entity* entity): AnimatedNode(sprite)
{
    //ctor
    m_smb = sm;
    m_entity = entity;
}

EntityNode::~EntityNode()
{
    //dtor
}
