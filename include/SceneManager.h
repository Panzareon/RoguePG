#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "MenuNode.h"
#include "Animation.h"
#include <vector>

class SceneManager
{
    public:
        SceneManager(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManager();
        virtual void NextTick();
        virtual void Draw();
        virtual bool IsFinished();
        virtual void AddSubMenu(MenuNode* menu);

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns true if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

        void AddAnimation(Animation* anim);
        Node* GetAnimationNode();
    protected:
        void SetMemberStats();

        virtual void Tick() = 0;
        void DrawScene();
        void DrawGui();
        Node * m_mainNode;
        Node * m_animationNode;
        Node * m_gui;
        MenuNode* m_mainMenu;
        Node * m_memberStats;
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
