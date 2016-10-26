#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Party.h"
#include "SceneManager.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Configuration.h"

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

        void GameOver();

        void SetRenderTarget(sf::RenderTarget* target);
        sf::RenderTarget* GetRenderTarget();
        int GetWindowWidth();
        int GetWindowHeight();

        bool IsKeyPressed(Configuration::Keys key);

        void setParty(Party* party);
        Party* getParty();
    protected:
    private:
        Party* m_party;
        sf::RenderTarget* m_renderTarget;
        int m_windowWidth;
        int m_windowHeight;
        static GameController* m_instance;
        GameController();

        std::vector<bool> m_keysPressed;

        std::vector<SceneManager*> m_sceneManager;
};

#endif // GAMECONTROLLER_H
