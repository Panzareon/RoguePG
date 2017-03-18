#ifndef AI_H
#define AI_H

class Entity;
//Base Class for all AI Algorithms
class AIBase
{
    public:
        AIBase(Entity* entity);
        virtual ~AIBase();
        virtual void UseNextSkill() = 0;
    protected:
        Entity* m_entity;
        Entity* GetRandomEntity(int teamId, bool enemy);
    private:
};

#endif // AI_H
