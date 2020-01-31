#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Party/Party.h"
#include "SceneManager/SceneManager.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Controller/Configuration.h"
#include "MapGeneration/DungeonConfiguration.h"
#include "PersistentProgress.h"
#include <random>

class GameController
{
    public:
        virtual ~GameController();
        static GameController* getInstance();

        void InitValues();

        void Tick();
        SceneManager* GetActiveSceneManager();
        void CloseActiveSceneManger();
        void LoadSceneManager(SceneManager*);
        void LoadSceneManager(std::shared_ptr<SceneManager>);
        //Loads a new Scenemanager before the given, to be displayed when the given Scenemanager is finished
        //If SceneManager is not found, the new Scenemanager is added to the end
        void LoadSceneManagerBefore(SceneManager*, SceneManager* sm = nullptr);
        void LoadSceneManagerBefore(std::shared_ptr<SceneManager>, SceneManager* sm = nullptr);
        void StartBattle(std::vector<Entity*>* enemies);
        void GotoNextLevel();
        void GotoPreviousLevel();
        void SetDungeonConfiguration(DungeonConfiguration* config);
        DungeonConfiguration* GetDungeonConfiguration();

        void GameOverCheck();
        void QuitTo(SceneManager::SceneManagerType toType);

        void SetRenderTarget(sf::RenderTarget* target);
        sf::RenderTarget* GetRenderTarget();
        int GetWindowWidth();
        int GetWindowHeight();

        float GetTickTimeSeconds();

        PersistentProgress* GetPersistentProgress();

        //If once == false check if it is still pressed
        bool IsKeyPressed(Configuration::Keys key, bool once = true);
        bool IsWindowFocused();

        void setParty(Party party);
        void SetWindowFocus(bool focused);
        Party* getParty();
        std::default_random_engine* GetRandomGenerator();

        int GetLastDungeonBeated();

        void SaveToFile();
        bool LoadFromFile();
        bool LoadAvailable();
        void RemoveSaveFile();
        void SaveProgress();
    protected:
    private:
        void ToQuitScreen();
        void GameOver();
        void LoadProgress();
        int m_lastDungeon;
        bool m_quit;
        SceneManager::SceneManagerType m_quitTo;
        bool m_gameOver;
        bool m_currentGameWasLoaded;
        Party m_party;
        sf::RenderTarget* m_renderTarget;
        int m_windowWidth;
        int m_windowHeight;
        int m_levelId;
        sf::Time m_frameTime;
        sf::Clock m_clock;

        PersistentProgress m_progress;

        bool m_windowFocused;

        std::vector<bool> m_keysPressed;
        std::vector<bool> m_defaultKeysPressed;

        std::vector<std::shared_ptr<SceneManager> > m_sceneManager;
        std::vector<std::shared_ptr<SceneManager> > m_nextLevels;
        std::default_random_engine m_randomGenerator;
        DungeonConfiguration* m_dungeonConfiguration;


        static GameController* m_instance;
        GameController();
};

#endif // GAMECONTROLLER_H
