#include "client/native/PlatformManager.hpp"
#include "wm.hpp"

neptune::client::Event neptune::client::Window::nextEvent() {
    return neptune::client::native::PlatformManager::getPlatform()->nextEvent_wnd(this);
}

void neptune::client::Window::glSwapBuffers() {
    if (nw.gl_context)
    {
        native::PlatformManager::getPlatform()->glSwapBuffers(nw);
    }
}

void neptune::client::Window::glMakeContextCurrent() {
    if (nw.gl_context)
    {
        native::PlatformManager::getPlatform()->makeGLContextCurrent(nw);
    }
}