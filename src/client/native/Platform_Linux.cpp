#include "client/native/PlatformManager.hpp"
#include "client/wm.hpp"
#include <cstdlib>
#include <dlfcn.h>

#ifdef __linux__

// XLib devs, tell me why DIDN'T YOU ADD A 'X' SUFFIX
// BEFORE ALL YOUR CLASSES! It could be 'XWindow' instead
// of 'Window', BECAUSE I HAVE NOW AMBIGUOUS REFERENCES!
// AHHHHH

#include <client/glad/glx.h>
#include "Platform_Linux.hpp"
#include <memory>
#include <X11/Xlib.h>

using namespace neptune;

client::EventType xEventBindingTable[LASTEvent] = {
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_KeyPress,
    client::E_KeyRelease,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Expose,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
    client::E_Inexistant,
};

class Platform_Linux : public client::native::Platform {
private:
    void init_GL() {
    }
public:
    virtual void ctor() override {
        
        
        //printf("Creating Linux platform...\n");
    }

    virtual client::Window createWindow(std::string title, int w, int h) override {
        client::NativeWindow nw;

        nw.event = malloc(sizeof(XEvent));
        nw.display = (void*)XOpenDisplay(NULL);
        int s = DefaultScreen(nw.display);

        // Load GLX
        gladLoaderLoadGLX((Display*)nw.display, s);

        nw.handle = XCreateSimpleWindow((Display*)nw.display, RootWindow((Display*)nw.display, s), 40, 40, w, h, 0, BlackPixel((Display*)nw.display, s), WhitePixel((Display*)nw.display, s));
        
        XSelectInput((Display*)nw.display, (Window)nw.handle, ExposureMask | KeyPressMask);
        XMapWindow((Display*)nw.display, (Window)nw.handle);
        XStoreName((Display *)nw.display, nw.handle, title.c_str());
        
        client::Window wnd;
        wnd.width = w;
        wnd.height = h;
        wnd.title = title;
        wnd.nw = nw;
        wnd.isEmptyWindow = false;

        return wnd;
    }

    virtual client::Event nextEvent_wnd(client::Window *w) override {
        client::Event ev;

        XNextEvent((Display*)w->nw.display, (XEvent*)w->nw.event);
        ev.type = xEventBindingTable[((XEvent*)w->nw.event)->type];

        return ev;
    }
};

std::unique_ptr<client::native::Platform> client::native::getLinuxPlatform() {
    return std::make_unique<Platform_Linux>();
}

#endif