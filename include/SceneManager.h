#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Node.h"

class SceneManager
{
    public:
        SceneManager(sf::RenderTarget * target);
        virtual ~SceneManager();
        virtual void NextTick();
    protected:
        virtual void Tick() = 0;
        void DrawScene();
        Node * m_mainNode;
        sf::RenderTarget* m_target;
        sf::Clock m_clock;
        sf::Time m_frameTime;

        float m_posx;
        float m_posy;
    private:
};

#endif // SCENEMANAGER_H
