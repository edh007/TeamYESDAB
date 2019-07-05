#pragma once

#include "glew.h"
//#include "../external/assimp/include/Importer.hpp"
#include "Importer.hpp"

#include "math/Vector3.h"
#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex
{
    Vec3 pos;
    Vec3 nor;
    Vec3 uv;
    Vec3 tangent;
    Vec3 biTangent;
};

struct Texture
{
    unsigned int id;
    string type;
    aiString path;
};

class Mesh
{
public:
    vector<Vertex> m_vertices;
    vector<unsigned int> m_indices;
    vector<Texture> m_textures;
    unsigned int VAO;

    Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures);
    void Draw(Shader shader);
private:
    unsigned int VBO, IBO;

    void SetUpMesh();
};