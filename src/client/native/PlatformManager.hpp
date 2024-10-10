#pragma once

#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>
#include <client/wm.hpp>

namespace neptune::client::native {
    class Platform {
    public:
        virtual void ctor() { }

        virtual neptune::client::Window createWindow(std::string title, int w, int h) {
            printf("base platform");
            return neptune::client::Window();
        }

        virtual neptune::client::Event nextEvent_wnd(neptune::client::Window *w) {
            return neptune::client::Event();
        }

        virtual void makeGLContextCurrent(neptune::client::NativeWindow w) {

        }

        virtual void glSwapBuffers(neptune::client::NativeWindow w) {

        }
    };

    class PlatformManager {
    private:
        static bool isPlatformSet;
        static std::unique_ptr<Platform> platform;

    public:
        static void setPlatform(std::unique_ptr<Platform> p) {
            if (p == NULL)
                return;

            if (!isPlatformSet)
            {
                platform = std::move(p);
                platform.get()->ctor();
                isPlatformSet = true;
            }
        }

        static void setPlatformAuto();

        static Platform *getPlatform()
        {
            assert(isPlatformSet);
            return platform.get();
        }
    };
}