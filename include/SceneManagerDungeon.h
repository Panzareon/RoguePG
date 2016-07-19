#ifndef SCENEMANAGERDUNGEON_H
#define SCENEMANAGERDUNGEON_H

#include "SceneManager.h"
#include "Map.h"
#include "MapGenerator.h"


class SceneManagerDungeon: public SceneManager
{
    public:
        SceneManagerDungeon();
        virtual ~SceneManagerDungeon();
    protected:
        Map m_map;
        MapGenerator m_generator;

        TileMap* m_tileMap;
        TileMap* m_tileMapWall;
        TileMap* m_tileMapItems;
        TileMap* m_tileMapAboveHero;
        TileMap* m_tileMapAboveWall;

        Node* m_belowHero;
        Node* m_eventLayer;
        Node* m_aboveHero;
    private:
};

#endif // SCENEMANAGERDUNGEON_H
