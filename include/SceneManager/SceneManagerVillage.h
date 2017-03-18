#ifndef SCENEMANAGERVILLAGE_H
#define SCENEMANAGERVILLAGE_H

#include "SceneManagerMoveable.h"
#include "MapGeneration/MapFill.h"
#include "MapGeneration/MapGeneratorVillage.h"


class SceneManagerVillage : public SceneManagerMoveable
{
    public:
        SceneManagerVillage(int tileWidth, int tileHeight, unsigned int seed, MapFill* mapFill);
        virtual ~SceneManagerVillage();

        virtual SceneManagerType GetType();

    protected:
        void AddShops();

        MapFill* m_mapFill;
        MapGeneratorVillage m_generator;

    private:
};

#endif // SCENEMANAGERVILLAGE_H
