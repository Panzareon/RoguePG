#ifndef EFFECTFACTORYLIST_H
#define EFFECTFACTORYLIST_H

#include "EffectFactoryBase.h"
#include <vector>


class EffectFactoryList
{
    public:
        virtual ~EffectFactoryList();
        static EffectFactoryList* GetInstance();
        EffectFactoryBase* getWithId(int id);
        EffectFactoryBase* getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType);
        EffectFactoryBase* getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType, bool needTarget);
    protected:
    private:
        std::vector<EffectFactoryBase*> m_effects;

        static  EffectFactoryList* m_instance;
        EffectFactoryList();
};

#endif // EFFECTFACTORYLIST_H
