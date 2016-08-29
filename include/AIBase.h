#ifndef AI_H
#define AI_H

//Base Class for all AI Algorithms
class AIBase
{
    public:
        AIBase();
        virtual ~AIBase();
        virtual void UseNextSkill() = 0;
    protected:
    private:
};

#endif // AI_H
