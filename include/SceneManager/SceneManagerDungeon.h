#ifndef SCENEMANAGERDUNGEON_H
#define SCENEMANAGERDUNGEON_H

#include "SceneManagerMoveable.h"
#include "MapGeneration/MapGeneratorDungeon.h"
#include "MapGeneration/DungeonConfiguration.h"
#include "MapGeneration/MapFill.h"
#include "Controller/GameController.h"

#include <cereal/types/base_class.hpp>

class MapEventEnemy;
class MapEventHero;

class SceneManagerDungeon: public SceneManagerMoveable
{
    public:
        SceneManagerDungeon();
        SceneManagerDungeon(int tileWidth, int tileHeight, unsigned int seed, int lvlId, DungeonConfiguration* config, MapFill* mapFill, Enums::GenerationType type, bool wallAbove);
        virtual ~SceneManagerDungeon();
        void Generate(int tileWidth, int tileHeight, Enums::GenerationType type, bool loadSaved = false);
        void SpawnEnemy();
        void SpawnEnemy(int x, int y, float movementSpeed, float followSpeed, int followRange, Enums::EnemyTypes);

        void SpawnEnemy(MapEventEnemy* event, Enums::EnemyTypes type, float x, float y);

        void PlaceHeroSprite(MapEventHero* event);

        virtual void Tick();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<SceneManagerMoveable>( this ), m_seed, m_mapFill, m_width, m_height, m_type, m_lvlId, *m_dungeonConfig);
            if(version >= 1)
            {
                archive(m_wallAbove);
            }
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            DungeonConfiguration conf;
            archive(cereal::base_class<SceneManagerMoveable>( this ), m_seed, m_mapFill, m_width, m_height, m_type, m_lvlId, conf);
            if(version >= 1)
            {
                archive(m_wallAbove);
            }
            else
            {
                m_wallAbove = true;
            }
            m_dungeonConfig = new DungeonConfiguration(conf);
            GameController::getInstance()->SetDungeonConfiguration(m_dungeonConfig);
            m_generator.Init(&m_map, m_seed);
            m_mapFill->SetMap(&m_map);
            Generate(m_width, m_height, m_type, true);
            for(int i = 0; i < m_events.size(); i++)
            {
                m_events[i]->AfterLoad(this);
            }
        }
    protected:
        void PlaceChest(bool loadSaved);
        void PlaceHero();
        MapGeneratorDungeon m_generator;

        float m_timeToNextSpawn;
        int m_lvlId;

        std::unique_ptr<MapFill> m_mapFill;
        unsigned int m_seed;

        int m_width;
        int m_height;
        bool m_wallAbove;
        Enums::GenerationType m_type;



        DungeonConfiguration* m_dungeonConfig;

    private:
};

CEREAL_CLASS_VERSION(SceneManagerDungeon, 1);

#endif // SCENEMANAGERDUNGEON_H
