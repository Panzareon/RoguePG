#ifndef ANIMATIONPART_H
#define ANIMATIONPART_H

class Animation;
class AnimationPart
{
    public:
        AnimationPart(Animation* animation = 0);
        virtual ~AnimationPart();
        void animate(float newTime);
    protected:
        Animation* m_animation;
        float m_start;
        float m_end;
        int m_status;
    private:
};

#endif // ANIMATIONPART_H
