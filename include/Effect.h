#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <functional>
#include "Entity.h"
#include "StrengthCalculation.h"
#include "AnimationFactory.h"

class Effect
{
    public:
        Effect(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target);

        void UseEffectOn(Entity* user, std::vector<Entity*>* targets);
        void SetAnimation(AnimationFactory::AnimationList anim);

        float GetValue();

        virtual ~Effect();
    protected:
    private:
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* m_effectFunction;

        std::vector<float> *m_strength;
        StrengthCalculation* m_strengthCalculation;
        BattleEnums::Target m_defaultTarget;
        AnimationFactory::AnimationList m_anim;
};

#endif // EFFECT_H
