#include "MapGeneration/DungeonConfiguration.h"
#include "SceneManager/SceneManagerDungeon.h"
#include "Controller/GameController.h"
#include "Controller/MusicController.h"
#include "MapGeneration/MapFillDungeon.h"
#include "MapGeneration/MapFillIceDungeon.h"
#include "MapGeneration/MapFillDungeon2.h"
#include "Localization.h"

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

int DungeonConfiguration::GetNrEnemies()
{
    if(m_dungeonId == 1)
        return 1;
    else
        return 2;
}

//Returns Number of enemies to spawn with Boss
int DungeonConfiguration::GetNrBossAdds()
{
    if(m_dungeonId == 1)
        return 0;
    else
        return 2;
}

std::string DungeonConfiguration::ClearedDungeon()
{
    std::string rewards = "";
    Localization* localization = Localization::GetInstance();
    GameController* controller = GameController::getInstance();
    PersistentProgress* progress = controller->GetPersistentProgress();

    int nrCleared = progress->GetNrDungeonsCleared();
    if(m_dungeonId == 1)
    {
        for(int i = 0; i < CharacterClass::CHARACTER_CLASS_END; i++)
        {
            CharacterClass::CharacterClassEnum asEnum = (CharacterClass::CharacterClassEnum)i;
            if(!progress->IsClassUnlocked(asEnum))
            {
                progress->UnlockClass(asEnum);
                CharacterClass* charClass = CharacterClass::GetCharacterClass(asEnum);
                std::string className = localization->GetLocalization(charClass->GetName());

                std::vector<std::string> values;
                values.push_back(className);
                rewards += "\n";
                rewards += localization->GetLocalizationWithStrings("dungeon.finished.unlocked_class", &values);
                break;
            }
        }

        if(nrCleared < m_dungeonId)
        {

            int money = 100;
            progress->AddStartMoney(money);
            std::vector<std::string> moneyValue;
            moneyValue.push_back(std::to_string(money));
            rewards += "\n";
            rewards += localization->GetLocalizationWithStrings("dungeon.finished.start_money", &moneyValue);
        }
        controller->getParty()->AddRandomMember();
        rewards += "\n";
        rewards += localization->GetLocalization("dungeon.finished.member");


    }
    else
    {
        float chance = 0.1f;
        if(nrCleared < m_dungeonId)
        {
            chance = 1.0f;
        }
        float random = (float)rand() / RAND_MAX;
        if(chance > random)
        {
            random = (float)rand() / RAND_MAX;
            if(random < 0.2f)
            {
                int money = 20;
                progress->AddStartMoney(money);
                std::vector<std::string> moneyValue;
                moneyValue.push_back(std::to_string(money));
                rewards += "\n";
                rewards += localization->GetLocalizationWithStrings("dungeon.finished.start_money", &moneyValue);
            }
            else if(random < 0.22f)
            {
                progress->AddStartMember(1);
                rewards += "\n";
                rewards += localization->GetLocalization("dungeon.finished.start_member");
            }
            else if(random < 0.4f)
            {
                progress->AddShopNrItems(1);
                rewards += "\n";
                rewards += localization->GetLocalization("dungeon.finished.shop_number");
            }
            else if(random < 0.6f)
            {
                progress->AddShopLevel(1);
                rewards += "\n";
                rewards += localization->GetLocalization("dungeon.finished.shop_level");
            }
            else if(random < 0.8f)
            {
                controller->getParty()->AddRandomMember();
                rewards += "\n";
                rewards += localization->GetLocalization("dungeon.finished.member");
            }
            else
            {
                int money = 100;
                controller->getParty()->AddMoney(money);
                std::vector<std::string> moneyValue;
                moneyValue.push_back(std::to_string(money));
                rewards += "\n";
                rewards += localization->GetLocalizationWithStrings("dungeon.finished.money", &moneyValue);
            }
        }
    }
    return rewards;
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
