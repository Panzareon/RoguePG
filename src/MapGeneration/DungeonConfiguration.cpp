#include "MapGeneration/DungeonConfiguration.h"
#include "SceneManager/SceneManagerDungeon.h"
#include "Controller/GameController.h"
#include "Controller/MusicController.h"
#include "MapGeneration/MapFillDungeon.h"
#include "MapGeneration/MapFillIceDungeon.h"
#include "MapGeneration/MapFillDungeon2.h"

DungeonConfiguration::DungeonConfiguration()
{

}

DungeonConfiguration::DungeonConfiguration(int nrLevels, unsigned int seed, int dungeonId)
{
    //ctor
    m_nrLevels = nrLevels;
    m_seed = seed;
    m_dungeonId = dungeonId;

    Init();
}

DungeonConfiguration::~DungeonConfiguration()
{
    //dtor
}

void DungeonConfiguration::Init()
{
    //Init all Enemies
    if(m_dungeonId == 1)
    {
        m_enemies[EnemyFactory::EnemyListBat] = 10.0f;
        m_enemies[EnemyFactory::EnemyListWaterSlime] = 3.0f;

        m_bosses[EnemyFactory::EnemyListDeadWizard] = 3.0f;
        m_bosses[EnemyFactory::EnemyListStoneGolem] = 10.0f;
    }
    else if(m_dungeonId % 2 == 0)
    {
        m_enemies[EnemyFactory::EnemyListBat] = 3.0f;
        m_enemies[EnemyFactory::EnemyListWaterSlime] = 5.0f;
        m_enemies[EnemyFactory::EnemyListWindEye] = 10.0f;
        m_enemies[EnemyFactory::EnemyListStoneGolem] = 7.0f;

        m_bosses[EnemyFactory::EnemyListDeadWizard] = 10.0f;
    }
    else
    {
        m_enemies[EnemyFactory::EnemyListWaterSlime] = 5.0f;
        m_enemies[EnemyFactory::EnemyListStoneGolem] = 7.0f;
        m_enemies[EnemyFactory::EnemyListIceSpiritm] = 15.0f;

        m_bosses[EnemyFactory::EnemyListDeadWizard] = 3.0f;
        m_bosses[EnemyFactory::EnemyListIceGolem] = 10.0f;
    }

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

void DungeonConfiguration::PlayMusic()
{
    MusicController::GetInstance()->PlayMusic(MusicController::Cave);
}

SceneManager* DungeonConfiguration::GetLevel(int id)
{
    //create next Level
    SceneManagerDungeon* sceneManager;
    bool wallAbove;
    if(m_dungeonId == 1)
    {
        wallAbove = true;
        MapFillDungeon* mf = new MapFillDungeon();
        mf->InitItemChances(wallAbove);
        sceneManager = new SceneManagerDungeon(40,30, m_seed + id, id, this, mf, SceneManagerDungeon::Cave, wallAbove);
    }
    else if(m_dungeonId % 2 == 0)
    {
        wallAbove = true;
        MapFillDungeon* mf;
        if(m_dungeonId % 4 == 0)
        {
            mf = new MapFillDungeon();
        }
        else
        {
            mf = new MapFillDungeon2();
        }
        mf->InitItemChances(wallAbove);
        sceneManager = new SceneManagerDungeon(100,70, m_seed + id, id, this, mf, SceneManagerDungeon::Dungeon, wallAbove);
    }
    else
    {
        wallAbove = true;
        MapFillDungeon* mf = new MapFillDungeon2();
        mf->InitItemChances(wallAbove);
        sceneManager = new SceneManagerDungeon(100,70, m_seed + id, id, this, mf, SceneManagerDungeon::Dungeon, wallAbove);
    }
    return sceneManager;
}

int DungeonConfiguration::GetDungeonId()
{
    return m_dungeonId;
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
        {
            if(m_dungeonId == 1)
            {
                return EnemyFactory::GetEntity(it->first, lvl);
            }
            else
            {
                return EnemyFactory::GetEntity(it->first, lvl + 5);
            }
        }
    }
}

Entity* DungeonConfiguration::GetDungeonBoss(int lvl)
{
    float rand = (std::rand()/((float) RAND_MAX)) * m_bossesSumChance;

    for(auto it = m_bosses.begin(); it != m_bosses.end(); it++)
    {
        rand -= it->second;
        if(rand <= 0.0f)
        {
            if(m_dungeonId == 1)
            {
                return EnemyFactory::GetEntity(it->first, lvl);
            }
            else
            {
                return EnemyFactory::GetEntity(it->first, lvl + 5);
            }
        }
    }
}
