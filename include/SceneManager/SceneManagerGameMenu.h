#ifndef SCENEMANAGERGAMEMENU_H
#define SCENEMANAGERGAMEMENU_H

#include "SceneManager.h"

#include <cereal/types/base_class.hpp>
/*
Class to display the ingame menu
*/
class SceneManagerGameMenu : public SceneManager
{
    public:
        SceneManagerGameMenu();
        virtual ~SceneManagerGameMenu();

        virtual void Quit();

        virtual void Tick();
        virtual bool IsFinished();

        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();
        virtual SceneManagerType GetType();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<SceneManager>( this ));
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<SceneManager>( this ));
        }
    protected:

        bool m_finished;

    private:
};

#endif // SCENEMANAGERGAMEMENU_H
