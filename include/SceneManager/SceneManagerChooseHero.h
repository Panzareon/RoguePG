#ifndef SCENEMANAGERCHOOSEHERO_H
#define SCENEMANAGERCHOOSEHERO_H

#include "SceneManager.h"
#include "SceneGraph/TextNode.h"

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
        void ShowForCharacterClass();

        sf::Sprite* m_classSprite;
        TextNode* m_textNode;
        int m_selected;

        bool m_finished;
    private:
};

#endif // SCENEMANAGERCHOOSEHERO_H
