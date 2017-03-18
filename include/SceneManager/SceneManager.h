#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SceneGraph/MenuNode.h"
#include "BattleAnimation/Animation.h"
#include <vector>

class SceneManager
{
    public:
        enum SceneManagerType {TypeBattle, TypeMainMenu, TypeVillage, TypeDefault};
        SceneManager();
        virtual ~SceneManager();
        virtual void NextTick();
        virtual void Draw();
        virtual bool IsFinished();
        virtual void AddSubMenu(MenuNode* menu);

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

        void AddAnimation(Animation* anim);
        Node* GetAnimationNode();

        virtual SceneManagerType GetType();
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

        float m_posx;
        float m_posy;

        int m_windowWidth;
        int m_windowHeight;

        std::vector<Animation*> m_animationList;
    private:
};

#endif // SCENEMANAGER_H
