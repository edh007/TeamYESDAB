#pragma once

#include <glew.h>
#include "Mesh.h"
#include "stb_image.h"

//#pragma comment(lib, "assimp-vc140-mt.lib")
/* Assimp Header Start */
//#include "Importer.hpp" //C++ importer interface
#include "scene.h" // Output data structure
#include "postprocess.h" // Post processing flags
/* Assimp Header End */

using namespace std;

enum ModelType { NORMAL, SPHERE, CONE, CYLINDER, PLANE, CUBE, LIGHT, PARTICLE, END };
class Model
{
public:

    vector<Texture> m_loadedTexture;
    vector<Mesh> m_meshes;
    string m_dir;
    ModelType m_modelType;

    Model(string const &_path);
    Model(ModelType _type);
    void Draw(Shader _shader);

	/*
	TODO(Dongho) : Temporary Values
	*/
	Vec3 pos;
    Vec3 scl;
    
	// Color
	Vec4 ambient;
	Vec4 specular;
	Vec4 diffuse;
	float shininess;
	Vec4 emmisive;
	float constant; //c1
	float linear; //c2
	float quadratic; //c3

private:
    void LoadModelfFile(string const &_path);
    void InsertNode(aiNode *_pNode, const aiScene* _pScene);
    Mesh InsertMesh(aiMesh *_pMesh, const aiScene *_pScene);
    vector<Texture> LoadMaterialTextures(aiMaterial* _pMat, aiTextureType _type, string _name);
    unsigned TextureFromFile(const char* path, const string& directory);
    void centerMesh();
    void normalizeVertices();
};

