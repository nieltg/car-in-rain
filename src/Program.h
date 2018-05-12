#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class Program
{
    public:
        GLuint ProgramID;
        Program();
        ~Program();
        void Attach(Shader s);
        void Link();
};