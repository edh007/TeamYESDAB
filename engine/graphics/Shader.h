#pragma once

#include "glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix3.h"
#include "math/Matrix4.h"

#define UNREFERENCED_PARAMETER(P)          (P)

enum class ShaderType
{
	EXAMPLE = 0,
	PHONG = 1,
    PARTICLE = 2,
    // TODO(Dongho): add more shader types here, such as PHONG or GOURAUD

	COUNT
};

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
    Shader* LoadShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
    //Shader const &RegisterShader(ShaderType type, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    //Shader const &GetShader(ShaderType type) const;
    //void ClearShaders();
    // activate the shader
    // ------------------------------------------------------------------------
    void Use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void SetInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void SetFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void SetVec3(const std::string &name, const Vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value.v[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void SetVec4(const std::string &name, const Vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value.v[0]);
    }
    void SetVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void SetMat3(const std::string &name, const Mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat.element[0]);
    }
    // ------------------------------------------------------------------------
    void SetMat4(const std::string &name, const Mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat.element[0]);
    }
    void SetUniform(std::string const &name, unsigned int value)
    {
        glUniform1i(ID, value);
    }


    static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        //TODO(Dongho): unreferenced parameter
        UNREFERENCED_PARAMETER(source);
        UNREFERENCED_PARAMETER(length);
        UNREFERENCED_PARAMETER(userParam);
        std::cout << "---------------------opengl-callback-start------------" << std::endl;
        std::cout << "message: " << message << std::endl;
        std::cout << "type: ";
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "OTHER";
            break;
        }
        std::cout << std::endl;
        std::cout << "id: " << std::hex << id << std::endl;
        std::cout << "severity: ";
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "HIGH";
            break;
        }
        std::cout << std::endl;
        std::cout << "---------------------opengl-callback-end--------------" << std::endl;
    }


private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(GLuint shader, std::string type);
	
};
