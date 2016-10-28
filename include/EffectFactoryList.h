#ifndef EFFECTFACTORYLIST_H
#define EFFECTFACTORYLIST_H

#include "EffectFactory.h"
#include <vector>


class EffectFactoryList
{
    public:
        virtual ~EffectFactoryList();
        static EffectFactoryList* GetInstance();
        EffectFactory* getWithId(int id);
        EffectFactory* getRandom(BattleEnums::AttackType attackType);
        EffectFactory* getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType);
        EffectFactory* getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType, bool needTarget);
    protected:
    private:
        std::vector<EffectFactory*> m_effects;

        static  EffectFactoryList* m_instance;
        EffectFactoryList();
};

#endif // EFFECTFACTORYLIST_H
