#ifndef MAPEVENTENEMY_H
#define MAPEVENTENEMY_H

#include "MapEvent.h"

#include "SceneGraph/Node.h"
#include "Map.h"
#include "Battle/Entity.h"

#include <cereal/types/base_class.hpp>

class MapEventEnemy : public MapEvent
{
    public:
        MapEventEnemy();
        MapEventEnemy(float movementSpeed, Enums::EnemyTypes type);
        virtual ~MapEventEnemy();
        void Init(Map* m, Node* node, std::vector<Entity*>* enemies);
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime);
        virtual void Activate();

        virtual void AfterLoad(SceneManager* sm);

        void FollowPlayer(bool follow, float followDistance = -1.0f, float followSpeed = -1.0f);

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            float xPos = m_node->getGlobalBoundingBox().left;
            float yPos = m_node->getGlobalBoundingBox().top;
            archive(cereal::base_class<MapEvent>( this ), m_type, xPos, yPos, m_movementSpeed, m_followPlayer, m_followDistanceSquared, m_followSpeed);
        }

        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<MapEvent>( this ), m_type, m_xLoadPos, m_yLoadPos, m_movementSpeed, m_followPlayer, m_followDistanceSquared, m_followSpeed);
        }

    protected:
        Node* m_node;
        Map* m_map;

        Enums::EnemyTypes m_type;

        float m_xLoadPos;
        float m_yLoadPos;

        float m_xMove;
        float m_yMove;
        float m_movementSpeed;

        float m_timeSinceChange;
        float m_maxTimeSinceChange;

        std::vector<Entity*>* m_enemies;

        bool m_followPlayer;
        float m_followDistanceSquared;
        float m_followSpeed;

    private:
};

#endif // MAPEVENTENEMY_H
