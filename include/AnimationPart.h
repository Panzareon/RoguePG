#ifndef ANIMATIONPART_H
#define ANIMATIONPART_H

class Animation;
class AnimationPart
{
    public:
        AnimationPart(Animation* animation = 0);
        virtual ~AnimationPart();
        void SetTiming(float start, float end);
        virtual void animate(float newTime);
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void AnimationStep(float percent) = 0;
    protected:
        Animation* m_animation;
        float m_start;
        float m_end;
        int m_status;
    private:
};

#endif // ANIMATIONPART_H
