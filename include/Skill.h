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
        Skill(Entity* user, BattleEnums::Target target);
        virtual ~Skill();
        void Use(BattleEnums::Target targetType, Entity* target);

        float GetManaUse();

        BattleEnums::Target GetDefaultTarget();
        std::string GetName();


        void AddEffect(Effect* eff, bool isPositive);
    protected:
    private:
        std::vector<Effect*> m_effects;
        std::vector<bool> m_isPositive;
        Entity* m_user;

        float m_manaUse;
        BattleEnums::Target m_defaultTarget;
};

#endif // SKILL_H
