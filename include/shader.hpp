#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "glad/glad.h"

enum class ShaderType {Basic, Lighting, PostProcess};

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentShader);
    ~Shader() = default;

    void Bind() const;
    void Unbind() const;

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat4(const std::string& name, bool transpose, const float* mat) const;

    void Destroy();

private:
    std::string readFile(const std::string& path);
    GLuint compileShader(GLenum type, const std::string& source);
    void checkCompileError(GLuint shader, GLenum type);
    void checkLinkError();

private:
    GLuint id;
};
