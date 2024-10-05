#pragma once

#include <string>
#include <util/vec.hpp>

namespace neptune::client {
    class Window {
    private:
        void *handle;

    public:
        Window(std::string str, utils::Vector2i size);

        void makeCurrent();
        bool shouldClose();
        void swapBuffers();
        
        static void initGL();
        static void pollEvents();
    };
}