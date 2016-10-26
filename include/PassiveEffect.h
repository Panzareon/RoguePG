#ifndef PASSIVEEFFECT_H
#define PASSIVEEFFECT_H

#include "Enums.h"
#include "Attack.h"
#include "IPassiveEffect.h"
#include <functional>
class Entity;

//Class for Buffs and Debuffs
class PassiveEffect: public IPassiveEffect
{
    public:
        PassiveEffect(Entity* target, bool buff, int duration, bool staysAfterBattle = false);
        virtual ~PassiveEffect();

        //For Effects that trigger every turn
        virtual void OnTurn();
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute);
        virtual void AttackEntity(Attack* att, Entity* target, Entity* attacker);
        virtual void GetAttacked(Attack* att, Entity* target, Entity* attacker);
        virtual float GetExp(float exp);
        virtual bool IsStillActive();
        virtual bool StaysAfterBattle();

        virtual int GetActivationPriority();
        void AddOnTurnEffect(std::function<void(Entity*,PassiveEffect*)>* onTurn);
        void AddAttributeEffect(std::function<float(float,BattleEnums::Attribute)>* attributeFunction);
        void AddAttack(std::function<void(Attack*, Entity*, Entity*)>* attack);
        void AddOnAttacked(std::function<void(Attack*, Entity*, Entity*)>* onAttacked);
        void AddGetExp(std::function<float(float)>* getExp);

    protected:
        Entity* m_target;
        bool m_buff;
        int m_prio;
        //Number of Turns this Effect lasts, -1 means forever
        int m_duration;
        bool m_staysAfterBattle;
        std::function<void(Entity*,PassiveEffect*)>* m_onTurn;
        std::function<float(float,BattleEnums::Attribute)>* m_attributeFunction;
        std::function<void(Attack*, Entity*, Entity*)>* m_attack;
        std::function<void(Attack*, Entity*, Entity*)>* m_onAttacked;
        std::function<float(float)>* m_getExp;
    private:
};

#endif // PASSIVEEFFECT_H
