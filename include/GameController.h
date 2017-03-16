#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Party.h"
#include "SceneManager.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "DungeonConfiguration.h"

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
        void StartBattle(std::vector<Entity*>* enemies);
        void GotoNextLevel();
        void GotoPreviousLevel();
        void SetDungeonConfiguration(DungeonConfiguration* config);

        void GameOverCheck();
        void QuitTo(SceneManager::SceneManagerType toType);

        void SetRenderTarget(sf::RenderTarget* target);
        sf::RenderTarget* GetRenderTarget();
        int GetWindowWidth();
        int GetWindowHeight();

        float GetTickTimeSeconds();

        //If once == false check if it is still pressed
        bool IsKeyPressed(Configuration::Keys key, bool once = true);
        bool IsWindowFocused();

        void setParty(Party* party);
        void SetWindowFocus(bool focused);
        Party* getParty();
        std::default_random_engine* GetRandomGenerator();
    protected:
    private:
        void ToQuitScreen();
        void GameOver();
        bool m_quit;
        SceneManager::SceneManagerType m_quitTo;
        bool m_gameOver;
        Party* m_party;
        sf::RenderTarget* m_renderTarget;
        int m_windowWidth;
        int m_windowHeight;
        int m_levelId;
        sf::Time m_frameTime;
        sf::Clock m_clock;

        bool m_windowFocused;

        std::vector<bool> m_keysPressed;
        std::vector<bool> m_defaultKeysPressed;

        std::vector<SceneManager*> m_sceneManager;
        std::vector<SceneManager*> m_nextLevels;
        std::default_random_engine m_randomGenerator;
        DungeonConfiguration* m_dungeonConfiguration;


        static GameController* m_instance;
        GameController();
};

#endif // GAMECONTROLLER_H
