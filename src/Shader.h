#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    private:
        std::string shaderCode;
    public:
        GLuint shader;
        Shader(GLenum _type);
        ~Shader();
        void Source(const char* shaderPath);
        void Compile();
};