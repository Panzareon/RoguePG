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


        BattleEnums::Target GetDefaultTarget();
        std::string GetName();


        void AddEffect(Effect* eff);
    protected:
    private:
        std::vector<Effect*> m_effects;
        Entity* m_user;

        float m_manaUse;
        BattleEnums::Target m_defaultTarget;
};

#endif // SKILL_H
