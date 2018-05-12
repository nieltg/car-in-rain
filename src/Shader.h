#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    private:
        GLuint shader;
        std::string shaderCode;
    public:
        Shader(GLenum _type);
        void Source(const char* shaderPath);
        void Compile();
};