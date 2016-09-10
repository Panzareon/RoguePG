#ifndef ENTITY_H
#define ENTITY_H

#include "Skill.h"
#include "PassiveEffect.h"
#include "AIBase.h"
#include <vector>
#include <map>

class SceneManagerBattle;

class Entity
{
    public:
        enum ControllType{ControllAI, ControllUser};
        Entity();
        virtual ~Entity();

        void PassTime(float Time);
        void FinishedTurn();

        //Deal dmg and play Attack animation
        void Attack(Entity* target);
        //Get damage and play get hit animation
        void GetHit(int attack, BattleEnums::AttackType type, bool physical);


        //returns Attack Type of basic attack
        BattleEnums::AttackType GetAttackType();
        bool IsAttackPhysical();

        bool IsDead();

        //Getter/Setter
        int GetAttribute(BattleEnums::Attribute attr);
        float GetTimeToNextAttack();
        virtual ControllType GetControllType();
        void CalculateMove(SceneManagerBattle* sm);
        void AddSkill(Skill* skill);

        std::vector<Skill>* GetSkillList();

    protected:
        std::vector<Skill> m_skills;
        std::multimap<int, PassiveEffect*> m_passiveEffects;

        std::map<BattleEnums::Attribute, int> m_attributes;

        int m_hp;
        float m_toNextAttack;

        ControllType m_controllTypeAtm;
        AIBase* m_AI;
    private:
};

#endif // ENTITY_H
