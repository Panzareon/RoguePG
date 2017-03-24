#ifndef IPASSIVEEFFECT_H
#define IPASSIVEEFFECT_H

#include "Controller/Enums.h"
#include <string>
#include "Controller/NamedItem.h"
class Attack;
class Entity;

class IPassiveEffect: public virtual NamedItem
{
    public:
        IPassiveEffect();
        virtual ~IPassiveEffect();
        virtual void OnEffectStart();
        virtual void OnTurn(Entity* target) = 0;
        virtual float GetResistance(float resistanceValue, BattleEnums::AttackType type) = 0;
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute) = 0;
        virtual void AttackEntity(Attack* att, Entity* target, Entity* attacker) = 0;
        virtual void GetAttacked(Attack* att, Entity* target, Entity* attacker) = 0;
        virtual float GetExp(float exp) = 0;
        virtual void OnBattleFinished(Entity* target);
        virtual bool ShowEnemyHealth(bool base);
        virtual float Movementspeed(float base);

        virtual bool IsStillActive() = 0;
        virtual bool StaysAfterBattle() = 0;

        virtual int GetActivationPriority() = 0;

        virtual bool IsEquipment();

        virtual bool DeleteEffect();
    protected:
    private:
};

#endif // IPASSIVEEFFECT_H
