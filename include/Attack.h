#ifndef ATTACK_H
#define ATTACK_H

#include "Enums.h"
#include <vector>

class Attack
{
    public:
        Attack(int attack, BattleEnums::AttackType type, bool physical);
        virtual ~Attack();

        int m_dmg;
        std::vector<BattleEnums::AttackType> m_type;
        bool m_physical;

    protected:

    private:
};

#endif // ATTACK_H
