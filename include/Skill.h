#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "Enums.h"

class Entity;

class Skill
{
    public:
        Skill();
        virtual ~Skill();
        void Use(BattleEnums::Target targetType, Entity* target);


        BattleEnums::Target GetDefaultTarget();
        std::string GetName();
    protected:
    private:
        Entity* m_user;
};

#endif // SKILL_H
