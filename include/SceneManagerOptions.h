#ifndef SCENEMANAGEROPTIONS_H
#define SCENEMANAGEROPTIONS_H

#include "SceneManager.h"
#include "Configuration.h"

class SceneManagerOptions : public SceneManager
{
    public:
        SceneManagerOptions();
        virtual ~SceneManagerOptions();

        virtual void Tick();
        virtual bool IsFinished();

        virtual void Keybindings();
        virtual void Close();
        virtual void SetKey(Configuration::Keys key);

    protected:
        Configuration::Keys m_updateKey;
        bool m_configKey;
        MenuNode* m_keybindings;

        bool m_finished;

    private:
};

#endif // SCENEMANAGEROPTIONS_H
