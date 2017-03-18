#ifndef DUNGEONCONFIGURATION_H
#define DUNGEONCONFIGURATION_H

#include "SceneManager/SceneManager.h"
#include "Battle/EnemyFactory.h"

class DungeonConfiguration
{
    public:
        DungeonConfiguration(int nrLevels, unsigned int seed, int dungeonId);
        virtual ~DungeonConfiguration();
        SceneManager* GetLevel(int id);
        int GetNrLevels();

        Entity* GetDungeonEnemy(int lvl);
        Entity* GetDungeonBoss(int lvl);

        void PlayMusic();

        int GetDungeonId();

    protected:
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
