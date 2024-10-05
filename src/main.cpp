#include "util/err.hpp"
#include <client/Game.hpp>

//#define BOOST_STACKTRACE_USE_ADDR2LINE
//#include <boost/stacktrace.hpp>

#include <cstdio>
#include <iostream>

using namespace neptune::client;

/// @brief The game's "real" entry point: Just a little shortcut to Game::run.
int main(int argc, char **argv) {
    try {
        Game g;
        return g.run(argc, argv);
    } catch (neptune::utils::NeptuneException e) {
        printf("! Neptune: CRASH !\n");
        printf("%s\n\n", e.getMessage().c_str());

        printf("Stacktrace: Disabled.\n");
        
        //std::cout << e.getStacktrace() << std::endl; // Capture up to 50 frames


        return 1;
    }
}