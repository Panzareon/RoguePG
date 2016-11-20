#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <IPassiveEffect.h>
#include <map>
#include <set>
#include "Enums.h"
#include "Item.h"
#include "SkillGenerator.h"
#include <memory>

class Entity;
class Skill;

class Equipment : public IPassiveEffect, public Item
{
    public:
        enum EquipmentPosition{MainHand, SideHand, Helmet, Armor, Ring, EQUIPMENT_POSITION_END};
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
        virtual void AddExp(int exp);
        virtual void AddExp(Entity* target, int exp);
        virtual int GetEquipmentExp();
        virtual int GetLevel();
        virtual int GetEquipmentExp(Entity* target);
        virtual int GetLevel(Entity* target);
        virtual std::map<int, std::shared_ptr<Skill>>* GetSkillsToLearn();
        virtual bool CanLearnSomething(Entity* target);

        virtual void EquipTo(Entity* target);
        virtual void UnEquip();

        //Methods from IPassiveEffect with NOOP
        virtual void OnTurn();
        virtual void GetAttacked(Attack*, Entity*, Entity*);
        virtual float GetExp(float);

    protected:
        SkillGenerator m_skillGenerator;

        std::map<BattleEnums::Attribute, int> m_attributeBuffs;
        std::map<BattleEnums::AttackType, float> m_typeResistance;
        std::set<BattleEnums::AttackType> m_attackTypes;
        std::map<int, std::shared_ptr<Skill>> m_skillsToLearn;

        std::map<Entity*,int> m_level;
        std::map<Entity*,int> m_exp;

        int m_neededExpMultiplier;

        Entity* m_target;

        virtual void LevelUp(Entity* target);
    private:
};

#endif // EQUIPMENT_H
