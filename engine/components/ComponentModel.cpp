#include "components/ComponentModel.h"
#include <imgui.h>
const std::string gi::ComponentModel::COMPONENT_ID = "gi_cmp_model";

gi::ComponentModel::ComponentModel(Entity* pObject)
	: Component(pObject)
{
  m_modelType = NORMAL;
  //LoadModelfFile(_path);

  m_ambient = Vec4(0.25f, 0.25f, 0.25f, 1.f);
  m_specular = Vec4(0.25f, 0.25f, 0.25f, 1.f);
  m_diffuse = Vec4(0.25f, 0.25f, 0.25f, 1.f);
  m_shininess = 8.f;
  m_emissive = Vec4(0.f, 0.f, 0.f, 1.f);
  m_constant = 1.f; //c1
  m_linear = 0.1f; //c2
  m_quadratic = 0.0f; //c3
}

gi::ComponentModel::~ComponentModel()
{
	m_pOwner = nullptr;
}

gi::ComponentModel* gi::ComponentModel::CreateComponentModel(Entity* pOwner)
{
  ComponentModel* pModel = new ComponentModel(pOwner);

	return pModel;
}

void gi::ComponentModel::SetAmbient(Vec4 ambient)
{
  m_ambient = ambient;
}

Vec4 gi::ComponentModel::GetAmbient() const
{
  return m_ambient;
}

void gi::ComponentModel::SetDiffuse(Vec4 diffuse)
{
  m_diffuse = diffuse;
}

Vec4 gi::ComponentModel::GetDiffuse() const
{
  return m_diffuse;
}

void gi::ComponentModel::SetSpecular(Vec4 specular)
{
  m_specular = specular;
}

Vec4 gi::ComponentModel::GetSpecular() const
{
  return m_specular;
}

void gi::ComponentModel::SetEmissive(Vec4 emissive)
{
  m_emissive = emissive;
}

Vec4 gi::ComponentModel::GetEmissive() const
{
  return m_emissive;
}

void gi::ComponentModel::SetShininess(float shininess)
{
  m_shininess = shininess;
}

float gi::ComponentModel::GetShininess() const
{
  return m_shininess;
}

void gi::ComponentModel::SetAttenuation(float constant, float linear, float quadratic)
{
  m_constant = constant;
  m_linear = linear;
  m_quadratic = quadratic;
}

void gi::ComponentModel::SetAttenuation(Vec3 att)
{
  m_constant = att.x;
  m_linear = att.y;
  m_quadratic = att.z;
}

Vec3 gi::ComponentModel::GetAttenuation() const
{
  return Vec3(m_constant, m_linear, m_quadratic);
}

void gi::ComponentModel::SetConstant(float constant)
{
  m_constant = constant;
}

float gi::ComponentModel::GetConstant() const
{
  return m_constant;
}

void gi::ComponentModel::SetLinear(float linear)
{
  m_linear = linear;
}

float gi::ComponentModel::GetLinear() const
{
  return m_linear;
}

void gi::ComponentModel::SetQuatratic(float quatratic)
{
  m_quadratic = quatratic;
}

float gi::ComponentModel::GetQuatratic() const
{
  return m_quadratic;
}

void gi::ComponentModel::SetDirection(std::string dir)
{
  m_dir = dir;
}

std::string gi::ComponentModel::GetDirection() const
{
  return m_dir;
}

void gi::ComponentModel::SetModelType(ModelType modelType)
{
  m_modelType = modelType;
}

ModelType gi::ComponentModel::GetModelType() const
{
  return m_modelType;
}

void gi::ComponentModel::InitModelByPath(string const& _path)
{
  LoadModelfFile(_path);
}

void gi::ComponentModel::InitModelByType(ModelType _type)
{
  //CurrentDirectory();
  switch (_type)
  {
  case SPHERE:
    m_modelType = SPHERE;
    LoadModelfFile("../../resources/obj/sphere.obj");
    break;
  case CONE:
    m_modelType = CONE;
    LoadModelfFile("../../resources/obj/cone.obj");
    break;
  case CYLINDER:
    m_modelType = CYLINDER;
    LoadModelfFile("../../resources/obj/cylinder.obj");
    break;
  case PLANE:
    m_modelType = PLANE;
    LoadModelfFile("../../resources/obj/plane.obj");
    break;
  case CUBE:
    m_modelType = CUBE;
    LoadModelfFile("../../resources/obj/cube.obj");
    break;
  case LIGHT:
    m_modelType = LIGHT;
    LoadModelfFile("../../resources/obj/cube.obj");
    break;
  default:
    std::cout << "ERROR!" << std::endl;
  }

  
}

void gi::ComponentModel::Draw(Shader _shader)
{
    if (m_renderCheck == true)
    {
        for (unsigned int i = 0; i < m_meshes.size(); ++i)
            m_meshes[i].Draw(_shader);
    }
}

void gi::ComponentModel::LoadModelfFile(string const& _path)
{
  // read file from the path with Assimp
  Assimp::Importer importer;
  const aiScene* pScene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

  //check for the errors
  if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
  {
    cout << "ERROR: ASSIMP: " << importer.GetErrorString() << endl;
    return;
  }

  m_dir = _path.substr(0, _path.find_last_of('/'));

  InsertNode(pScene->mRootNode, pScene);

  //TODO(DONGHO): need to check
  centerMesh();
  normalizeVertices();
}

void gi::ComponentModel::InsertNode(aiNode* _pNode, const aiScene* _pScene)
{
  for (unsigned int i = 0; i<_pNode->mNumMeshes; ++i)
  {
    aiMesh* pMesh = _pScene->mMeshes[_pNode->mMeshes[i]];
    m_meshes.emplace_back(InsertMesh(pMesh, _pScene));
  }

  for (unsigned int i = 0; i<_pNode->mNumChildren; ++i)
  {
    InsertNode(_pNode->mChildren[i], _pScene);
  }
}

Mesh gi::ComponentModel::InsertMesh(aiMesh* _pMesh, const aiScene* _pScene)
{
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;

  unsigned mNumVertices = _pMesh->mNumVertices;
  unsigned mNumFaces = _pMesh->mNumFaces;

  vertices.reserve(_pMesh->mNumVertices);
  indices.reserve(_pMesh->mNumFaces);

  for (unsigned int i = 0; i < mNumVertices; ++i)
  {
    Vertex vertex;
    Vec3 vector;

    vector.x = _pMesh->mVertices[i].x;
    vector.y = _pMesh->mVertices[i].y;
    vector.z = _pMesh->mVertices[i].z;
    vertex.pos = vector;

    vector.x = _pMesh->mNormals[i].x;
    vector.y = _pMesh->mNormals[i].y;
    vector.z = _pMesh->mNormals[i].z;
    vertex.nor = vector;

    if (_pMesh->mTextureCoords[0])
    {
      vertex.uv.x = _pMesh->mTextureCoords[0][i].x;
      vertex.uv.y = _pMesh->mTextureCoords[0][i].y;
    }
    else
    {
      vertex.uv.x = 0.f;
      vertex.uv.y = 0.f;
    }
    // tangent
    vector.x = _pMesh->mTangents[i].x;
    vector.y = _pMesh->mTangents[i].y;
    vector.z = _pMesh->mTangents[i].z;
    vertex.tangent = vector;
    // bitangent
    vector.x = _pMesh->mBitangents[i].x;
    vector.y = _pMesh->mBitangents[i].y;
    vector.z = _pMesh->mBitangents[i].z;
    vertex.biTangent = vector;
    vertices.emplace_back(vertex);
  }

  for (unsigned int i = 0; i < mNumFaces; i++)
  {
    aiFace face = _pMesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.emplace_back(face.mIndices[j]);
  }

  aiMaterial* pMaterial = _pScene->mMaterials[_pMesh->mMaterialIndex];

  vector<Texture> diffuseMap = LoadMaterialTextures(pMaterial, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());

  vector<Texture> specularMap = LoadMaterialTextures(pMaterial, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specularMap.begin(), specularMap.end());

  vector<Texture> normalMap = LoadMaterialTextures(pMaterial, aiTextureType_HEIGHT, "texture_normal");
  textures.insert(textures.end(), normalMap.begin(), normalMap.end());

  vector<Texture> heightMap = LoadMaterialTextures(pMaterial, aiTextureType_AMBIENT, "texture_height");
  textures.insert(textures.end(), heightMap.begin(), heightMap.end());

  return Mesh(vertices, indices, textures);
}

vector<Texture> gi::ComponentModel::LoadMaterialTextures(aiMaterial* _pMat, aiTextureType _type, string _name)
{
  vector<Texture> textures;
  for (unsigned int i = 0; i < _pMat->GetTextureCount(_type); ++i)
  {
    aiString str;
    _pMat->GetTexture(_type, i, &str);

    // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    bool skip = false;
    for (unsigned int j = 0; j < m_loadedTexture.size(); j++)
    {
      if (std::strcmp(m_loadedTexture[j].path.C_Str(), str.C_Str()) == 0)
      {
        textures.emplace_back(m_loadedTexture[j]);
        skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
        break;
      }
    }
    if (!skip)
    {   // if texture hasn't been loaded already, load it
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), this->m_dir);
      texture.type = _name;
      texture.path = str;
      textures.emplace_back(texture);
      m_loadedTexture.emplace_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
    }
  }
  return textures;
}

unsigned int gi::ComponentModel::TextureFromFile(const char *path, const string &directory)
{
  string filename = string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;
    else
      format = 0;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

void gi::ComponentModel::centerMesh()
{
  // find the centroid of the entire mesh (average of all vertices, hoping for
  // no overflow) and translate all vertices by the negative of this centroid
  // to ensure all transformations are about the origin
  Vec3 centroid(0.f, 0.f, 0.f);
  unsigned size = 0;
  for (unsigned i = 0; i < m_meshes.size(); ++i)
  {
    Mesh tmp = m_meshes[i];
    for (unsigned j = 0; j < tmp.m_vertices.size(); ++j)
    {
      centroid += tmp.m_vertices[j].pos;
      ++size;
    }
  }
  centroid *= 1.f / static_cast<float>(size);
  // translate by negative centroid to center model at (0, 0, 0)
  centroid = -centroid;

  for (unsigned i = 0; i < m_meshes.size(); ++i)
  {
    Mesh tmp = m_meshes[i];
    for (unsigned j = 0; j < tmp.m_vertices.size(); ++j)
    {
      tmp.m_vertices[j].pos += centroid;
    }
  }
}

void gi::ComponentModel::normalizeVertices()
{
  // find the extent of this mesh and normalize all vertices by scaling them
  // by the inverse of the smallest value of the extent
  Vec3 minimum = m_meshes[0].m_vertices[0].pos;
  Vec3 maximum = minimum;

  for (unsigned i = 0; i < m_meshes.size(); ++i)
  {
    Mesh tmp = m_meshes[i];
    for (unsigned j = 0; j < tmp.m_vertices.size(); ++j)
    {
      float x = tmp.m_vertices[j].pos.x;
      float y = tmp.m_vertices[j].pos.y;
      float z = tmp.m_vertices[j].pos.z;

      minimum.x = std::min(minimum.x, x);
      minimum.y = std::min(minimum.y, y);
      minimum.z = std::min(minimum.z, z);
      maximum.x = std::max(maximum.x, x);
      maximum.y = std::max(maximum.y, y);
      maximum.z = std::max(maximum.z, z);
    }
  }

  Vec3 extent = maximum - minimum;
  if (extent.x == 0)
    extent.x = 1;
  else if (extent.y == 0)
    extent.y = 1;
  else if (extent.z == 0)
    extent.z = 1;
  float scalar = 1.f / std::min(std::min(extent.x, extent.y), extent.z);

  for (unsigned i = 0; i < m_meshes.size(); ++i)
  {
    Mesh tmp = m_meshes[i];
    for (unsigned j = 0; j < tmp.m_vertices.size(); ++j)
    {
      tmp.m_vertices[j].pos *= scalar;
    }
  }
}

void gi::ComponentModel::DrawComponent()
{
    if (ImGui::CollapsingHeader("Model Component"))
    {
        ImGui::PushItemWidth(160);
        {
            //ImGui::InputInt("Quadratic", &m_modelType, 0, 1, 3);
            //LoadModelfFile("../../resources/obj/sphere.obj");

            float textWidth;
            float buttonSpacing;

            if (ImGui::GetWindowWidth() < 700)
            {
                textWidth = 300 - (700 - ImGui::GetWindowWidth());
                buttonSpacing = textWidth + 10;
            }
            else
            {
                textWidth = 300;
                buttonSpacing = 310;
            }

            // Actor name + active state
            {
                static char buf2[32] = "";
                ImGui::Text("OBJ name: %s\n", m_dir.c_str());
                ImGui::PushItemWidth(textWidth);
                {
                    if (ImGui::InputText("OBJ", buf2, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                    {
                        std::string dir = "../../resources/obj/";
                        m_dir = dir + buf2 + ".obj";
                        buf2[0] = '\0';
                        m_loadedTexture.clear();
                        m_meshes.clear();
                        LoadModelfFile(m_dir);
                    }
                    ImGui::PopItemWidth();
                }
                //ImGui::SameLine(buttonSpacing);

            }
            //std::cout << m_dir << std::endl;
            ImGui::InputFloat("Ambient R", &m_ambient.x, 0.f, 1.f, 3);
            ImGui::InputFloat("Ambient G", &m_ambient.y, 0.f, 1.f, 3);
            ImGui::InputFloat("Ambient B", &m_ambient.z, 0.f, 1.f, 3);
            ImGui::InputFloat("Ambient A", &m_ambient.w, 0.f, 1.f, 3);

            ImGui::InputFloat("Diffuse R", &m_diffuse.x, 0.f, 1.f, 3);
            ImGui::InputFloat("Diffuse G", &m_diffuse.y, 0.f, 1.f, 3);
            ImGui::InputFloat("Diffuse B", &m_diffuse.z, 0.f, 1.f, 3);
            ImGui::InputFloat("Diffuse A", &m_diffuse.w, 0.f, 1.f, 3);

            ImGui::InputFloat("Specular R", &m_specular.x, 0.f, 1.f, 3);
            ImGui::InputFloat("Specular G", &m_specular.y, 0.f, 1.f, 3);
            ImGui::InputFloat("Specular B", &m_specular.z, 0.f, 1.f, 3);
            ImGui::InputFloat("Specular A", &m_specular.w, 0.f, 1.f, 3);

            ImGui::InputFloat("Emmisive R", &m_emissive.x, 0.f, 1.f, 3);
            ImGui::InputFloat("Emmisive G", &m_emissive.y, 0.f, 1.f, 3);
            ImGui::InputFloat("Emmisive B", &m_emissive.z, 0.f, 1.f, 3);
            ImGui::InputFloat("Emmisive A", &m_emissive.w, 0.f, 1.f, 3);

            ImGui::InputFloat("Shiness R", &m_shininess, 0.f, 50.f, 3);
            ImGui::InputFloat("Constant", &m_constant, 0.f, 1.f, 3);
            ImGui::InputFloat("Linear", &m_linear, 0.f, 1.f, 3);
            ImGui::InputFloat("Quadratic", &m_quadratic, 0.f, 1.f, 3);
        }
        ImGui::PopItemWidth();
    }
    
    
}