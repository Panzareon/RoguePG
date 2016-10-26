#ifndef ENTITY_H
#define ENTITY_H

#include "Skill.h"
#include "IPassiveEffect.h"
#include "AIBase.h"
#include "Attack.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <map>

class SceneManagerBattle;

class Entity
{
    public:
        enum ControllType{ControllAI, ControllUser};
        Entity(int teamId);
        virtual ~Entity();

        void PassTime(float Time);
        void FinishedTurn();

        //Deal dmg and play Attack animation
        void AttackEntity(Entity* target);
        void AttackEntity(Entity* target, Attack* attack);
        //Get damage and play get hit animation
        void GetHit(Attack* attack, Entity* attacker);


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

        int GetTeamId();

        sf::Sprite* GetBattleSprite();
        int GetNumberSprites();
    protected:
        std::vector<Skill> m_skills;
        std::multimap<int, IPassiveEffect*> m_passiveEffects;

        std::map<BattleEnums::Attribute, int> m_attributes;

        int m_hp;
        float m_toNextAttack;

        ControllType m_controllTypeAtm;
        AIBase* m_AI;

        int m_teamId;

        sf::Sprite* m_battleSprite;
        int m_numberSprites;
    private:
};

#endif // ENTITY_H
