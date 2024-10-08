#pragma once

#include <string>

namespace neptune::utils {
    
#ifdef _WIN32
    std::string home_dir = "C:\\Users\\"; // The Microsoft classic...
#elif defined (__linux)
    std::string home_dir = "/home/"; // The classic...
#elif defined (__APPLE__)
    std::string home_dir = "/Users/"; // Even through macOS is a *NIX, it uses different paths
#else
    #error Unknown platform!
#endif

}