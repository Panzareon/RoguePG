#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <functional>
#include "Entity.h"
#include "StrengthCalculation.h"
#include "AnimationFactory.h"

class EffectFactory;

class Effect
{
    public:
        Effect(EffectFactory* factory, std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target);

        void UseEffectOn(Entity* user, std::vector<Entity*>* targets);
        void SetAnimation(AnimationFactory::AnimationList anim);

        float GetValue();
        EffectFactory* GetFactory();

        std::string GetName();
        std::string GetLocalizedDescription();

        virtual ~Effect();
    protected:
    private:
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* m_effectFunction;

        std::vector<float> *m_strength;
        StrengthCalculation* m_strengthCalculation;
        BattleEnums::Target m_defaultTarget;
        AnimationFactory::AnimationList m_anim;
        EffectFactory* m_factory;
};

#endif // EFFECT_H
