#ifndef SCENEMANAGERGAMEOVER_H
#define SCENEMANAGERGAMEOVER_H

#include "SceneManager.h"


class SceneManagerGameOver : public SceneManager
{
    public:
        SceneManagerGameOver(sf::RenderTarget * target, int windowWidth, int windowHeight);
        virtual ~SceneManagerGameOver();
        virtual bool IsFinished();

    protected:
        bool m_finished;
        virtual void Tick();

    private:
};

#endif // SCENEMANAGERGAMEOVER_H
