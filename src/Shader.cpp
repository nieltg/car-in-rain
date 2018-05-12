#include "Shader.h"

Shader::Shader(GLenum _type)
{
    shader = glCreateShader(type);
}

Shader::~Shader()
{
    glDeleteShader(shader);
}

void Shader::Source(const char* shaderPath)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch
    {
        std::cerr << "Shader file not read succesfully" << std::endl;
    }
    glShaderSource(shader, 1, &shaderCode, NULL);
}

void Compile()
{
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "Shader not compiled: " << infoLog << std::endl; 
    }
}