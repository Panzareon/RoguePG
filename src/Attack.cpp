#include "Attack.h"

Attack::Attack(int attack, BattleEnums::AttackType type, bool physical)
{
    //ctor
    m_dmg = attack;
    m_type.push_back(type);
    m_physical = physical;
}

Attack::~Attack()
{
    //dtor
}
