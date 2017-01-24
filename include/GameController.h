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

        void Tick();
        SceneManager* GetActiveSceneManager();
        void CloseActiveSceneManger();
        void LoadSceneManager(SceneManager*);
        void StartBattle(std::vector<Entity*>* enemies);
        void GotoNextLevel();
        void GotoPreviousLevel();
        void SetDungeonConfiguration(DungeonConfiguration* config);

        void GameOverCheck();

        void SetRenderTarget(sf::RenderTarget* target);
        sf::RenderTarget* GetRenderTarget();
        int GetWindowWidth();
        int GetWindowHeight();

        bool IsKeyPressed(Configuration::Keys key);

        void setParty(Party* party);
        Party* getParty();
        std::default_random_engine* GetRandomGenerator();
    protected:
    private:
        void GameOver();
        bool m_gameOver;
        Party* m_party;
        sf::RenderTarget* m_renderTarget;
        int m_windowWidth;
        int m_windowHeight;
        int m_levelId;

        std::vector<bool> m_keysPressed;

        std::vector<SceneManager*> m_sceneManager;
        std::vector<SceneManager*> m_nextLevels;
        std::default_random_engine m_randomGenerator;
        DungeonConfiguration* m_dungeonConfiguration;


        static GameController* m_instance;
        GameController();
};

#endif // GAMECONTROLLER_H
