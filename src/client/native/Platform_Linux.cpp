#include "client/native/PlatformManager.hpp"
#include "client/wm.hpp"
#include "util/err.hpp"
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
        int glx_ver = gladLoaderLoadGLX((Display*)nw.display, s);
        if (glx_ver == 0)
        {
            throw neptune::utils::NeptuneException("Unable to load the OpenGL-X11 connector!");
        }
        
        // Get the visual info
        Window root = RootWindow(nw.display, s);

        GLint visual_attributes[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
        XVisualInfo *visual_info = glXChooseVisual((Display *)nw.display, s, visual_attributes);
        
        Colormap colormap = XCreateColormap((Display *)nw.display, root, visual_info->visual, AllocNone);

        XSetWindowAttributes attributes;
        attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;
        attributes.colormap = colormap;

        // Create a Bimbow
        nw.handle = XCreateWindow((Display *)nw.display, root, 0, 0, w, h, 0,
                      visual_info->depth, InputOutput, visual_info->visual,
                      CWColormap | CWEventMask, &attributes);

        
        XMapWindow((Display*)nw.display, (Window)nw.handle);
        XStoreName((Display *)nw.display, nw.handle, title.c_str());
        
        // Now create the OpenGL context.
        GLXContext ctx = glXCreateContext((Display*)nw.display, visual_info, NULL, GL_TRUE);
        nw.gl_context = (void*)ctx;

        // Create the toplevel window object
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

    virtual void makeGLContextCurrent(client::NativeWindow w) override {
        glXMakeContextCurrent((Display*)w.display, w.handle, w.handle, (GLXContext)w.gl_context);
    }

    virtual void glSwapBuffers(client::NativeWindow w) override {
        glXSwapBuffers((Display *)w.display, w.handle);
    }
};

std::unique_ptr<client::native::Platform> client::native::getLinuxPlatform() {
    return std::make_unique<Platform_Linux>();
}

#endif