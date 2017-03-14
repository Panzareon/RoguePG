#ifndef SCENEMANAGERDUNGEON_H
#define SCENEMANAGERDUNGEON_H

#include "SceneManagerMoveable.h"
#include "MapGenerator.h"


class MapFill;
class DungeonConfiguration;

class SceneManagerDungeon: public SceneManagerMoveable
{
    public:
        enum GenerationType {Cave, Dungeon};
        SceneManagerDungeon(int tileWidth, int tileHeight, unsigned int seed, int lvlId, DungeonConfiguration* config, MapFill* mapFill, GenerationType type);
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


        DungeonConfiguration* m_dungeonConfig;

    private:
};

#endif // SCENEMANAGERDUNGEON_H
