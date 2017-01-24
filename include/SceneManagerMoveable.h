#ifndef SCENEMANAGERMOVEABLE_H
#define SCENEMANAGERMOVEABLE_H

#include <SceneManager.h>
#include "Map.h"
#include "AnimatedNode.h"
#include "MapEvent.h"
#include <vector>


class SceneManagerMoveable : public SceneManager
{
    public:
        SceneManagerMoveable(sf::RenderTarget * target, int windowWidth, int windowHeight, int tileWidth, int tileHeight);
        virtual ~SceneManagerMoveable();
        virtual void Tick();
    protected:
        Map m_map;
        AnimatedNode* m_hero;
        Enums::Direction m_heroDirection;
        std::vector<MapEvent*> m_events;

        int m_minViewPosX;
        int m_minViewPosY;
        int m_maxViewPosX;
        int m_maxViewPosY;
    private:
};

#endif // SCENEMANAGERMOVEABLE_H
