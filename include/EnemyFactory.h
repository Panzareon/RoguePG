#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Entity.h"
#include <map>

class EnemyFactory
{
    public:
        enum EnemyList{
            EnemyListBat
        };
        EnemyFactory();
        virtual ~EnemyFactory();

        static Entity* GetEntity(EnemyList type);

    protected:

    private:
};

#endif // ENEMYFACTORY_H