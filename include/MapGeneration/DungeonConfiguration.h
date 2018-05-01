#ifndef DUNGEONCONFIGURATION_H
#define DUNGEONCONFIGURATION_H

#include "SceneManager/SceneManager.h"
#include "Battle/EnemyFactory.h"

class DungeonConfiguration
{
    public:
        DungeonConfiguration();
        DungeonConfiguration(int nrLevels, unsigned int seed, int dungeonId);
        virtual ~DungeonConfiguration();
        void Init();
        SceneManager* GetLevel(int id);
        int GetNrLevels();
        int GetNrEnemies();
        int GetNrBossAdds();
        //Returns string of the received rewards
        std::string ClearedDungeon();

        Entity* GetDungeonEnemy(int lvl);
        Entity* GetDungeonBoss(int lvl);

        void PlayMusic();

        int GetDungeonId();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_nrLevels, m_dungeonId, m_seed);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(m_nrLevels, m_dungeonId, m_seed);
            Init();
        }
    protected:
        int m_dungeonType;
        int m_mapFillNr;
        Enums::GenerationType m_generationType;

        int m_nrLevels;
        int m_dungeonId;
        unsigned int m_seed;

        //Dungeon Enemies and Bosses with chance
        std::map<EnemyFactory::EnemyList, float> m_enemies;
        float m_enemiesSumChance;
        std::map<EnemyFactory::EnemyList, float> m_bosses;
        float m_bossesSumChance;

    private:
};

#endif // DUNGEONCONFIGURATION_H
