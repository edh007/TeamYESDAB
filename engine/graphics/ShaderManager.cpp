#include "ShaderManager.h"


Shader* const &ShaderManager::RegisterShader(
	std::string type, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	// load the shader program given the specified source files; save the shader
	// given the specified type or, if one is already associated with that type,
	// replace it with the newly loaded shader program
	auto find = m_shaderMap.find(type);
	Shader* program = new Shader(vertexPath, fragmentPath, geometryPath);
	//auto program = Shader::LoadShaderProgram;
	if (find != m_shaderMap.end())
	{
		find->second = program; // replace program
		return find->second;    // and return it
	}
	else // new shader: insert(std::pair<ShaderType, ...>(type, program))
		return m_shaderMap.emplace(type, program).first->second; // and return it
}

Shader* const &ShaderManager::GetShader(const char* type) const
{
	// find a shader given the specified type; if it doesn't exist, return null
	// instead

	//if (m_shaderMap.at(type) == 0)
	//	return nullptr;

	return m_shaderMap.at(type);

	//auto find = m_shaderMap.find(type);
	//if (find != m_shaderMap.end())
	//	return find->second;
	//else
	//	return nullptr;

	//return m_texList[key];
}

void ShaderManager::ClearShaders()
{
	m_shaderMap.clear(); // delete all shader program instances registered
}