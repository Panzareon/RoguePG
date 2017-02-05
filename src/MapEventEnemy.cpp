#include "MapEventEnemy.h"
#include <vector>
#include "Entity.h"
#include "EnemyFactory.h"
#include "GameController.h"

#define M_PI 3.1415926535897
#include <math.h>

MapEventEnemy::MapEventEnemy(Map* m, Node* node, float movementSpeed) : MapEvent(false)
{
    //ctor
    m_map = m;
    m_xMove = 0.0f;
    m_xMove = 0.0f;
    m_movementSpeed = movementSpeed;
    m_node = node;
    m_maxTimeSinceChange = 3.0f;
}

MapEventEnemy::~MapEventEnemy()
{
    //dtor
}

bool MapEventEnemy::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, sf::Time tickTime)
{
    if(m_timeSinceChange > m_maxTimeSinceChange){
        m_timeSinceChange = 0.0f;
        //Change Direction
        float angle = (rand() % 4) / 2.0f * M_PI;
        m_xMove = cos(angle);
        m_yMove = sin(angle);
    }
    m_timeSinceChange += tickTime.asSeconds();
    sf::FloatRect enemyBB = m_node->getGlobalBoundingBox();
    enemyBB.left += m_xMove * m_movementSpeed * tickTime.asSeconds();
    enemyBB.top += m_yMove * m_movementSpeed  * tickTime.asSeconds();
    if(!m_map->DoesCollide(enemyBB))
    {
        m_node->moveNode(m_xMove, m_yMove);
    }
    else
    {
        m_timeSinceChange += m_maxTimeSinceChange;
    }
    return rect.intersects(m_node->getGlobalBoundingBox());
}

void MapEventEnemy::Activate()
{
    std::vector<Entity*> enemies;
    //TODO: get Entities of this Map from somewhere else
    Entity* e = EnemyFactory::GetEntity(EnemyFactory::EnemyListBat);
    e->SetTeamId(1);
    enemies.push_back(e);
    e = EnemyFactory::GetEntity(EnemyFactory::EnemyListBat);
    e->SetTeamId(1);
    enemies.push_back(e);

    GameController::getInstance()->StartBattle(&enemies);

    m_finished = true;
    m_node->GetParent()->removeChild(m_node);
    delete m_node;
}
