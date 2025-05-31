#include "shader.hpp"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkLinkError();
    glValidateProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Bind() const
{
    glUseProgram(id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (bool)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), (float)value);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), (float)x, (float)y);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), (float)x, (float)y, (float)z);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), (float)x, (float)y, (float)z, (float)w);
}

void Shader::SetMat4(const std::string& name, bool transpose, const float* mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, transpose, mat);
}

std::string Shader::readFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open shader file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    checkCompileError(shader, type);
    return shader;
}

void Shader::checkCompileError(GLuint shader, GLenum type)
{
    GLint params;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type : "
        << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
        << "\n" << infoLog << std::endl;
    }
}

void Shader::checkLinkError()
{
    GLint params;
    GLchar infoLog[1024];
    glGetProgramiv(id, GL_LINK_STATUS, &params);
    if (!params) {
        glGetProgramInfoLog(id, 1024, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
    }
}

void Shader::Destroy()
{
    glDeleteProgram(id);
}
