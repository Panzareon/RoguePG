#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <vector>
#include "Controller/Enums.h"
#include "Controller/NamedItem.h"
#include "Battle/EffectFactoryList.h"

#include <cereal/types/vector.hpp>
#include <cereal/types/base_class.hpp>

class Entity;
class EffectBase;

class Skill: public virtual NamedItem
{
    public:
        enum SkillType{Usable, Passive};
        Skill();
        Skill(BattleEnums::Target target);
        virtual ~Skill();
        void Use(Entity* user, BattleEnums::Target targetType, Entity* target);

        int GetManaUse();
        int GetManaBase();

        BattleEnums::Target GetDefaultTarget();
        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();

        std::vector<EffectBase*>* GetEffects();


        virtual SkillType GetSkillType();
        virtual void AddEffect(EffectBase* eff, bool isPositive);


        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_effectIds, m_effectStrength, m_isPositive, m_name, m_defaultTarget);
        }
        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            std::vector<int> m_effectIds;
            std::vector<std::vector<float> > m_effectStrength;
            std::vector<bool> m_isPositive;
            archive(m_effectIds, m_effectStrength, m_isPositive, m_name, m_defaultTarget);
            for(int i = 0; i < m_effectIds.size(); i++)
            {
                EffectFactoryBase* factory = EffectFactoryList::GetInstance()->getWithId(m_effectIds[i]);
                AddEffect(factory->GetEffectWithStrength(new std::vector<float>(m_effectStrength[i]),m_defaultTarget),m_isPositive[i]);
            }
        }
    protected:
    private:
        std::vector<int> m_effectIds;
        std::vector<std::vector<float> > m_effectStrength;
        std::vector<EffectBase*> m_effects;
        std::vector<bool> m_isPositive;

        std::string m_name;

        float m_manaUseBase;
        BattleEnums::Target m_defaultTarget;
};

#endif // SKILL_H
