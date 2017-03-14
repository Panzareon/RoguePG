#ifndef SCENEMANAGERDUNGEON_H
#define SCENEMANAGERDUNGEON_H

#include "SceneManagerMoveable.h"
#include "MapGenerator.h"


class MapFill;
class DungeonConfiguration;

class SceneManagerDungeon: public SceneManagerMoveable
{
    public:
        SceneManagerDungeon(int tileWidth, int tileHeight, unsigned int seed, int lvlId, DungeonConfiguration* config);
        virtual ~SceneManagerDungeon();
        void SpawnEnemy();
        void SpawnEnemy(int x, int y, int lvl, float movementSpeed, float followSpeed, int followRange, int nr);
        virtual void Tick();
    protected:
        void PlaceChest();
        void PlaceHero();
        MapGenerator m_generator;

        float m_timeToNextSpawn;
        int m_lvlId;

        MapFill* m_mapFill;

        TileMap* m_tileMap;
        TileMap* m_tileMapItems;
        TileMap* m_tileMapAboveHero;
        TileMap* m_tileMapAboveWall;
        TileMap* m_tileMapWallDecoration;

        Node* m_roomNumberNode;

        DungeonConfiguration* m_dungeonConfig;

        Node* m_belowHero;
        Node* m_eventLayer;
        Node* m_aboveHero;
    private:
};

#endif // SCENEMANAGERDUNGEON_H
