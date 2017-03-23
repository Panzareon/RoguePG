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

    protected:

    private:
};

#endif // PASSIVESKILL_H
