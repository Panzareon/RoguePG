#ifndef SCENEMANAGERCHOOSEHERO_H
#define SCENEMANAGERCHOOSEHERO_H

#include "SceneManager.h"
#include "SceneGraph/TextNode.h"
#include "Party/CharacterClass.h"

class SceneManagerChooseHero : public SceneManager
{
    public:
        SceneManagerChooseHero();
        virtual ~SceneManagerChooseHero();

        virtual void Tick();
        virtual bool IsFinished();

        void ChooseNext();
        void ChoosePrev();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:
        void StartDungeon();
        void ShowForCharacterClass();

        std::vector<Node*> m_classNodes;
        std::map<CharacterClass::CharacterClassEnum, bool> m_classAvailable;
        TextNode* m_textNode;
        TextNode* m_description;
        Node* m_cursor;

        int m_selected;

        bool m_finished;
    private:
};

#endif // SCENEMANAGERCHOOSEHERO_H
