#pragma once

#include <string>

namespace neptune::client {
    enum EventType {
        E_Inexistant,
        E_Expose,
        E_Close, // When the window closes
        E_Update, // Tells the game it needs to update
        E_KeyPress,
        E_KeyRelease,
        E_ButtonPress,
        E_ButtonRelease
    };

    class Event {
    public:
        EventType type;
    };

    class NativeWindow {
    public:
        // Window's handle: HWND on Window, XWindow on Linux/X11, NSWindow on macOS
        void *display;
        void *event;
        unsigned long handle;  
    };

    class Window {
    public:
        bool isEmptyWindow = true;
        int width;
        int height;
        std::string title;
        NativeWindow nw;

        Event nextEvent();
    };

}