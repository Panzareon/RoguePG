#ifndef EFFECTBASE_H
#define EFFECTBASE_H

#include <vector>
#include "Controller/NamedItem.h"
#include "StrengthCalculation.h"

class EffectFactoryBase;
class PassiveEffect;
class Entity;

class EffectBase : public virtual NamedItem
{
    public:
        EffectBase(EffectFactoryBase* factory, std::vector<float> *strength, float value, BattleEnums::Target target);
        virtual ~EffectBase();

        virtual void UseEffectOn(Entity* user, std::vector<Entity*>* targets);
        virtual void AddToPassiveEffect(PassiveEffect* target);


        float GetValue();
        EffectFactoryBase* GetFactory();

        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();

        std::vector<float>* GetStrength();

    protected:
        std::vector<float> *m_strength;
        float m_value;
        BattleEnums::Target m_defaultTarget;
        EffectFactoryBase* m_factory;

    private:
};

#endif // EFFECTBASE_H
