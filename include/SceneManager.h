#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Node.h"

class SceneManager
{
    public:
        SceneManager();
        virtual ~SceneManager();

        void DrawScene(sf::RenderTarget& target);
    protected:
        Node * m_mainNode;
    private:
};

#endif // SCENEMANAGER_H
