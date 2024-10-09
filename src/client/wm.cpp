#include "client/native/PlatformManager.hpp"
#include "wm.hpp"

neptune::client::Event neptune::client::Window::nextEvent() {
    return neptune::client::native::PlatformManager::getPlatform()->nextEvent_wnd(this);
}