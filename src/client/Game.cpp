#include "client/Window.hpp"
#include "client/render/shader/Shader.hpp"
#include "render/TextRenderer.hpp"
#include "util/vec.hpp"
#include <client/glad/glad.h>
#include <client/Game.hpp>
#include <client/render/Mesh.hpp>
#include <client/render/MeshLoader.hpp>
#include <iostream>

using namespace neptune::client;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "uniform vec4 OutputColor;\n"
    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
    "    FragColor = OutputColor;\n"
    "}\0";

int Game::run(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Window wnd("Project Neptune", utils::Vector2i(800, 600));
    wnd.makeCurrent();
    Window::initGL();

    const char *ver = (const char*)glGetString(GL_VERSION);
    const char *ren = (const char*)glGetString(GL_RENDERER);
    const char *vnd = (const char*)glGetString(GL_VENDOR);

    std::cout << "-- Project Neptune" << std::endl;
    std::cout << "- OpenGL version: " << ver << std::endl;
    std::cout << "- OpenGL vendor: " << vnd << std::endl;
    std::cout << "- OpenGL renderer: " << ren << std::endl;

    render::shaders::Shader sh;
    sh.addShader(render::shaders::SHADER_VERTEX, vertexShaderSource);
    sh.addShader(render::shaders::SHADER_FRAGMENT, fragmentShaderSource);
    sh.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> vertices = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    std::vector<int> indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    render::Mesh m = render::MeshLoader::createMesh(vertices, indices);

    render::TextRenderer::init();

    GLenum err;
    while (!wnd.shouldClose())
    {
        if ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "OpenGL error: " << err << std::endl;
            std::cout << std::flush;
        }

        glClearColor(0.0f, 0.2f, 0.471f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sh.use();
        sh.setVec4F("OutputColor", glm::vec4(0.2f, 1.0f, 0.6f, 1.0f));

        glBindVertexArray(m.getVaoID());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        render::TextRenderer::renderText("Project Neptune", 2.0f, 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        wnd.swapBuffers();
        Window::pollEvents();
    }

    return 0;
}