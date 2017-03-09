#ifndef DUNGEONCONFIGURATION_H
#define DUNGEONCONFIGURATION_H

#include "SceneManager.h"
#include "EnemyFactory.h"

class DungeonConfiguration
{
    public:
        DungeonConfiguration(int nrLevels, unsigned int seed);
        virtual ~DungeonConfiguration();
        SceneManager* GetLevel(int id);
        int GetNrLevels();

        Entity* GetDungeonEnemy(int lvl);
        Entity* GetDungeonBoss(int lvl);

        void PlayMusic();

    protected:
        int m_nrLevels;
        unsigned int m_seed;

        //Dungeon Enemies and Bosses with chance
        std::map<EnemyFactory::EnemyList, float> m_enemies;
        float m_enemiesSumChance;
        std::map<EnemyFactory::EnemyList, float> m_bosses;
        float m_bossesSumChance;

    private:
};

#endif // DUNGEONCONFIGURATION_H
