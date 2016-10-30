#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <IPassiveEffect.h>
#include <map>
#include <set>
#include "Enums.h"
#include "Item.h"

class Entity;

class Equipment : public IPassiveEffect, public Item
{
    public:
        Equipment(int ItemId);

        virtual void OnEffectStart();
        virtual float GetResistance(float resistanceValue, BattleEnums::AttackType type);
        virtual void AttackEntity(Attack* att, Entity* target, Entity* attacker);

        virtual ~Equipment();
        virtual bool StaysAfterBattle();
        virtual bool IsStillActive();
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute);


        virtual int GetActivationPriority();

        virtual bool IsEquipment();

        virtual void EquipTo(Entity* target);
        virtual void UnEquip();

    protected:
        std::map<BattleEnums::Attribute, int> m_attributeBuffs;
        std::map<BattleEnums::AttackType, float> m_typeResistance;
        std::set<BattleEnums::AttackType> m_attackTypes;

        Entity* m_target;
    private:
};

#endif // EQUIPMENT_H
