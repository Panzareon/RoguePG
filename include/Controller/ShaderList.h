#ifndef SHADERLIST_H
#define SHADERLIST_H

#include <SFML/Graphics.hpp>

class ShaderList
{
    public:
        enum ShaderFiles {
            AnimatedSpriteShader
        };
        virtual ~ShaderList();

        static sf::Shader* GetShader(ShaderFiles file);
    protected:
    private:
        static std::map<ShaderFiles, sf::Shader*> m_shaders;
        ShaderList();
};

#endif // SHADERLIST_H
