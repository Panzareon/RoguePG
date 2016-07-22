#ifndef ANIMATEDNODE_H
#define ANIMATEDNODE_H

#include "Node.h"

class AnimatedNode : public Node
{
    public:
        AnimatedNode(sf::Sprite sprite);
        virtual ~AnimatedNode();
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;


        void Tick(float seconds);
    protected:
        static sf::Shader* m_shader;
        float m_elapsedSeconds;
        sf::Sprite m_sprite;
    private:
};

#endif // ANIMATEDNODE_H
