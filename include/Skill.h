#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <vector>
#include "Enums.h"

class Entity;
class Effect;

class Skill
{
    public:
        Skill(BattleEnums::Target target);
        virtual ~Skill();
        void Use(Entity* user, BattleEnums::Target targetType, Entity* target);

        float GetManaUse();

        BattleEnums::Target GetDefaultTarget();
        std::string GetName();

        std::vector<Effect*>* GetEffects();


        void AddEffect(Effect* eff, bool isPositive);
    protected:
    private:
        std::vector<Effect*> m_effects;
        std::vector<bool> m_isPositive;

        float m_manaUse;
        BattleEnums::Target m_defaultTarget;
};

#endif // SKILL_H
