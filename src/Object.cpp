#include "Object.h"

Object::Object(std::string path) : vBuffer("coord3d"), 
                                    uvBuffer("texcoord"),
                                    normBuffer("normals"),
                                    idxBuffer("elements")
{
    loaded = loader.LoadFile(path);
    if (!loaded)
    {
        std::cerr << ".obj not loaded" << std::endl;
    }
    else
    {
        //Load all meshes here
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
            vertexPositions.push_back(currentPositions);
            //load normals per mesh
            std::vector<glm::vec3> currentNormals;
            for (int j = 0; j < currentMesh.Vertices.size(); j++)
            {
                glm::vec3 currentVertex(currentMesh.Vertices[j].Normal.X,
                    currentMesh.Vertices[j].Normal.Y,
                    currentMesh.Vertices[j].Normal.Z);
                currentNormals.push_back(currentVertex);
            }
            vertexNormals.push_back(currentNormals);
            //Load uvs per mesh
            std::vector<glm::vec2> currentTexCoors;
            for (int j = 0; j < currentMesh.Vertices.size(); j++)
            {
                glm::vec2 currentVertex(currentMesh.Vertices[j].TextureCoordinate.X,
                    currentMesh.Vertices[j].TextureCoordinate.Y);
                currentTexCoors.push_back(currentVertex);
            }
            vertexTexCoors.push_back(currentTexCoors);  
            //Load indices per mesh
            std::vector<glm::vec3> currentIndices;
            for (int j = 0; j < currentMesh.Vertices.size(); j+=3)
            {
                glm::vec3 currentIndice(currentMesh.Indices[j],
                    currentMesh.Indices[j+1],
                    currentMesh.Indices[j+2]);
                currentIndices.push_back(currentIndice);
            }
            indices.push_back(currentIndices);   
        }
        //Do things with Buffers
        setBufferData();
    }
}

void Object::setBufferData()
{
    //writes every vertex etc data for Buffer to bind
    std::vector<GLfloat> allVertex;
    for (auto i = vertexPositions.begin(); i != vertexPositions.end(); i++)
    {
        for (auto j = i->begin(); j != i->end(); j++)
        {
            glm::vec3 rawData = *j;
            GLfloat* data = glm::value_ptr(rawData);
            allVertex.push_back(data[0]);
            allVertex.push_back(data[1]);
            allVertex.push_back(data[2]);
        }
    }
    vBuffer.setBufferData(&allVertex[0]);
    std::vector<GLfloat> allNormals;
    for (auto i = vertexNormals.begin(); i != vertexNormals.end(); i++)
    {
        for (auto j = i->begin(); j != i->end(); j++)
        {
            glm::vec3 rawData = *j;
            GLfloat* data = glm::value_ptr(rawData);
            allNormals.push_back(data[0]);
            allNormals.push_back(data[1]);
            allNormals.push_back(data[2]);
        }
    }
    normBuffer.setBufferData(&allNormals[0]);
    std::vector<GLfloat> allTexCoords;
    for (auto i = vertexTexCoors.begin(); i != vertexTexCoors.end(); i++)
    {
        for (auto j = i->begin(); j != i->end(); j++)
        {
            glm::vec2 rawData = *j;
            GLfloat* data = glm::value_ptr(rawData);
            allTexCoords.push_back(data[0]);
            allTexCoords.push_back(data[1]);
        }
    }
    uvBuffer.setBufferData(&allTexCoords[0]);
    std::vector<GLushort> allIndices;
    for (auto i = indices.begin(); i != indices.end(); i++)
    {
        for (auto j = i->begin(); j != i->end(); j++)
        {
            glm::vec3 rawData = *j;
            GLfloat* data = glm::value_ptr(rawData);
            allIndices.push_back((GLushort)data[0]);
            allIndices.push_back((GLushort)data[1]);
            allIndices.push_back((GLushort)data[3]);
        }
    }
    idxBuffer.setBufferData(&allIndices[0]);
}

bool Object::isLoaded()
{
    return loaded;
}