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
        m_generationType = Enums::Cave;
        m_dungeonType = 0;
        m_mapFillNr = 0;

        m_enemies[EnemyFactory::EnemyListBat] = 10.0f;
        m_enemies[EnemyFactory::EnemyListWaterSlime] = 3.0f;

        m_bosses[EnemyFactory::EnemyListDeadWizard] = 3.0f;
        m_bosses[EnemyFactory::EnemyListStoneGolem] = 10.0f;
    }
    else
    {
        m_dungeonType = rand() % 2;
        if(m_dungeonType == 0)
        {
            if(rand() % 2 == 0)
            {
                m_generationType = Enums::Cave;
            }
            else
            {
                m_generationType = Enums::Dungeon;
            }
            m_mapFillNr = rand() % 2;
            m_enemies[EnemyFactory::EnemyListBat] = 3.0f;
            m_enemies[EnemyFactory::EnemyListWaterSlime] = 5.0f;
            m_enemies[EnemyFactory::EnemyListWindEye] = 10.0f;
            m_enemies[EnemyFactory::EnemyListStoneGolem] = 7.0f;

            m_bosses[EnemyFactory::EnemyListDeadWizard] = 10.0f;
        }
        else
        {
            m_generationType = Enums::Cave;
            m_mapFillNr = 0;
            m_enemies[EnemyFactory::EnemyListWaterSlime] = 5.0f;
            m_enemies[EnemyFactory::EnemyListStoneGolem] = 7.0f;
            m_enemies[EnemyFactory::EnemyListIceSpirit] = 15.0f;

            m_bosses[EnemyFactory::EnemyListDeadWizard] = 3.0f;
            m_bosses[EnemyFactory::EnemyListIceGolem] = 10.0f;
        }
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
    MapFillDungeon* mf;
    int width, height;

    if(m_dungeonId == 1)
    {
        wallAbove = true;
        width = 40;
        height = 30;
        mf = new MapFillDungeon();
    }
    else
    {
        width = 100;
        height = 70;
        if(m_dungeonType == 0)
        {
            wallAbove = true;
            if(m_mapFillNr == 0)
            {
                mf = new MapFillDungeon();
            }
            else
            {
                mf = new MapFillDungeon2();
            }
        }
        else
        {
            wallAbove = false;
            mf = new MapFillIceDungeon();
        }
    }
    mf->InitItemChances(wallAbove);
    return new SceneManagerDungeon(width,height, m_seed + id, id, this, mf, m_generationType, wallAbove);;
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
            return EnemyFactory::GetEntity(it->first, lvl + 5 * (m_dungeonId - 1));
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
            return EnemyFactory::GetEntity(it->first,  lvl + 5 * (m_dungeonId - 1));
        }
    }
}
