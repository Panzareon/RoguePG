#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Party.h"
#include "SceneManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GameController
{
    public:
        virtual ~GameController();
        static GameController* getInstance();

        void Tick();
        SceneManager* GetActiveSceneManager();
        void CloseActiveSceneManger();
        void LoadSceneManager(SceneManager*);
        //TODO: Enemies as Parameter
        void StartBattle();

        void SetRenderTarget(sf::RenderTarget* target);
        sf::RenderTarget* GetRenderTarget();
        int GetWindowWidth();
        int GetWindowHeight();



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


        std::vector<SceneManager*> m_sceneManager;
};

#endif // GAMECONTROLLER_H
