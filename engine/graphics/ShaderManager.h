#include "Shader.h"

typedef std::unordered_map<std::string, Shader*> ShaderMap;

class ShaderManager
{
public:
	Shader* const &RegisterShader(std::string type, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	Shader* const &GetShader(const char* type) const;
	void ClearShaders();

private:
	ShaderMap m_shaderMap;
};