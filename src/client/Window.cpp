#include "client/render/TextRenderer.hpp"
#include <cstdio>
#include <cstdlib>
#include <client/Window.hpp>
#include <client/glad/glad.h> // GLAD must be included before GLFW
#include <GLFW/glfw3.h>
#include <util/vec.hpp>
#include <util/err.hpp>

using namespace neptune::client;
using namespace neptune::utils;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(std::string title, Vector2i size)
{
    if (!glfwInit())
        throw utils::NeptuneException("GLFW could not be initialized.");

    glfwSetErrorCallback([](int error_code, const char* description) 
    { 
        char *buf = (char *)malloc(512);
        snprintf(buf, 512, "GLFW error %d: %s", error_code, description);

        throw NeptuneException(buf);
    });
    /***glfwSetFramebufferSizeCallback((GLFWwindow*)handle, [](GLFWwindow *h, int xw, int yh) {
        if (glad_glViewport)
        {
            glViewport(0, 0, xw, yh);
        }
    });***/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->handle = glfwCreateWindow(size.getX(), size.getY(), title.c_str(), NULL, NULL);

    glfwSetFramebufferSizeCallback((GLFWwindow*)handle, framebuffer_size_callback);
    glfwSetKeyCallback((GLFWwindow *)handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);

        if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
            if (glfwGetWindowMonitor(window) == NULL) {
                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            } else {
                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(window, nullptr, 0, 0, 800, 600, mode->refreshRate);
            }
        }
    });
}

void Window::initGL() {
    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw NeptuneException("GLAD initialization failed. (How i would even draw my cubes?)");
    }
}

void Window::makeCurrent()
{
    glfwMakeContextCurrent((GLFWwindow *)handle);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose((GLFWwindow*)handle);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers((GLFWwindow *)handle);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    // Scaled text is ugly. Set the text's projection for a better text quality.
    render::TextRenderer::setTextProjection(0, 0, width, height);
}