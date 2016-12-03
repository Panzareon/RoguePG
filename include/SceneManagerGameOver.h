#ifndef SCENEMANAGERGAMEOVER_H
#define SCENEMANAGERGAMEOVER_H

#include "SceneManager.h"


class SceneManagerGameOver : public SceneManager
{
    public:
        SceneManagerGameOver(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerGameOver();
        virtual void Tick();
        virtual bool IsFinished();

    protected:
        bool m_finished;

    private:
};

#endif // SCENEMANAGERGAMEOVER_H
