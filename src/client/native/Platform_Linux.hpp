#pragma once

#include "client/native/PlatformManager.hpp"

namespace neptune::client::native {

std::unique_ptr<native::Platform> getLinuxPlatform();

}