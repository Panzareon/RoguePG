#include "Battle/Attack.h"


Attack::Attack(int attack, bool physical, Entity* target)
{
    //ctor
    m_dmg = attack;
    m_physical = physical;
    m_target = target;
}

Attack::Attack(int attack, bool physical, Entity* target, BattleEnums::AttackType type)
{
    //ctor
    m_dmg = attack;
    m_type.insert(type);
    m_physical = physical;
    m_target = target;
}

Attack::~Attack()
{
    //dtor
}
