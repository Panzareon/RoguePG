#include "MapGeneration/MapEventEnemy.h"
#include <vector>
#include "Battle/Entity.h"
#include "Battle/EnemyFactory.h"
#include "Controller/GameController.h"
#include "SceneManager/SceneManagerDungeon.h"

#define M_PI 3.1415926535897
#include <math.h>
#include <iostream>

MapEventEnemy::MapEventEnemy() : MapEvent(false)
{
    //ctor
    m_xMove = 0.0f;
    m_yMove = 0.0f;
    m_followPlayer = false;
    m_followSpeed = -1.0f;
    m_followDistanceSquared = -1.0f;
    m_maxTimeSinceChange = 3.0f;
}

MapEventEnemy::MapEventEnemy(float movementSpeed, Enums::EnemyTypes type)
{
    m_movementSpeed = movementSpeed;
    m_type = type;
    m_xMove = 0.0f;
    m_yMove = 0.0f;
    m_followPlayer = false;
    m_followSpeed = -1.0f;
    m_followDistanceSquared = -1.0f;
    m_maxTimeSinceChange = 3.0f;
}

MapEventEnemy::~MapEventEnemy()
{
    //dtor
    delete m_enemies;
}

void MapEventEnemy::Init(Map* m, Node* node, std::vector<Entity*>* enemies)
{
    m_map = m;
    m_node = node;
    m_enemies = enemies;
}

void MapEventEnemy::AfterLoad(SceneManager* sm)
{
    ((SceneManagerDungeon*)sm)->SpawnEnemy(this,m_type, m_xLoadPos, m_yLoadPos);
}


bool MapEventEnemy::ActivateAt(sf::FloatRect rect, Enums::Direction lookingDirection, float tickTime)
{
    bool mv = false;
    sf::FloatRect enemyBB = m_node->getGlobalBoundingBox();
    if(m_movementSpeed > 0.0f)
    {
        if(m_timeSinceChange > m_maxTimeSinceChange){
            m_timeSinceChange = 0.0f;
            //Change Direction
            float angle = (rand() % 4) / 2.0f * M_PI;
            m_xMove = cos(angle) * m_movementSpeed;
            m_yMove = sin(angle) * m_movementSpeed;
        }
        m_timeSinceChange += tickTime;
        mv = true;
    }
    if(m_followPlayer)
    {
        float xDist = rect.left - enemyBB.left;
        float yDist = rect.top - enemyBB.top;
        xDist *= xDist;
        yDist *= yDist;
        if(xDist + yDist < m_followDistanceSquared)
        {
            float x1 = (rect.left + rect.width / 2) / TileMap::GetTileWidth();
            float x2 = (enemyBB.left + enemyBB.width / 2) / TileMap::GetTileWidth();
            float y1 = (rect.top + rect.height / 2) / TileMap::GetTileWidth();
            float y2 = (enemyBB.top + enemyBB.height / 2) / TileMap::GetTileWidth();
            if(!m_map->DoesCollide(x1,y1,x2,y2))
            {
                m_xMove = (x1 - x2);
                m_yMove = (y1 - y2);
                float length = sqrt(m_xMove * m_xMove + m_yMove * m_yMove);
                //Prevent division by 0
                if(length == 0.0f)
                    length = 1.0f;
                m_xMove *= m_followSpeed/length;
                m_yMove *= m_followSpeed/length;
                mv = true;
            }
        }
    }
    if(mv)
    {
        sf::FloatRect testBB = enemyBB;
        testBB.left += m_xMove * tickTime;
        testBB.top += m_yMove * tickTime;
        if(!m_map->DoesCollide(testBB))
        {
            m_node->moveNode(m_xMove * tickTime, m_yMove * tickTime);
        }
        else
        {
            sf::FloatRect testBB = enemyBB;
            testBB.left += m_xMove * tickTime;
            if(!m_map->DoesCollide(testBB) && (m_xMove < -0.01f || m_xMove > 0.01f))
            {
                m_node->moveNode(m_xMove * tickTime, 0.0f);
            }
            else
            {
                sf::FloatRect testBB = enemyBB;
                testBB.top += m_yMove * tickTime;
                if(!m_map->DoesCollide(testBB) && (m_yMove < -0.01f || m_yMove > 0.01f))
                {
                    m_node->moveNode(0.0f, m_yMove * tickTime);
                }
                else
                {
                    m_timeSinceChange += m_maxTimeSinceChange;
                }
            }
        }
    }
    return rect.intersects(m_node->getGlobalBoundingBox());
}

void MapEventEnemy::Activate()
{

    #ifdef DEBUG_FLAG
    //DebugKey to not start battles
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {

    #endif // DEBUG_FLAG

    GameController::getInstance()->StartBattle(m_enemies);

    #ifdef DEBUG_FLAG

    }

    #endif // DEBUG_FLAG

    m_finished = true;
    m_node->GetParent()->removeChild(m_node);
    delete m_node;
}

void MapEventEnemy::FollowPlayer(bool follow, float followDistance, float followSpeed)
{
    m_followPlayer = follow;
    m_followDistanceSquared = followDistance * followDistance * TileMap::GetTileWidth() * TileMap::GetTileWidth();
    m_followSpeed = followSpeed;
}
