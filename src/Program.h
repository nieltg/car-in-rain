#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Program
{
    public:
        GLUint ProgramID;
        Program();
        void Attach(Shader s);
        void Link();
}