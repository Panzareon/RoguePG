#ifndef ANIMATEDNODE_H
#define ANIMATEDNODE_H

#include "Node.h"
#include "Controller/Enums.h"

class AnimatedNode : public Node
{
    public:
        AnimatedNode(sf::Sprite* sprite, int numberFrames);
        virtual ~AnimatedNode();
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;


        void Tick(float seconds);
        void SetDirection(Enums::Direction);
        void SetAnimationSpeed(float framesPerSecond);

        void SetSprite(sf::Sprite* sprite, int numberFrames);
    protected:
        sf::Shader* m_shader;
        float m_elapsedSeconds;
        float m_framesPerSecond;
        int m_numberFrames;
        sf::Sprite m_sprite;
    private:
};

#endif // ANIMATEDNODE_H
