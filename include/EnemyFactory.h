#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Entity.h"
#include <map>

class EnemyFactory
{
    public:
        enum EnemyList{
            EnemyListBat,
            EnemyListDeadWizard
        };
        EnemyFactory();
        virtual ~EnemyFactory();

        static Entity* GetEntity(EnemyList type, int lvl);

    protected:

    private:
};

#endif // ENEMYFACTORY_H
