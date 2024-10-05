#include "util/err.hpp"
#include <client/render/shader/Shader.hpp>
#include <client/glad/glad.h>
#include <glm/ext/vector_float4.hpp>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

using namespace neptune::client::render::shaders;

Shader::Shader() {
    shaders = std::vector<long>();
}

void Shader::addShader(ShaderType type, std::string code)
{
    unsigned int shader = glCreateShader(type == SHADER_VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    
    // Correctly passing the address of the C-string
    const char* codeCStr = code.c_str();
    glShaderSource(shader, 1, &codeCStr, NULL);
    
    glCompileShader(shader);
    
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        
        char *buf = (char *)malloc(512);
        snprintf(buf, 512, "Shader compilation failed: %s", infoLog);

        throw utils::NeptuneException(buf);
    }

    shaders.push_back(shader);
}


void Shader::link() {
    // Attach the shaders & link
    unsigned int shaderProgram = glCreateProgram();
    for (int i = 0; i < (int)shaders.size(); i++) {
        glAttachShader(shaderProgram, shaders[i]);
    }
    
    glLinkProgram(shaderProgram);

    // Check if OpenGL refused to link our shader
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        
        char *buf = (char *)malloc(512);
        snprintf(buf, 512, "Shader linkage failed: %s", infoLog);

        throw utils::NeptuneException(buf);
    }

    // We don't need the shaders anymore: they are linked together into the program.
    for (int i = 0; i < (int)shaders.size(); i++) {
        glDeleteShader(shaders[i]);
    }

    this->program = shaderProgram;
}

void Shader::use() {
    // As simple as that!
    glUseProgram(program);
}

void Shader::setBool(std::string name, bool value) {
    glUniform1i(glGetUniformLocation(program, (const GLchar *)name.c_str()), (int)value);
}

void Shader::setInt(std::string name, int value) {
    glUniform1i(glGetUniformLocation(program, (const GLchar *)name.c_str()), value);
}

void Shader::setMat4F(std::string name, glm::mat4x4 value) {
    glUniformMatrix4fv(glGetUniformLocation(program, (const GLchar *)name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4F(std::string name, glm::vec4 value) {
    glUniform4fv(glGetUniformLocation(program, (const GLchar *)name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3F(std::string name, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(program, (const GLchar *)name.c_str()), 1, glm::value_ptr(value));
}