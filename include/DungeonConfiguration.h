#ifndef DUNGEONCONFIGURATION_H
#define DUNGEONCONFIGURATION_H

#include "SceneManager.h"

class DungeonConfiguration
{
    public:
        DungeonConfiguration(int nrLevels, unsigned int seed);
        virtual ~DungeonConfiguration();
        SceneManager* GetLevel(int id);
        int GetNrLevels();

    protected:
        int m_nrLevels;
        unsigned int m_seed;

    private:
};

#endif // DUNGEONCONFIGURATION_H
