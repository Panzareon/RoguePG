#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include <functional>

#include "Effect.h"
#include "EffectFactoryBase.h"

class EffectFactory : public EffectFactoryBase
{
    public:
        EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* func, int id, float chance = 1.0f);
        virtual ~EffectFactory();

        //Returns new Instance of Effect with a strength defined by the value given, needs to be deleted
        virtual EffectBase* GetEffectWithValue(float value, BattleEnums::Target target);
        virtual EffectBase* GetEffectWithStrength(std::vector<float>* strength, BattleEnums::Target target);


    protected:
    private:
        //Function Pointer to Function that implements the Effect
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* m_effectFunction;

};

#endif // EFFECTFACTORY_H
