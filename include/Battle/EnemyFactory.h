#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Entity.h"
#include <map>

class EnemyFactory
{
    public:
        enum class EnemyList{
            Bat,
            DeadWizard,
            StoneGolem,
            WindEye,
            WaterSlime,
            IceGolem,
            IceSpirit

        };
        EnemyFactory();
        virtual ~EnemyFactory();

        static Entity* GetEntity(EnemyList type, int lvl);

    protected:

    private:
};

#endif // ENEMYFACTORY_H
