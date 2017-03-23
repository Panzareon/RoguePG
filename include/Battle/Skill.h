#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <vector>
#include "Controller/Enums.h"
#include "Controller/NamedItem.h"

class Entity;
class EffectBase;

class Skill: public virtual NamedItem
{
    public:
        Skill(BattleEnums::Target target);
        virtual ~Skill();
        void Use(Entity* user, BattleEnums::Target targetType, Entity* target);

        int GetManaUse();
        int GetManaBase();

        BattleEnums::Target GetDefaultTarget();
        virtual std::string GetName();
        virtual std::string GetLocalizedDescription();

        std::vector<EffectBase*>* GetEffects();


        void AddEffect(EffectBase* eff, bool isPositive);
    protected:
    private:
        std::vector<EffectBase*> m_effects;
        std::vector<bool> m_isPositive;

        std::string m_name;

        float m_manaUseBase;
        BattleEnums::Target m_defaultTarget;
};

#endif // SKILL_H
