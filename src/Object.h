#include "OBJ_Loader.h"
#include "Buffer.h"
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
        void setBufferData();
        bool isLoaded();
        Buffer vBuffer;
        Buffer uvBuffer;
        Buffer normBuffer;
        Buffer idxBuffer;
        std::vector<std::vector<glm::vec3>> vertexPositions;
        std::vector<std::vector<glm::vec3>> vertexNormals;
        std::vector<std::vector<glm::vec2>> vertexTexCoors;
        std::vector<std::vector<glm::vec3>> indices;
};