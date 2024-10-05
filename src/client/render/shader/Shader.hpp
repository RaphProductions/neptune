#pragma once

#include <glm/detail/qualifier.hpp>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

namespace neptune::client::render::shaders {
    enum ShaderType {
        SHADER_VERTEX,
        SHADER_FRAGMENT
    };
    
    class Shader {
    private:
        long program;
        std::vector<long> shaders;

    public:
        Shader();

        void addShader(ShaderType type, std::string code);
        void link();

        void use();

        void setBool(std::string name, bool value);
        void setInt(std::string name, int value);
        void setMat4F(std::string name, glm::mat4x4 value);
        void setVec4F(std::string name, glm::vec4 value);
        void setVec3F(std::string name, glm::vec3 value);
    };
}