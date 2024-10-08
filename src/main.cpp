#include "util/err.hpp"
#include "util/errhandler.hpp"
#include <client/Game.hpp>

using namespace neptune::client;

/// @brief The game's "real" entry point: Just a little shortcut to Game::run.
int main(int argc, char **argv) {

    try {
        neptune::utils::ErrHandler::init();

        Game g;
        return g.run(argc, argv);
    } catch (neptune::utils::NeptuneException e) {
        neptune::utils::ErrHandler::__except_handler(e);

        return 1;
    }
}