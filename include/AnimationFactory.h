#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H

#include "Animation.h"
#include "EntityNode.h"

class AnimationFactory
{
    public:
        enum AnimationList{
            Fireball
        };
        AnimationFactory();
        virtual ~AnimationFactory();

        static Animation* GetAnimation(AnimationList anim, EntityNode* target);

    protected:

    private:
};

#endif // ANIMATIONFACTORY_H
