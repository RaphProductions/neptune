#include "PlatformManager.hpp"
#include "Platform_Linux.hpp"
#include "util/err.hpp"

using namespace neptune::client::native;
using namespace neptune::utils;

bool PlatformManager::isPlatformSet;
std::unique_ptr<Platform> PlatformManager::platform;

void PlatformManager::setPlatformAuto() {
#ifdef __linux__
    setPlatform(getLinuxPlatform()); 
#else
    throw NeptuneException("Unsupported platform!");
#endif
}