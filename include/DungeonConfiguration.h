#ifndef DUNGEONCONFIGURATION_H
#define DUNGEONCONFIGURATION_H

#include "SceneManager.h"

class DungeonConfiguration
{
    public:
        DungeonConfiguration(int nrLevels);
        virtual ~DungeonConfiguration();
        SceneManager* GetLevel(int id);
        int GetNrLevels();

    protected:
        int m_nrLevels;

    private:
};

#endif // DUNGEONCONFIGURATION_H
