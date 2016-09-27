#ifndef ENTITYNODE_H
#define ENTITYNODE_H

#include "AnimatedNode.h"
#include "SceneManagerBattle.h"


class EntityNode : public AnimatedNode
{
    public:
        EntityNode(sf::Sprite* sprite, SceneManagerBattle* sm, Entity* entity);
        virtual ~EntityNode();
    protected:
        SceneManagerBattle* m_smb;
        Entity* m_entity;
    private:
};

#endif // ENTITYNODE_H
