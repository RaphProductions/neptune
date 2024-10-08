#pragma once

#include <boost/stacktrace/stacktrace.hpp>
#include <string>
#include <boost/stacktrace.hpp>

namespace neptune::utils {
    class NeptuneException
    {
    private:
        std::string msg;
        std::string details;
        boost::stacktrace::stacktrace *st;
        bool details_provided = false;

    public:
        NeptuneException(std::string msg)
        {
            this->st = new boost::stacktrace::stacktrace();

            this->msg = msg;
        }

        NeptuneException(std::string msg, std::string details)
        {
            this->st = new boost::stacktrace::stacktrace();

            this->msg = msg;
            this->details = details;

            details_provided = true;
        }

        bool isDetailsProvided() { return details_provided; }
        std::string getDetails() { return details; }
        std::string getMessage() { return msg; }
        boost::stacktrace::stacktrace *getStacktrace() { return st; }
    };
}