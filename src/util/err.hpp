#pragma once

#include <string>
#include <boost/stacktrace.hpp>

namespace neptune::utils {
    class NeptuneException
    {
    private:
        std::string msg;

    public:
        NeptuneException(std::string msg)
        {
            this->msg = msg;
        }

        std::string getMessage() { return msg; }
    };
}