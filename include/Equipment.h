#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "IPassiveEffect.h"
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
        Equipment(int ItemId, EquipmentPosition pos);

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
        EquipmentPosition GetEquipmentPosition();
        virtual int GetEquipmentExp();
        virtual int GetLevel();
        virtual int GetEquipmentExp(Entity* target);
        virtual int GetLevel(Entity* target);
        virtual std::map<int, std::shared_ptr<Skill>>* GetSkillsToLearn();
        virtual bool CanLearnSomething(Entity* target);
        bool IsEquiped();

        virtual void EquipTo(Entity* target);
        virtual void UnEquip();

        SkillGenerator* GetSkillGenerator();

        void AddSkillsToLearn(int nr);
        void SetSkillStrength(float strength);
        void SetAttributeBuff(BattleEnums::Attribute attribute, int buff);
        void SetTypeResistance(BattleEnums::AttackType type, float multiplier);
        void AddAttackType(BattleEnums::AttackType type);


        //Methods from IPassiveEffect with NOOP
        virtual void OnTurn();
        virtual void GetAttacked(Attack*, Entity*, Entity*);
        virtual float GetExp(float);

    protected:
        SkillGenerator m_skillGenerator;

        EquipmentPosition m_position;

        std::map<BattleEnums::Attribute, int> m_attributeBuffs;
        std::map<BattleEnums::AttackType, float> m_typeResistance;
        std::set<BattleEnums::AttackType> m_attackTypes;
        std::map<int, std::shared_ptr<Skill>> m_skillsToLearn;
        float m_skillStrength;

        std::map<Entity*,int> m_level;
        std::map<Entity*,int> m_exp;

        int m_neededExpMultiplier;

        Entity* m_target;

        virtual void LevelUp(Entity* target);
    private:
};

#endif // EQUIPMENT_H
