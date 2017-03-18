#ifndef ATTACK_H
#define ATTACK_H

#include "Controller/Enums.h"
#include <set>

class Attack
{
    public:
        Attack(int attack, bool physical);
        Attack(int attack, bool physical, BattleEnums::AttackType type);
        virtual ~Attack();

        int m_dmg;
        std::set<BattleEnums::AttackType> m_type;
        bool m_physical;

    protected:

    private:
};

#endif // ATTACK_H
