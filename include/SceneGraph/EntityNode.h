#ifndef ENTITYNODE_H
#define ENTITYNODE_H

#include "AnimatedNode.h"
#include "EntityBarsNode.h"
#include "SceneManager/SceneManagerBattle.h"


class EntityNode : public AnimatedNode
{
    public:
        EntityNode(SceneManagerBattle* sm, Entity* entity);
        virtual ~EntityNode();
        virtual void draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const;
        void SetTargetedNode(Node* node);
        void SetEntity(Entity* entity);
        void ShowHpBar(bool show);
    protected:
        SceneManagerBattle* m_smb;
        Entity* m_entity;
        Node* m_targetedNode;
        EntityBarsNode* m_entityHpBar;
    private:
};

#endif // ENTITYNODE_H
