#ifndef SCENEMANAGERMAINMENU_H
#define SCENEMANAGERMAINMENU_H

#include "SceneManager.h"
#include <cereal/types/base_class.hpp>

class SceneManagerMainMenu : public SceneManager
{
    public:
        SceneManagerMainMenu();
        virtual ~SceneManagerMainMenu();

        virtual void ChooseHero();
        virtual void Quit();

        virtual void Tick();
        virtual bool IsFinished();

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
        bool m_checkLoad;

    private:
};

#endif // SCENEMANAGERMAINMENU_H
