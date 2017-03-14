#include "DungeonConfiguration.h"
#include "SceneManagerDungeon.h"
#include "GameController.h"
#include "MusicController.h"
#include "MapFillDungeon.h"

DungeonConfiguration::DungeonConfiguration(int nrLevels, unsigned int seed)
{
    //ctor
    m_nrLevels = nrLevels;
    m_seed = seed;

    //Init all Enemies
    m_enemies[EnemyFactory::EnemyListBat] = 10.0f;
    m_enemies[EnemyFactory::EnemyListWaterSlime] = 10.0f;
    m_enemies[EnemyFactory::EnemyListWindEye] = 10.0f;
    m_enemies[EnemyFactory::EnemyListStoneGolem] = 2.0f;

    m_bosses[EnemyFactory::EnemyListDeadWizard] = 10.0f;

    m_enemiesSumChance = 0.0f;
    for(auto it = m_enemies.begin(); it != m_enemies.end(); it++)
    {
        m_enemiesSumChance += it->second;
    }

    m_bossesSumChance = 0.0f;
    for(auto it = m_bosses.begin(); it != m_bosses.end(); it++)
    {
        m_bossesSumChance += it->second;
    }
}

DungeonConfiguration::~DungeonConfiguration()
{
    //dtor
}

void DungeonConfiguration::PlayMusic()
{
    MusicController::GetInstance()->PlayMusic(MusicController::Cave);
}

SceneManager* DungeonConfiguration::GetLevel(int id)
{
    //create next Level
    GameController* controller = GameController::getInstance();

    SceneManagerDungeon* sceneManager = new SceneManagerDungeon(60,60, m_seed + id, id, this, new MapFillDungeon(), SceneManagerDungeon::Cave);
    return sceneManager;
}

int DungeonConfiguration::GetNrLevels()
{
    return m_nrLevels;
}

Entity* DungeonConfiguration::GetDungeonEnemy(int lvl)
{
    float rand = (std::rand()/((float) RAND_MAX)) * m_enemiesSumChance;

    for(auto it = m_enemies.begin(); it != m_enemies.end(); it++)
    {
        rand -= it->second;
        if(rand <= 0.0f)
            return EnemyFactory::GetEntity(it->first, lvl);
    }
}

Entity* DungeonConfiguration::GetDungeonBoss(int lvl)
{
    float rand = (std::rand()/((float) RAND_MAX)) * m_bossesSumChance;

    for(auto it = m_bosses.begin(); it != m_bosses.end(); it++)
    {
        rand -= it->second;
        if(rand <= 0.0f)
            return EnemyFactory::GetEntity(it->first, lvl);
    }
}
