#ifndef EFFECT_H
#define EFFECT_H

#include <functional>
#include "EffectBase.h"
#include "BattleAnimation/AnimationFactory.h"


class Effect : public EffectBase
{
    public:
        Effect(EffectFactoryBase* factory, std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* func, std::vector<float> *strength, float value, BattleEnums::Target target);

        virtual void UseEffectOn(Entity* user, std::vector<Entity*>* targets);

        void SetAnimation(AnimationFactory::AnimationList anim);

        virtual ~Effect();
    protected:
    private:
        std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* m_effectFunction;
        AnimationFactory::AnimationList m_anim;

};

#endif // EFFECT_H
