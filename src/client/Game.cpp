#include <client/Game.hpp>
#include <client/native/PlatformManager.hpp>
#include <X11/Xlib.h>

using namespace neptune::client;
using namespace neptune::client::native;

int Game::run(int argc, char **argv)
{
    native::PlatformManager::setPlatformAuto();
    client::Window wnd = PlatformManager::getPlatform()->createWindow("Neptune", 800, 600);
    
    XEvent e;
    while (1) 
    { 
        XNextEvent((Display*)wnd.nw.display, &e);
        if (e.type == Expose) {
            //XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            //XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }
    return 0;
}