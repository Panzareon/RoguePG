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
        virtual bool DeleteEffect();


        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<Skill>( this ));
        }
        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<Skill>( this ));
        }
    protected:

    private:
};

#endif // PASSIVESKILL_H
