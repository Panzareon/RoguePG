#ifndef MAPEVENTENEMY_H
#define MAPEVENTENEMY_H

#include <MapEvent.h>

#include "Node.h"
#include "Map.h"


class MapEventEnemy : public MapEvent
{
    public:
        MapEventEnemy(Map* m, Node* node, float movementSpeed);
        virtual ~MapEventEnemy();
        virtual bool ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, sf::Time tickTime);
        virtual void Activate();

    protected:
        Node* m_node;
        Map* m_map;

        float m_xMove;
        float m_yMove;
        float m_movementSpeed;

        float m_timeSinceChange;
        float m_maxTimeSinceChange;

    private:
};

#endif // MAPEVENTENEMY_H
