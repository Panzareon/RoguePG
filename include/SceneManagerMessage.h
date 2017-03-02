#ifndef SCENEMANAGERMESSAGE_H
#define SCENEMANAGERMESSAGE_H

#include "SceneManager.h"
#include "TextNode.h"
#include <functional>


class SceneManagerMessage : public SceneManager
{
    public:
        SceneManagerMessage(sf::RenderTarget * target, int windowWidth, int windowHeight, std::string toDisplay);
        virtual ~SceneManagerMessage();

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

        void OnAccept(std::function<void()> func);

    protected:
        TextNode* m_text;
        std::function<void()> m_onAccept;

        bool m_finished;
    private:
};

#endif // SCENEMANAGERMESSAGE_H
