#include "ShaderList.h"
#include "InvalidArgumentException.h"

ShaderList::ShaderList()
{
    //ctor
}

ShaderList::~ShaderList()
{
    //dtor
}
std::map<ShaderList::ShaderFiles, sf::Shader*> ShaderList::m_shaders;

sf::Shader* ShaderList::GetShader(ShaderFiles file)
{
    if(m_shaders.find(file) == m_shaders.end())
    {
        std::string filename;
        std::string shaderPath = "shader/";
        sf::Shader* newShader = new sf::Shader();
        bool ret;

        //Initialize all Textures
        switch(file)
        {
        case AnimatedSpriteShader:
            filename = "spriteSheetAnimation.frag";
            shaderPath += filename;
            ret = newShader->loadFromFile(shaderPath , sf::Shader::Fragment);
            break;
        }

        if(!ret)
        {
            delete newShader;
            std::string msg("Could not load Shader: ");
            msg.append(shaderPath);
            throw InvalidArgumentException(msg);
            return 0;
        }
        m_shaders.insert(std::make_pair(file, newShader));
    }
    return m_shaders[file];
}
