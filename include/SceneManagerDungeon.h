#ifndef SCENEMANAGERDUNGEON_H
#define SCENEMANAGERDUNGEON_H

#include "SceneManagerMoveable.h"
#include "MapGenerator.h"


class SceneManagerDungeon: public SceneManagerMoveable
{
    public:
        SceneManagerDungeon(sf::RenderTarget * target, int windowWidth, int windowHeight, int tileWidth, int tileHeight, unsigned int seed);
        virtual ~SceneManagerDungeon();
        void SpawnEnemy();
    protected:

        MapGenerator m_generator;

        TileMap* m_tileMap;
        TileMap* m_tileMapItems;
        TileMap* m_tileMapAboveHero;
        TileMap* m_tileMapAboveWall;
        TileMap* m_tileMapWallDecoration;

        Node* m_belowHero;
        Node* m_eventLayer;
        Node* m_aboveHero;
    private:
};

#endif // SCENEMANAGERDUNGEON_H
