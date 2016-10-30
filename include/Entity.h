#ifndef ENTITY_H
#define ENTITY_H

#include "TextureList.h"
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
        Entity(int exp = 0);
        virtual ~Entity();

        void PassTime(float Time);
        void FinishedTurn();

        //Deal dmg and play Attack animation
        void AttackEntity(Entity* target);
        void AttackEntity(Entity* target, Attack* attack);
        //Get damage and play get hit animation
        void GetHit(Attack* attack, Entity* attacker);


        bool IsAttackPhysical();

        bool IsDead();
        virtual void Died();

        //Getter/Setter
        float GetResistanceFor(BattleEnums::AttackType type);
        int GetAttribute(BattleEnums::Attribute attr);
        void InitAttribute(BattleEnums::Attribute attr, int value);
        void InitAllAttributes(int maxHp, int strength, int intelligence, int defense, int magicDefense);
        float GetTimeToNextAttack();
        virtual ControllType GetControllType();
        void CalculateMove(SceneManagerBattle* sm);
        void AddSkill(Skill* skill);

        void AddPassiveEffect(IPassiveEffect* eff);
        void RemovePassiveEffect(IPassiveEffect* eff);

        int GetExpToGive();

        std::vector<Skill>* GetSkillList();

        int GetTeamId();
        void SetTeamId(int id);

        sf::Sprite* GetBattleSprite();
        void SetBattleSprite(TextureList::TextureFiles newSprite);
        int GetNumberSprites();
    protected:
        std::vector<Skill> m_skills;
        //Map of all Passive Effects including the equiped Weapons and Armor with Priority, in which order they are called
        std::multimap<int, IPassiveEffect*> m_passiveEffects;

        std::map<BattleEnums::Attribute, int> m_attributes;
        std::map<BattleEnums::AttackType, float> m_resistances;
        int m_giveExp;

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
