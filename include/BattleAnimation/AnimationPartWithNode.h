#ifndef ANIMATIONPARTWITHNODE_H
#define ANIMATIONPARTWITHNODE_H

#include "AnimationPart.h"
#include "SceneGraph/Node.h"
#include "SFML/Graphics/Transform.hpp"

class AnimationPartWithNode : public AnimationPart
{
    public:
        AnimationPartWithNode();
        virtual ~AnimationPartWithNode();

        void SetStartTransform(sf::Transform tr);
        void SetTranslation(float moveX, float moveY);
        void SetRotation(float angle);
        void SetScaling(float scale);
        virtual void Start();
        virtual void Stop();
        virtual void AnimationStep(float percent);

    protected:
        Node* m_node;

        sf::Transform m_startTransform;
        sf::FloatRect m_size;
        float m_moveX;
        float m_moveY;
        float m_angle;
        float m_scale;

    private:
};

#endif // ANIMATIONPARTWITHNODE_H
