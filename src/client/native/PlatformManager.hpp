#pragma once

#include "client/wm.hpp"
#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>

namespace neptune::client::native {
    class Platform {
    public:
        virtual void ctor() { }

        virtual Window createWindow(std::string title, int w, int h) {
            printf("base platform");
            return Window();
        }

        virtual Event nextEvent_wnd(Window *w) {
            return Event();
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