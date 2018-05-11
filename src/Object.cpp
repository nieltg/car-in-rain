#include "Object.h"

Object::Object(std::string path)
{
    loaded = loader.LoadFile(path);
    if (!loaded)
    {
        std::cerr << ".obj not loaded" << std::endl;
    }
}

std::vector<std::vector<glm::vec3>> Object::getVertexPositions()
{
    if (!loaded)
        std::cerr << "Call after .obj is loaded" << std::endl;
    else
    {
        //Load all meshes here
        std::vector<std::vector<glm::vec3>> VertexPositions;
        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            //Load vertices per mesh
            std::vector<glm::vec3> currentPositions;
            objl::Mesh currentMesh = loader.LoadedMeshes[i];
            for (int j = 0; j < currentMesh.Vertices.size(); j++)
            {
                glm::vec3 currentVertex(currentMesh.Vertices[j].Position.X,
                    currentMesh.Vertices[j].Position.Y,
                    currentMesh.Vertices[j].Position.Z);
                currentPositions.push_back(currentVertex);
            }
            VertexPositions.push_back(currentPositions);    
        }
        return VertexPositions; 
    }
}


std::vector<std::vector<glm::vec3>> Object::getVertexNormals()
{
    if (!loaded)
        std::cerr << "Call  after .obj is loaded" << std::endl;
    else
    {
        //Load all meshes here
        std::vector<std::vector<glm::vec3>> VertexNormals;
        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            //Load vertices per mesh
            std::vector<glm::vec3> currentNormals;
            objl::Mesh currentMesh = loader.LoadedMeshes[i];
            for (int j = 0; j < currentMesh.Vertices.size(); j++)
            {
                glm::vec3 currentVertex(currentMesh.Vertices[j].Normal.X,
                    currentMesh.Vertices[j].Normal.Y,
                    currentMesh.Vertices[j].Normal.Z);
                currentNormals.push_back(currentVertex);
            }
            VertexNormals.push_back(currentNormals);    
        }
        return VertexNormals; 
    }
}

std::vector<std::vector<glm::vec2>> Object::getVertexTexCoors()
{
    if (!loaded)
        std::cerr << "Call  after .obj is loaded" << std::endl;
    else
    {
        //Load all meshes here
        std::vector<std::vector<glm::vec2>> VertexTexCoors;
        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            //Load vertices per mesh
            std::vector<glm::vec2> currentTexCoors;
            objl::Mesh currentMesh = loader.LoadedMeshes[i];
            for (int j = 0; j < currentMesh.Vertices.size(); j++)
            {
                glm::vec2 currentVertex(currentMesh.Vertices[j].TextureCoordinate.X,
                    currentMesh.Vertices[j].TextureCoordinate.Y);
                currentTexCoors.push_back(currentVertex);
            }
            VertexTexCoors.push_back(currentTexCoors);    
        }
        return VertexTexCoors; 
    }
}

std::vector<std::vector<glm::vec3>> Object::getIndices()
{
    if (!loaded)
        std::cerr << "Call  after .obj is loaded" << std::endl;
    else
    {
        //Load all meshes here
        std::vector<std::vector<glm::vec3>> Indices;
        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            //Load vertices per mesh
            std::vector<glm::vec3> currentIndices;
            objl::Mesh currentMesh = loader.LoadedMeshes[i];
            for (int j = 0; j < currentMesh.Vertices.size(); j+=3)
            {
                glm::vec3 currentIndice(currentMesh.Indices[j],
                    currentMesh.Indices[j+1],
                    currentMesh.Indices[j+2]);
                currentIndices.push_back(currentIndice);
            }
            Indices.push_back(currentIndices);    
        }
        return Indices; 
    }
}