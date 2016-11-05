#ifndef ANIMATIONPARTSPRITE_H
#define ANIMATIONPARTSPRITE_H

#include "AnimationPart.h"
#include "TextureList.h"
#include "SFML/Graphics.hpp"
#include "DrawableNode.h"


class AnimationPartSprite : public AnimationPart
{
    public:
        AnimationPartSprite(TextureList::TextureFiles sprite);
        virtual ~AnimationPartSprite();
        void SetStartTransform(sf::Transform tr);
        void SetTranslation(float moveX, float moveY);
        void SetRotation(float angle);
        void SetScaling(float scale);
        virtual void Start();
        virtual void Stop();
        virtual void AnimationStep(float percent);
        sf::Sprite* GetSprite();

    protected:
        TextureList::TextureFiles m_texture;
        DrawableNode* m_node;
        sf::Sprite* m_sprite;

        sf::Transform m_startTransform;
        float m_moveX;
        float m_moveY;
        float m_angle;
        float m_scale;

    private:
};

#endif // ANIMATIONPARTSPRITE_H
