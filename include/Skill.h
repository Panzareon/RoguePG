#ifndef SKILL_H
#define SKILL_H

class Entity;

class Skill
{
    public:
        enum Target{OwnTeam, EnemyTeam};
        Skill();
        virtual ~Skill();
        void Use();
        void Use(Entity* target);
        void Use(Target target);
    protected:
    private:
        Entity* m_user;
};

#endif // SKILL_H
