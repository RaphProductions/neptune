#include <client/Game.hpp>
#include <client/native/PlatformManager.hpp>

using namespace neptune::client;
using namespace neptune::client::native;

int Game::run(int argc, char **argv)
{
    native::PlatformManager::setPlatformAuto();
    client::Window wnd = PlatformManager::getPlatform()->createWindow("Neptune", 800, 600);
    
    Event e;
    while (1) 
    { 
        e = wnd.nextEvent();
        if (e.type == E_Expose) {
            //XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            //XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
        }
        else if (e.type == E_KeyPress) {
            break;
        }
    }
    return 0;
}