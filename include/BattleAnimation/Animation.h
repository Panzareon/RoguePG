#ifndef ANIMATION_H
#define ANIMATION_H

#include "AnimationPart.h"
#include "SceneGraph/Node.h"
#include <vector>


class Animation
{
    public:
        Animation(float maxTime);
        virtual ~Animation();
        void PassTime(float Time);
        bool IsFinished();
        void AddStep(AnimationPart* part);
        //Set whether later added animations should stop until this is finished
        void SetStopsOther(bool stopsOther);
        bool StopsOther();
    protected:
    private:
        float m_animationTime;
        float m_maxTime;
        bool m_stopsOther;
        std::vector<AnimationPart*> m_animationParts;
};

#endif // ANIMATION_H
