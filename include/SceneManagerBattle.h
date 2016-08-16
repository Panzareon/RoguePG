#ifndef SCENEMANAGERBATTLE_H
#define SCENEMANAGERBATTLE_H

#include "SceneManager.h"
#include "DrawableNode.h"

#include "Party.h"
#include <vector>

class SceneManagerBattle : public SceneManager
{
    public:
        SceneManagerBattle(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerBattle();
        virtual void Tick();
    protected:
        void CalculateNext();

        void PassTime(float Time);

        DrawableNode* m_background;
        Node* m_eventLayer;
        Node* m_gui;

        Entity* m_next;

        Party* m_party;
        std::vector<Entity*> m_enemies;
    private:
};

#endif // SCENEMANAGERBATTLE_H
