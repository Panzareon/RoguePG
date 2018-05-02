#ifndef SCENEMANAGERBATTLE_H
#define SCENEMANAGERBATTLE_H

#include "SceneManager.h"
#include "SceneGraph/DrawableNode.h"
#include "SceneGraph/MenuNode.h"
#include "SceneGraph/TextNode.h"
#include "Controller/Enums.h"

#include "Party/Party.h"
#include <vector>

class EntityNode;

class SceneManagerBattle : public SceneManager
{
    public:
        SceneManagerBattle();

        void UseOnTarget(std::function<void(BattleEnums::Target, Entity*)>* func, BattleEnums::Target defaultTarget, Entity* attacking);
        virtual ~SceneManagerBattle();
        virtual void Tick();
        virtual bool IsFinished();
        void Finished();

        void AddEnemy(Entity* enemy);
        std::vector<Entity*>* GetEnemies();
        void UpdatePlayerSprites();

        void TurnIsFinished();

        bool IsEntityTargeted(Entity* entity);

        void AddSpriteForEntity(Entity* entity, bool hpBar);

        void SetDescription(std::string str);
        void MoveSkillPosition(int from, int to);

        virtual SceneManagerType GetType();
    protected:
        void CheckBattleEnd();
        bool m_finished;

        void CalculateNext();
        void ShowMenuForNext();

        Entity* m_lastEnemyTargeted;
        Entity* m_lastHeroTargeted;

        void PassTime(float Time);

        DrawableNode* m_background;
        Node* m_eventLayer;
        TextNode* m_description;

        Entity* m_next;
        bool m_nextFinished;
        bool m_showHpBar;
        float m_restoreHpPercent;
        float m_restoreMpPercent;

        Party* m_party;
        std::vector<Entity*> m_enemies;

        float m_timeHeight;
        Node* m_timeDisplay;
        std::vector<TextNode*> m_partyMemberTime;
        std::vector<TextNode*> m_enemyTime;
        Entity* m_dontInterpolate;

        std::vector<std::vector<EntityNode*> > m_entityNodes;

        std::function<void(BattleEnums::Target, Entity*)>* m_useOnTarget;
        Entity* m_targetEntity;
        BattleEnums::Target m_targetType;
        unsigned int m_targetNr;

        std::vector<sf::Vector2f> m_posPerTeam;
        std::vector<sf::Vector2f> m_posChangePerTeam;

        bool m_expGiven;
    private:
};

#endif // SCENEMANAGERBATTLE_H
