#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Node.h"
#include "Animation.h"
#include <vector>

class SceneManager
{
    public:
        SceneManager(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManager();
        virtual void NextTick();
        virtual bool IsFinished();

        void AddAnimation(Animation* anim);
        Node* GetAnimationNode();
    protected:
        virtual void Tick() = 0;
        void DrawScene();
        Node * m_mainNode;
        Node * m_animationNode;
        sf::RenderTarget* m_target;
        sf::Clock m_clock;
        sf::Time m_frameTime;

        float m_posx;
        float m_posy;

        int m_windowWidth;
        int m_windowHeight;

        std::vector<Animation*> m_animationList;
    private:
};

#endif // SCENEMANAGER_H
