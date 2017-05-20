#ifndef IPASSIVEEFFECT_H
#define IPASSIVEEFFECT_H

#include "Controller/Enums.h"
#include <string>
#include "Controller/NamedItem.h"
#include <functional>
#include <vector>

class Attack;
class Entity;

class IPassiveEffect: public virtual NamedItem
{
    public:
        IPassiveEffect();
        virtual ~IPassiveEffect();
        virtual void OnEffectStart();
        //For Effects that trigger every turn
        virtual void OnTurn(Entity* target);
        virtual float GetResistance(float resistanceValue, BattleEnums::AttackType type) = 0;
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute) = 0;
        virtual void AttackEntity(Attack* att, Entity* attacker);
        virtual void GetAttacked(Attack* att, Entity* target, Entity* attacker) = 0;
        virtual float GetExp(float exp) = 0;
        virtual void OnBattleFinished(Entity* target);
        virtual bool ShowEnemyHealth(bool base);
        virtual float Movementspeed(float base);
        virtual float GetNeededMP(float base);

        virtual bool IsStillActive() = 0;
        virtual bool StaysAfterBattle() = 0;

        virtual int GetActivationPriority() = 0;

        virtual bool IsEquipment();

        virtual bool DeleteEffect();


        void AddOnTurnEffect(std::function<void(Entity*,IPassiveEffect*)>* onTurn);
        void AddAttack(std::function<void(Attack*, Entity*)>* attack);
        void AddGetNeededMp(std::function<float(float)>* getMp);
    protected:
        std::vector<std::function<void(Attack*, Entity*)>*> m_attack;
        std::vector<std::function<float(float)>*> m_getNeededMp;
        std::vector<std::function<void(Entity*,IPassiveEffect*)>*> m_onTurn;
    private:
};

#endif // IPASSIVEEFFECT_H
