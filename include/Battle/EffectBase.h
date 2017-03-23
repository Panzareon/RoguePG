#ifndef EFFECTBASE_H
#define EFFECTBASE_H

#include <vector>
#include "Controller/NamedItem.h"
#include "Entity.h"
#include "StrengthCalculation.h"
#include "BattleAnimation/AnimationFactory.h"

class EffectFactoryBase;

class EffectBase : public virtual NamedItem
{
    public:
        EffectBase(EffectFactoryBase* factory, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target);
        virtual ~EffectBase();

        virtual void UseEffectOn(Entity* user, std::vector<Entity*>* targets);
        void SetAnimation(AnimationFactory::AnimationList anim);

        float GetValue();
        EffectFactoryBase* GetFactory();

        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();
    protected:
        std::vector<float> *m_strength;
        StrengthCalculation* m_strengthCalculation;
        BattleEnums::Target m_defaultTarget;
        AnimationFactory::AnimationList m_anim;
        EffectFactoryBase* m_factory;

    private:
};

#endif // EFFECTBASE_H
