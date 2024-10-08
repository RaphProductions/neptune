#include "errhandler.hpp"
#include "util/err.hpp"

#include <cstdarg>
#include <cstdlib>
#include <util/PLTHook/plthook.h>

using namespace neptune::utils;

void (*assert_fail_og)(const char *, const char *, unsigned int, const char *);

/// Hook for LibC's assert failed function.
void __assert_fail_hook(const char *assertion, const char *file, unsigned int line, const char *function) {
    char *buf = (char*)malloc(2048);

    snprintf(buf, 2048,
        "An assertion failed in: \n"
        "- File: %s\n"
        "- Line: %d\n"
        "- Function: %s\n"
        "- Condition: %s\n\n"
        "This means that Neptune detected a problem in it's state.\n"
        "You may copy this message and report this issue on GitHub: https://github.com/RaphProductions/neptune",
        file, line, function, assertion);


    throw neptune::utils::NeptuneException("libc: Assertion failed!", buf);
}

char *snprintf_ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    char *buf = (char*)malloc(4096);
    vsnprintf(buf, 4096, fmt, ap);

    va_end(ap);

    return buf;
}

void ErrHandler::init()
{
    plthook_t *plthook;
    
    if (plthook_open_by_address(&plthook, &assert_fail_og) != 0) {
        throw NeptuneException(snprintf_ret("errhandler: plthook_open error: %s\n", plthook_error()));
        
    }
    if (plthook_replace(plthook, "__assert_fail", (void*)__assert_fail_hook, (void**)&assert_fail_og) != 0) {
        plthook_close(plthook);
        throw NeptuneException(snprintf_ret("errhandler: plthook_replace error: %s\n", plthook_error()));
    }
}

void ErrHandler::__except_handler(neptune::utils::NeptuneException e) {
    printf("! Neptune: CRASH !\n");
    printf("%s\n\n", e.getMessage().c_str());

    if (e.isDetailsProvided())
        printf("%s\n\n", e.getDetails().c_str());

    printf("Stacktrace: Disabled.\n");
}