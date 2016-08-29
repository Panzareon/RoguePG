#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Node.h"

class SceneManager
{
    public:
        SceneManager(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManager();
        virtual void NextTick();
        virtual bool IsFinished();
    protected:
        virtual void Tick() = 0;
        void DrawScene();
        Node * m_mainNode;
        sf::RenderTarget* m_target;
        sf::Clock m_clock;
        sf::Time m_frameTime;

        float m_posx;
        float m_posy;

        int m_windowWidth;
        int m_windowHeight;
    private:
};

#endif // SCENEMANAGER_H
