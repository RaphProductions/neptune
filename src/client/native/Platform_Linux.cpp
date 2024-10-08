#include "client/native/PlatformManager.hpp"
#include "client/wm.hpp"

#ifdef __linux__

// XLib devs, tell me why DIDN'T YOU ADD A 'X' SUFFIX
// BEFORE ALL YOUR CLASSES! It could be 'XWindow' instead
// of 'Window', BECAUSE I HAVE NOW AMBIGUOUS REFERENCES!
// AHHHHH

#include "Platform_Linux.hpp"
#include <memory>
#include <X11/Xlib.h>

using namespace neptune;

class Platform_Linux : public client::native::Platform {
private:
    void createGL() {
        
    }
public:
    virtual void ctor() override {
        printf("Creating Linux platform...\n");
    }

    virtual client::Window createWindow(std::string title, int w, int h) override {
        client::NativeWindow nw;

        nw.display = (void*)XOpenDisplay(NULL);
        int s = DefaultScreen(nw.display);

        nw.handle = XCreateSimpleWindow((Display*)nw.display, RootWindow((Display*)nw.display, s), 40, 40, w, h, 0, BlackPixel((Display*)nw.display, s), WhitePixel((Display*)nw.display, s));
        
        XSelectInput((Display*)nw.display, (Window)nw.handle, ExposureMask | KeyPressMask);
        XMapWindow((Display*)nw.display, (Window)nw.handle);
        XStoreName((Display *)nw.display, nw.handle, title.c_str());
        
        //printf("linux platform\n");

        client::Window wnd;
        wnd.width = w;
        wnd.height = h;
        wnd.title = title;
        wnd.nw = nw;
        wnd.isEmptyWindow = false;

        return wnd;
    }
};

std::unique_ptr<client::native::Platform> client::native::getLinuxPlatform() {
    return std::make_unique<Platform_Linux>();
}

#endif