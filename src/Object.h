#include "OBJ_Loader.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
    private:
        objl::Loader loader;
        bool loaded;
    public:
        Object(std::string path);
        std::vector<std::vector<glm::vec3>> getVertexPositions();
        std::vector<std::vector<glm::vec3>> getVertexNormals();
        std::vector<std::vector<glm::vec2>> getVertexTexCoors();
};