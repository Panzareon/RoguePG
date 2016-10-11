#ifndef ENTITYNODE_H
#define ENTITYNODE_H

#include "AnimatedNode.h"
#include "SceneManagerBattle.h"


class EntityNode : public AnimatedNode
{
    public:
        EntityNode(SceneManagerBattle* sm, Entity* entity);
        virtual ~EntityNode();
        virtual void draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const;
        void SetTargetedNode(Node* node);
    protected:
        SceneManagerBattle* m_smb;
        Entity* m_entity;
        Node* m_targetedNode;
    private:
};

#endif // ENTITYNODE_H
