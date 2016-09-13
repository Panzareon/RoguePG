#ifndef AIRANDOM_H
#define AIRANDOM_H

#include "AIBase.h"

//AI that uses random skills at random targets
class AIRandom : public AIBase
{
    public:
        AIRandom(Entity* entity);
        virtual ~AIRandom();
        virtual void UseNextSkill();
    protected:
    private:
};

#endif // AIRANDOM_H
