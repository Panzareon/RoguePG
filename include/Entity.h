#ifndef ENTITY_H
#define ENTITY_H

#include "Skill.h"
#include <vector>

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void PassTime(float Time);


        //Getter/Setter
        float GetTimeToNextAttack();
    protected:
        std::vector<Skill> m_skills;

        int m_maxHp;
        int m_hp;
        int m_attack;
        int m_speed;
        float m_toNextAttack;
    private:
};

#endif // ENTITY_H
