#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}
void Entity::PassTime(float Time)
{
    m_toNextAttack -= Time * m_speed;
}

float Entity::GetTimeToNextAttack()
{
    return m_toNextAttack / m_speed;
}
