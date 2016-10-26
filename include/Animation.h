#ifndef ANIMATION_H
#define ANIMATION_H

#include "AnimationPart.h"
#include "Node.h"
#include <vector>


class Animation
{
    public:
        Animation(float maxTime);
        virtual ~Animation();
        void PassTime(float Time);
        bool IsFinished();
        void AddStep(AnimationPart* part);
    protected:
    private:
        float m_animationTime;
        float m_maxTime;
        std::vector<AnimationPart*> m_animationParts;
        std::vector<Node*> m_nodes;
};

#endif // ANIMATION_H
