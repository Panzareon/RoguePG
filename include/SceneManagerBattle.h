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

        void UseOnTarget(std::function<void(BattleEnums::Target, Entity*)>* func, BattleEnums::Target defaultTarget);
        virtual ~SceneManagerBattle();
        virtual void Tick();
        virtual bool IsFinished();

        void AddEnemy(Entity* enemy);

        void TurnIsFinished();
        void AddSubMenu(MenuNode* menu);
    protected:
        void CalculateNext();
        void ShowMenuForNext();

        void PassTime(float Time);

        DrawableNode* m_background;
        Node* m_eventLayer;
        Node* m_gui;

        MenuNode* m_mainMenu;

        Entity* m_next;

        Party* m_party;
        std::vector<Entity*> m_enemies;

        std::function<void(BattleEnums::Target, Entity*)>* m_useOnTarget;
        Entity* m_targetEntity;
        BattleEnums::Target m_targetType;
        int m_targetNr;
    private:
};

#endif // SCENEMANAGERBATTLE_H
