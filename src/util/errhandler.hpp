#pragma once

#include "util/err.hpp"
namespace neptune::utils {
    class ErrHandler {
    public:
        static void init();
        static void __except_handler(NeptuneException e);
    };
}