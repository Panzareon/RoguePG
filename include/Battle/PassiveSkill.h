#ifndef PASSIVESKILL_H
#define PASSIVESKILL_H

#include "PassiveEffect.h"
#include "Skill.h"

class PassiveSkill : public Skill, public PassiveEffect
{
    public:
        PassiveSkill();
        virtual ~PassiveSkill();

        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();

        virtual SkillType GetSkillType();
        virtual void AddEffect(EffectBase* eff, bool isPositive);
    protected:

    private:
};

#endif // PASSIVESKILL_H
