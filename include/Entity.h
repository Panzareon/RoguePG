#ifndef ENTITY_H
#define ENTITY_H

#include "Skill.h"
#include "AIBase.h"
#include <vector>

class Entity
{
    public:
        enum AttackType{Physical, Fire, Water, Earth, Air};
        enum ControllType{ControllAI, ControllUser};
        Entity();
        virtual ~Entity();

        void PassTime(float Time);
        void FinishedTurn();

        //Play attack animation
        void Attack();
        //Get damage and play get hit animation
        void GetHit(int attack, AttackType type);


        //returns Attack Type of basic attack
        AttackType GetAttackType();

        bool IsDead();

        //Getter/Setter
        int GetAttack();
        float GetTimeToNextAttack();
        virtual ControllType GetControllType();
        void CalculateMove();

        std::vector<Skill>* GetSkillList();

    protected:
        std::vector<Skill> m_skills;

        int m_maxHp;
        int m_hp;
        int m_attack;
        int m_defense;
        int m_speed;
        float m_toNextAttack;

        ControllType m_controllTypeAtm;
        AIBase* m_AI;
    private:
};

#endif // ENTITY_H
