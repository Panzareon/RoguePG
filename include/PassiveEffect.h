#ifndef PASSIVEEFFECT_H
#define PASSIVEEFFECT_H

#include "Enums.h"
#include <functional>
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
        void AddOnTurnEffect(std::function<void(Entity*,PassiveEffect*)>* onTurn);
        void AddAttributeEffect(std::function<float(float,BattleEnums::Attribute)>* attributeFunction);

    protected:
        Entity* m_target;
        bool m_buff;
        int m_prio;
        //Number of Turns this Effect lasts, -1 means forever
        int m_duration;
        std::function<void(Entity*,PassiveEffect*)>* m_onTurn;
        std::function<float(float,BattleEnums::Attribute)>* m_attributeFunction;
    private:
};

#endif // PASSIVEEFFECT_H
