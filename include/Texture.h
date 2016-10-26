#ifndef TEXTURE_H
#define TEXTURE_H

#include "SFML/Graphics/Texture.hpp"

class Texture : public sf::Texture
{
    public:
        Texture(int numberAnimationSteps = 1);
        virtual ~Texture();

        int GetNumberAnimationSteps();
    protected:
        int m_numberAnimationSteps;
    private:
};

#endif // TEXTURE_H
