#ifndef ANIMATIONPARTTEXT_H
#define ANIMATIONPARTTEXT_H

#include "AnimationPartWithNode.h"


class AnimationPartText : public AnimationPartWithNode
{
    public:
        AnimationPartText(std::string str, sf::Color color, int fontSize);
        virtual ~AnimationPartText();

        sf::Text* GetText();

    protected:
        sf::Text* m_text;

    private:
};

#endif // ANIMATIONPARTTEXT_H
