#pragma once

#include <string>

namespace neptune::client {
    class NativeWindow {
    public:
        // Window's handle: HWND on Window, XWindow on Linux/X11, NSWindow on macOS
        void *display;
        unsigned long handle;  
    };

    class Window {
    public:
        bool isEmptyWindow = true;
        int width;
        int height;
        std::string title;
        NativeWindow nw;
    };

    enum EventType {
        Expose,
        Close, // When the window closes
        Update // Tells the game it needs to update
    };

    class Event {
    public:
        EventType type;
    };
}