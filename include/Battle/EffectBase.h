#ifndef EFFECTBASE_H
#define EFFECTBASE_H

#include <vector>
#include "Controller/NamedItem.h"
#include "Entity.h"
#include "StrengthCalculation.h"

class EffectFactoryBase;
class PassiveEffect;

class EffectBase : public virtual NamedItem
{
    public:
        EffectBase(EffectFactoryBase* factory, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target);
        virtual ~EffectBase();

        virtual void UseEffectOn(Entity* user, std::vector<Entity*>* targets);
        virtual void AddToPassiveEffect(PassiveEffect* target);


        float GetValue();
        EffectFactoryBase* GetFactory();

        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();
    protected:
        std::vector<float> *m_strength;
        StrengthCalculation* m_strengthCalculation;
        BattleEnums::Target m_defaultTarget;
        EffectFactoryBase* m_factory;

    private:
};

#endif // EFFECTBASE_H
