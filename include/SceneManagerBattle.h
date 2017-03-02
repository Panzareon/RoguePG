#ifndef SCENEMANAGERBATTLE_H
#define SCENEMANAGERBATTLE_H

#include "SceneManager.h"
#include "DrawableNode.h"
#include "MenuNode.h"
#include "Enums.h"

#include "Party.h"
#include <vector>

class SceneManagerBattle : public SceneManager
{
    public:
        SceneManagerBattle(sf::RenderTarget * target, int windowWidth, int windowHeight);

        void UseOnTarget(std::function<void(BattleEnums::Target, Entity*)>* func, BattleEnums::Target defaultTarget, Entity* attacking);
        virtual ~SceneManagerBattle();
        virtual void Tick();
        virtual bool IsFinished();
        void Finished();

        void AddEnemy(Entity* enemy);
        std::vector<Entity*>* GetEnemies();

        void TurnIsFinished();

        bool IsEntityTargeted(Entity* entity);

        void AddSpriteForEntity(Entity* entity);
    protected:
        void CalculateNext();
        void ShowMenuForNext();

        void PassTime(float Time);

        DrawableNode* m_background;
        Node* m_eventLayer;

        Entity* m_next;
        bool m_nextFinished;
        float m_restoreHpPercent;
        float m_restoreMpPercent;

        Party* m_party;
        std::vector<Entity*> m_enemies;

        std::function<void(BattleEnums::Target, Entity*)>* m_useOnTarget;
        Entity* m_targetEntity;
        BattleEnums::Target m_targetType;
        unsigned int m_targetNr;

        std::vector<sf::Vector2f> m_posPerTeam;
        std::vector<sf::Vector2f> m_posChangePerTeam;
    private:
};

#endif // SCENEMANAGERBATTLE_H
