#ifndef SCENEMANAGERDUNGEON_H
#define SCENEMANAGERDUNGEON_H

#include "SceneManagerMoveable.h"
#include "MapGeneration/MapGeneratorDungeon.h"
#include "MapGeneration/DungeonConfiguration.h"
#include "MapGeneration/MapFill.h"

#include <cereal/types/base_class.hpp>


class SceneManagerDungeon: public SceneManagerMoveable
{
    public:
        enum GenerationType {Cave, Dungeon};
        SceneManagerDungeon();
        SceneManagerDungeon(int tileWidth, int tileHeight, unsigned int seed, int lvlId, DungeonConfiguration* config, MapFill* mapFill, GenerationType type);
        virtual ~SceneManagerDungeon();
        void Generate(int tileWidth, int tileHeight, GenerationType type);
        void SpawnEnemy();
        void SpawnEnemy(int x, int y, int lvl, float movementSpeed, float followSpeed, int followRange, int nr);
        virtual void Tick();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<SceneManagerMoveable>( this ), m_seed, m_mapFill, m_width, m_height, m_type, m_lvlId, *m_dungeonConfig);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            DungeonConfiguration conf;
            archive(cereal::base_class<SceneManagerMoveable>( this ), m_seed, m_mapFill, m_width, m_height, m_type, m_lvlId, conf);
            m_dungeonConfig = new DungeonConfiguration(conf);
            m_generator.Init(&m_map, m_seed);
            m_mapFill->SetMap(&m_map);
            Generate(m_width, m_height, m_type);
        }
    protected:
        void PlaceChest();
        void PlaceHero();
        MapGeneratorDungeon m_generator;

        float m_timeToNextSpawn;
        int m_lvlId;

        std::unique_ptr<MapFill> m_mapFill;
        unsigned int m_seed;

        int m_width;
        int m_height;
        GenerationType m_type;


        DungeonConfiguration* m_dungeonConfig;

    private:
};

#endif // SCENEMANAGERDUNGEON_H
