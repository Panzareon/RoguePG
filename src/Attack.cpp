#include "Attack.h"


Attack::Attack(int attack, bool physical)
{
    //ctor
    m_dmg = attack;
    m_physical = physical;
}

Attack::Attack(int attack, bool physical, BattleEnums::AttackType type)
{
    //ctor
    m_dmg = attack;
    m_type.insert(type);
    m_physical = physical;
}

Attack::~Attack()
{
    //dtor
}
