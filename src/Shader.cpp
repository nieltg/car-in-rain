#include "Shader.h"

Shader::Shader(GLenum _type)
{
    shader = glCreateShader(_type);
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
    catch(std::ifstream::failure e)
    {
        std::cerr << "Shader file not read succesfully" << std::endl;
    }
    const GLchar* glFormatString = shaderCode.c_str();
    glShaderSource(shader, 1, &glFormatString, NULL);
}

void Shader::Compile()
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