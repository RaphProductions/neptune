#include "client/render/shader/Shader.hpp"
#include "util/err.hpp"
#include <client/render/TextRenderer.hpp>
#include <client/glad/glad.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace neptune::client::render;

const char *vertShaderCode = 
"#version 330 core\n"
"layout (location = 0) in vec4 vertex;\n" // <vec2 pos, vec2 tex>
"out vec2 TexCoords;\n"

"uniform mat4 projection;\n"

"void main()\n"
"{"
"    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
"    TexCoords = vertex.zw;\n"
"}\0";  

const char *fragShaderCode = 
"#version 330 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;\n"

"uniform sampler2D text;\n"
"uniform vec3 textColor;\n"

"void main()\n"
"{    \n"
"    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
"    color = vec4(textColor, 1.0) * sampled;\n"
"}\0";
 
std::map<char, Character> TextRenderer::Characters;
unsigned int TextRenderer::VAO, TextRenderer::VBO;
shaders::Shader TextRenderer::textShader;
bool TextRenderer::textShaderInitialized = false;
int TextRenderer::mostCharHeight = 0;
float TextRenderer::projectionHeight = 0.0f;

void TextRenderer::init() {
    if (TextRenderer::textShaderInitialized != true) {
        TextRenderer::textShader.addShader(shaders::SHADER_VERTEX, vertShaderCode);
        TextRenderer::textShader.addShader(shaders::SHADER_FRAGMENT, fragShaderCode);
        TextRenderer::textShader.link();

        projectionHeight = 600.0f;
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 000.0f, static_cast<float>(600));
        TextRenderer::textShader.use();
        TextRenderer::textShader.setMat4F("projection", projection);
        textShaderInitialized = true;
    }

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        throw utils::NeptuneException("Cannot initialize FreeType");
    }

    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/TTF/arial.ttf", 0, &face))
    {
        throw utils::NeptuneException("Font loading failed!");
    }

    FT_Set_Pixel_Sizes(face, 0, 18);  

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        if (mostCharHeight < (int)face->glyph->bitmap.rows)
            mostCharHeight = face->glyph->bitmap.rows;

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

float TextRenderer::getYTop(float offset_y) {
    return projectionHeight - mostCharHeight - offset_y;
}

void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    // On most things, Y 0 is the top.
    y = TextRenderer::getYTop(y);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // activate corresponding render state	
    TextRenderer::textShader.use();
    TextRenderer::textShader.setVec3F("textColor", glm::vec3(color.x, color.y, color.z));

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
}

void TextRenderer::setTextProjection(float left, float bottom, float width, float height) {
    projectionHeight = height;
    glm::mat4 projection = glm::ortho(left, static_cast<float>(width), bottom, static_cast<float>(height));
    TextRenderer::textShader.use();
    TextRenderer::textShader.setMat4F("projection", projection);
}