#ifndef PASSIVEEFFECT_H
#define PASSIVEEFFECT_H

#include "Enums.h"
class Entity;

//Class for Buffs and Debuffs
class PassiveEffect
{
    public:
        PassiveEffect(Entity* target, bool buff, int duration);
        virtual ~PassiveEffect();

        //For Effects that trigger every turn
        virtual void OnTurn();
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute);
        bool IsStillActive();

        int GetActivationPriority();

    protected:
        Entity* m_target;
        bool m_buff;
        int m_prio;
        //Number of Turns this Effect lasts, -1 means forever
        int m_duration;
    private:
};

#endif // PASSIVEEFFECT_H
