#pragma once

#include <map>
#include <string>
#include <client/render/shader/Shader.hpp>

namespace neptune::client::render {
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    class TextRenderer {
    private:
        static std::map<char, Character> Characters;
        
        static shaders::Shader textShader;
        static bool textShaderInitialized;
        static unsigned int VAO, VBO;
        static int mostCharHeight; // bruh
        static float projectionHeight;
    public:
        static float getYTop(float offset_y);
        static void init();
        static void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
        static void setTextProjection(float x, float y, float width, float height);
    };
}