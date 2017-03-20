#ifndef SCENEMANAGERSTATUS_H
#define SCENEMANAGERSTATUS_H

#include "SceneManager.h"
#include "SceneGraph/EntityBarsNode.h"
#include "AttributeNodesDisplay.h"

class SceneManagerStatus : AttributeNodesDisplay, public SceneManager
{
    public:
        SceneManagerStatus();
        virtual ~SceneManagerStatus();
        void ShowForEntity(PartyMember* partyMember);

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();
    protected:

        bool m_finished;

        TextNode* m_name;
        TextNode* m_level;
        TextNode* m_class;
        float m_expWidth;
        float m_expHeight;
        sf::RectangleShape* m_exp;
        EntityBarsNode* m_manaAndHealth;
        EntityNode* m_battleSprite;

    private:
};

#endif // SCENEMANAGERSTATUS_H
