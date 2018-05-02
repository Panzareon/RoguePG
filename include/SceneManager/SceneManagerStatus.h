#ifndef SCENEMANAGERSTATUS_H
#define SCENEMANAGERSTATUS_H

#include "SceneManager.h"
#include "SceneGraph/EntityBarsNode.h"
#include "AttributeNodesDisplay.h"
#include "SceneGraph/AnimatedNode.h"

class SceneManagerStatus : AttributeNodesDisplay, public SceneManager
{
    public:
        SceneManagerStatus();
        virtual ~SceneManagerStatus();
        void ShowForEntity(PartyMember* partyMember);

        void SetDescription(std::string str);
        void DeselectSkills();
        void SelectSkills();
        void DeselectPassiveEffects();
        void MoveSkillPosition(int from, int to);

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();
        virtual SceneManagerType GetType();
    protected:

        int m_selectedMember;

        std::vector<std::shared_ptr<PartyMember> >* m_partyMember;

        bool m_finished;

        TextNode* m_name;
        TextNode* m_level;
        TextNode* m_class;
        TextNode* m_description;
        float m_expWidth;
        float m_expHeight;
        sf::RectangleShape* m_exp;
        EntityBarsNode* m_manaAndHealth;
        AnimatedNode* m_battleSprite;

        MenuNode* m_skills;
        bool m_skillsActive;
        MenuNode* m_passiveEffects;
        bool m_passiveEffectsActive;

    private:
};

#endif // SCENEMANAGERSTATUS_H
