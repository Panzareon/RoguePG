#ifndef ANIMATIONPARTSPRITE_H
#define ANIMATIONPARTSPRITE_H

#include "AnimationPartWithNode.h"
#include "SceneGraph/TextureList.h"
#include "SFML/Graphics.hpp"
#include "SceneGraph/DrawableNode.h"


class AnimationPartSprite : public AnimationPartWithNode
{
    public:
        AnimationPartSprite(TextureList::TextureFiles sprite);
        virtual ~AnimationPartSprite();
        sf::Sprite* GetSprite();

    protected:
        TextureList::TextureFiles m_texture;
        sf::Sprite* m_sprite;

    private:
};

#endif // ANIMATIONPARTSPRITE_H
