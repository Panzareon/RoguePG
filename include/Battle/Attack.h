#ifndef ATTACK_H
#define ATTACK_H

#include "Controller/Enums.h"
#include <set>

class Entity;

class Attack
{
    public:
        Attack(int attack, bool physical, Entity* target);
        Attack(int attack, bool physical, Entity* target, BattleEnums::AttackType type);
        virtual ~Attack();

        int m_dmg;
        std::set<BattleEnums::AttackType> m_type;
        bool m_physical;
        Entity* m_target;

        int m_finalDmg;

    protected:

    private:
};

#endif // ATTACK_H
