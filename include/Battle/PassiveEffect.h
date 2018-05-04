#ifndef PASSIVEEFFECT_H
#define PASSIVEEFFECT_H

#include "Controller/Enums.h"
#include "Controller/NamedItem.h"
#include "Attack.h"
#include "IPassiveEffect.h"
#include "EffectFactoryBase.h"
#include <functional>
class Entity;

//Class for Buffs and Debuffs
class PassiveEffect: public IPassiveEffect
{
    public:
        PassiveEffect(bool buff, int duration, NamedItem* causingEffect, bool staysAfterBattle = false);
        virtual ~PassiveEffect();

        virtual void OnTurn(Entity* entity);
        virtual float GetResistance(float resistanceValue, BattleEnums::AttackType type);
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute);
        virtual void GetAttacked(Attack* att, Entity* target, Entity* attacker);
        virtual int LooseHp(Attack* att, Entity* target, Entity* attacker, int baseAmount);
        virtual float GetExp(float exp);
        virtual void OnBattleFinished(Entity* target);
        virtual bool ShowEnemyHealth(bool base);
        virtual bool ShowCompleteMap(bool base);
        virtual float Movementspeed(float base);


        virtual bool IsStillActive();
        virtual bool StaysAfterBattle();
        virtual bool SetDuration(int duration);

        virtual int GetActivationPriority();
        void SetActivationPriority(int prio);
        void AddAttributeEffect(std::function<float(float,BattleEnums::Attribute)>* attributeFunction);
        void AddOnAttacked(std::function<void(Attack*, Entity*, Entity*)>* onAttacked);
        void AddOnLooseHp(std::function<int(Attack*, Entity*, Entity*, int)>* onLooseHp);
        void AddGetExp(std::function<float(float)>* getExp);
        void AddGetResistance(std::function<float(float,BattleEnums::AttackType)>* getResistance);
        void AddOnBattleFinished(std::function<void(Entity*)>* onBattleFinished);
        void SetMovementSpeedMultiplier(float mult);
        void SetShowEnemyHealth(bool show);
        void SetShowCompleteMap(bool show);

        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();

        void AddDescription(std::string descriptionName, std::vector<float>* descriptionValues);

    protected:
        NamedItem* m_causingEffect;
        bool m_buff;
        int m_prio;
        //Number of Turns this Effect lasts, -1 means forever
        int m_duration;
        bool m_staysAfterBattle;
        std::vector<std::function<float(float,BattleEnums::AttackType)>*> m_resistanceFunction;
        std::vector<std::function<float(float,BattleEnums::Attribute)>*> m_attributeFunction;
        std::vector<std::function<void(Attack*, Entity*, Entity*)>*> m_onAttacked;
        std::vector<std::function<int(Attack*, Entity*, Entity*, int)>*> m_onLooseHp;
        std::vector<std::function<float(float)>*> m_getExp;
        std::vector<std::function<void(Entity*)>*> m_onBattleFinished;

        float m_movementspeedMultiplier;
        bool m_showEnemyHealth;
        bool m_showCompleteMap;

        std::string m_additionalDescription;
        std::vector<float>* m_additionalDescriptionValues;
    private:
};

#endif // PASSIVEEFFECT_H
