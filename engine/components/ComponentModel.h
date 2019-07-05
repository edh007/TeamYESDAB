#pragma once

#include "base/Component.h"
//#include "math\Math.h"
#include <glew.h>
#include "graphics/Mesh.h"
#include "stb_image.h"

//#pragma comment(lib, "assimp-vc140-mt.lib")
/* Assimp Header Start */
//#include "Importer.hpp" //C++ importer interface
#include "scene.h" // Output data structure
#include "postprocess.h" // Post processing flags
/* Assimp Header End */

#include "graphics/Model.h"

namespace gi
{
  //enum ModelType { NORMAL, SPHERE, CONE, CYLINDER, PLANE, CUBE, LIGHT, PARTICLE, END };
  class ComponentModel : public Component
  {
  public:
    static const std::string COMPONENT_ID;

    static ComponentModel* CreateComponentModel(Entity* pOwner);

    void SetAmbient(Vec4 ambient);
    Vec4 GetAmbient() const;

    void SetDiffuse(Vec4 diffuse);
    Vec4 GetDiffuse() const;

    void SetSpecular(Vec4 specular);
    Vec4 GetSpecular() const;

    void SetEmissive(Vec4 emissive);
    Vec4 GetEmissive() const;

    void SetShininess(float shininess);
    float GetShininess() const;

    void SetAttenuation(float constant, float linear, float quadratic);
    void SetAttenuation(Vec3 att);
    Vec3 GetAttenuation() const;

    void SetConstant(float constant);
    float GetConstant() const;

    void SetLinear(float linear);
    float GetLinear() const;

    void SetQuatratic(float quatratic);
    float GetQuatratic() const;

    void SetDirection(std::string dir);
    std::string GetDirection() const;

    void SetModelType(ModelType modelType);
    ModelType GetModelType() const;

    void InitModelByPath(string const& _path);
    void InitModelByType(ModelType _type);

    //private:
    explicit ComponentModel(Entity* pObject);
    virtual ~ComponentModel();

    void Draw(Shader _shader);
    void LoadModelfFile(string const &_path);
    void InsertNode(aiNode *_pNode, const aiScene* _pScene);
    Mesh InsertMesh(aiMesh *_pMesh, const aiScene *_pScene);
    vector<Texture> LoadMaterialTextures(aiMaterial* _pMat, aiTextureType _type, string _name);
    unsigned TextureFromFile(const char* path, const string& directory);
    void centerMesh();
    void normalizeVertices();
    void DrawComponent();
    Mat4 GetWorldMat() { return m_world; }
    void SetWorldMat(Mat4 input) { m_world = input; }
    bool GetRenderCheck() { return m_renderCheck; }
    void SetRenderCheck(bool input) { m_renderCheck = input; }
  private:
    // Color
    Vec4 m_ambient;
    Vec4 m_specular;
    Vec4 m_diffuse;
    float m_shininess;
    Vec4 m_emissive;
    float m_constant; //c1
    float m_linear; //c2
    float m_quadratic; //c3

    std::string m_dir;
    ModelType m_modelType;
    std::vector<Texture> m_loadedTexture;
    std::vector<Mesh> m_meshes;
    Mat4 m_world;
    bool m_renderCheck = true;
  };
}