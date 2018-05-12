#include "Program.h"

Program::Program()
{
    ProgramID = glCreateProgram();
}

Program::~Program()
{
    glDeleteProgram(ProgramID);
}

void Program::Attach(Shader s)
{
    glAttachShader(ProgramID,s.shader);
}

void Program::Link()
{
    glLinkProgram(ProgramID);
}
