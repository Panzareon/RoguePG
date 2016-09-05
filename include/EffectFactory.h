#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include <vector>
#include <functional>

#include "Effect.h"

class EffectFactory
{
    public:
        EffectFactory(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::function<std::vector<float>*(float, BattleEnums::Target)>* valueToStrength);
        virtual ~EffectFactory();

        //Returns new Instance of Effect with a strength defined by the value given, needs to be deleted
        Effect* GetEffectWithValue(float value, BattleEnums::Target target);
    protected:
    private:
        //Function Pointer to Function that implements the Effect
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* m_effectFunction;

        //Function that calculates Strength for the Effect given a value how strong it should be
        std::function<std::vector<float>*(float, BattleEnums::Target)>* m_valueToStrength;
};

#endif // EFFECTFACTORY_H
