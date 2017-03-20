#ifndef ENTITY_H
#define ENTITY_H

#include "SceneGraph/TextureList.h"
#include "Battle/Skill.h"
#include "Battle/IPassiveEffect.h"
#include "AI/AIBase.h"
#include "Battle/Attack.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <map>
#include <memory>

class EntityNode;
class SceneManagerBattle;

class Entity
{
    public:
        enum ControllType{ControllAI, ControllUser};
        Entity(int exp = 0);
        virtual ~Entity();

        void PassTime(float Time);
        void StartBattle();
        void StartTurn();
        void FinishedTurn();

        void AttackWasEffective();
        //Deal dmg and play Attack animation
        void AttackEntity(Entity* target);
        void AttackEntity(Entity* target, Attack* attack);
        //Get damage and play get hit animation
        void GetHit(Attack* attack, Entity* attacker);

        void Heal(int hp);
        void RestoreMana(int mp);
        bool UseMp(int mp);


        bool IsAttackPhysical();

        bool IsDead();
        virtual void Died();

        //Getter/Setter
        float GetResistanceFor(BattleEnums::AttackType type);
        void SetResistance(BattleEnums::AttackType type, float value);
        int GetAttribute(BattleEnums::Attribute attr);
        void InitAttribute(BattleEnums::Attribute attr, int value);
        void InitAllAttributes(int maxHp, int maxMp, int strength, int intelligence, int defense, int magicDefense, int speed);
        float GetTimeToNextAttack();
        virtual ControllType GetControllType();
        void CalculateMove(SceneManagerBattle* sm);
        void AddSkill(Skill* skill);
        void AddSkill(std::shared_ptr<Skill> skill);

        void AddPassiveEffect(IPassiveEffect* eff);
        void RemovePassiveEffect(IPassiveEffect* eff);

        int GetExpToGive();

        std::vector<std::shared_ptr<Skill>>* GetSkillList();
        std::multimap<int, IPassiveEffect*>* GetPassiveEffects();

        int GetTeamId();
        void SetTeamId(int id);

        sf::Sprite* GetBattleSprite();
        void SetBattleSprite(TextureList::TextureFiles newSprite);
        int GetNumberSprites();

        int GetHp();
        int GetMp();
        float GetHpPercent();
        float GetMpPercent();
        void CheckMaxValues();
        virtual std::string GetName();
        void SetName(std::string name);

        //Sets the Node showing this Entity on Screen
        void SetNode(EntityNode* node);
        EntityNode* GetNode();
    protected:
        std::vector<std::shared_ptr<Skill>> m_skills;
        //Map of all Passive Effects including the equiped Weapons and Armor with Priority, in which order they are called
        std::multimap<int, IPassiveEffect*> m_passiveEffects;

        std::map<BattleEnums::Attribute, int> m_attributes;
        std::map<BattleEnums::AttackType, float> m_resistances;
        int m_giveExp;

        std::string m_name;

        int m_hp;
        int m_mp;
        float m_toNextAttack;

        ControllType m_controllTypeAtm;
        AIBase* m_AI;

        int m_teamId;

        sf::Sprite* m_battleSprite;
        int m_numberSprites;
        bool m_lastAttackWasEffective;

        EntityNode* m_node;
    private:
};

#endif // ENTITY_H
