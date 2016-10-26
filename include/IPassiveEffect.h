#ifndef IPASSIVEEFFECT_H
#define IPASSIVEEFFECT_H

#include "Enums.h"
class Attack;
class Entity;

class IPassiveEffect
{
    public:
        IPassiveEffect();
        virtual ~IPassiveEffect();
        virtual void OnTurn() = 0;
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute) = 0;
        virtual void AttackEntity(Attack* att, Entity* target, Entity* attacker) = 0;
        virtual void GetAttacked(Attack* att, Entity* target, Entity* attacker) = 0;
        virtual float GetExp(float exp) = 0;
        virtual bool IsStillActive() = 0;
        virtual bool StaysAfterBattle() = 0;

        virtual int GetActivationPriority() = 0;
    protected:
    private:
};

#endif // IPASSIVEEFFECT_H
