#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <functional>
#include "Entity.h"
#include "StrengthCalculation.h"

class Effect
{
    public:
        Effect(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::vector<float> *strength, StrengthCalculation* strengthCalculation);

        void UseEffectOn(Entity* user, std::vector<Entity*>* targets);

        virtual ~Effect();
    protected:
    private:
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* m_effectFunction;

        std::vector<float> *m_strength;
        StrengthCalculation* m_strengthCalculation;
};

#endif // EFFECT_H
