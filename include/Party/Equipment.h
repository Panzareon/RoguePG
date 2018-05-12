#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Battle/IPassiveEffect.h"
#include <map>
#include <set>
#include "Controller/Enums.h"
#include "Party/Item.h"
#include "Battle/SkillGenerator.h"
#include <memory>
#include <cereal/types/base_class.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/set.hpp>

class Entity;
class PartyMember;
class Skill;

class Equipment : public IPassiveEffect, public Item
{
    public:
        enum EquipmentPosition{MainHand, SideHand, Helmet, Armor, Ring, EQUIPMENT_POSITION_END};
        Equipment();
        Equipment(int ItemId, EquipmentPosition pos);

        virtual void OnEffectStart();
        virtual float GetResistance(float resistanceValue, BattleEnums::AttackType type);
        virtual void AttackEntity(Attack* att, Entity* attacker);

        virtual ~Equipment();
        virtual bool StaysAfterBattle();
        virtual bool IsStillActive();
        virtual float GetAttribute(float attributeValue, BattleEnums::Attribute attribute);


        virtual int GetActivationPriority();

        virtual bool IsEquipment();
        virtual void AddExp(int exp);
        virtual void AddExp(std::shared_ptr<PartyMember> target, int exp);
        EquipmentPosition GetEquipmentPosition();
        virtual int GetEquipmentExp();
        virtual float GetEquipmentExpPercent();
        virtual int GetLevel();
        virtual int GetEquipmentExp(std::shared_ptr<PartyMember> target);
        virtual float GetEquipmentExpPercent(std::shared_ptr<PartyMember> target);
        virtual int GetLevel(std::shared_ptr<PartyMember> target);
        virtual std::map<int, std::shared_ptr<Skill>>* GetSkillsToLearn();
        virtual bool CanLearnSomething(std::shared_ptr<PartyMember> target);
        bool IsEquipped();

        virtual void EquipTo(std::shared_ptr<PartyMember> target);
        virtual void UnEquip();
        std::shared_ptr<PartyMember> GetEquipTarget();

        SkillGenerator* GetSkillGenerator();

        void AddSkillsToLearn(int nr);
        void SetSkillStrength(float strength);
        void SetAttributeBuff(BattleEnums::Attribute attribute, int buff);
        void SetTypeResistance(BattleEnums::AttackType type, float multiplier);
        void AddAttackType(BattleEnums::AttackType type);

        void AddAdditionalEffect(std::shared_ptr<IPassiveEffect> effect);

        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();


        //Methods from IPassiveEffect with NOOP
        virtual void OnTurn(Entity* target);
        virtual void GetAttacked(Attack*, Entity*, Entity*);
        virtual float GetExp(float);
        virtual bool DeleteEffect();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<Item>( this ), m_position, m_attributeBuffs, m_typeResistance, m_attackTypes, m_skillsToLearn,
                    m_level, m_exp);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<Item>( this ), m_position, m_attributeBuffs, m_typeResistance, m_attackTypes, m_skillsToLearn,
                    m_level, m_exp);
            LoadItem();
        }
    protected:
        int NeededExp(int lvl);
        SkillGenerator m_skillGenerator;

        EquipmentPosition m_position;

        std::map<BattleEnums::Attribute, int> m_attributeBuffs;
        std::map<BattleEnums::AttackType, float> m_typeResistance;
        std::set<BattleEnums::AttackType> m_attackTypes;
        std::map<int, std::shared_ptr<Skill>> m_skillsToLearn;
        float m_skillStrength;

        void initExpAndLevel(std::shared_ptr<PartyMember> target);
        std::map<std::shared_ptr<PartyMember>,int> m_level;
        std::map<std::shared_ptr<PartyMember>,int> m_exp;

        int m_neededExpMultiplier;

        std::weak_ptr<PartyMember> m_target;

        virtual void LevelUp(std::shared_ptr<PartyMember> target);

        std::vector<std::shared_ptr<IPassiveEffect>> m_additionalEffects;
    private:
};

#endif // EQUIPMENT_H
