#ifndef EFFECTFACTORYLIST_H
#define EFFECTFACTORYLIST_H

#include "EffectFactory.h"
#include <vector>


class EffectFactoryList
{
    public:
        virtual ~EffectFactoryList();
        static EffectFactoryList* GetInstance();
        EffectFactory* getRandom();
    protected:
    private:
        std::vector<EffectFactory*> m_effects;

        static  EffectFactoryList* m_instance;
        EffectFactoryList();
};

#endif // EFFECTFACTORYLIST_H
