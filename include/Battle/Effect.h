#ifndef EFFECT_H
#define EFFECT_H

#include <functional>
#include "EffectBase.h"


class Effect : public EffectBase
{
    public:
        Effect(EffectFactoryBase* factory, std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* func, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target);

        virtual void UseEffectOn(Entity* user, std::vector<Entity*>* targets);


        virtual ~Effect();
    protected:
    private:
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* m_effectFunction;

};

#endif // EFFECT_H
