#include "Texture.h"

Texture::Texture(int numberAnimationSteps)
{
    //ctor
    m_numberAnimationSteps = numberAnimationSteps;
}

Texture::~Texture()
{
    //dtor
}

int Texture::GetNumberAnimationSteps()
{
    return m_numberAnimationSteps;
}
